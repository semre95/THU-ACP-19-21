#!/usr/bin/env python
# coding: utf-8

# In[1]:


import gym
import random
import numpy as np
import tflearn
from tflearn.layers.core import input_data, dropout, fully_connected
from tflearn.layers.estimator import regression
from statistics import median, mean
from collections import Counter

LR = 1e-3
env = gym.make("CartPole-v1")
env.reset()
goal_steps = 500
score_requirement = 50
initial_games = 10000


# In[2]:


def some_random_games_first():
    
    for episode in range(5):
        env.reset()
        # each frame, up to 200
        for t in range(200):
            
            env.render()
            
            # action can be 0 or 1,left or right
            action = env.action_space.sample()
            observation, reward, done, info = env.step(action)
            if done:
                break


# In[3]:


def initial_population():
  
    training_data = []
    scores = []
    accepted_scores = []

    for _ in range(initial_games):
        score = 0
        game_memory = []
        prev_observation = []
        # for each frame in 200
        for _ in range(goal_steps):
            # choose random action (0 or 1)
            action = random.randrange(0,2)
            observation, reward, done, info = env.step(action)
            
            if len(prev_observation) > 0 :
                game_memory.append([prev_observation, action])
            prev_observation = observation
            score = score + reward
            if done: break

      
        if score >= score_requirement:
            accepted_scores.append(score)
            for data in game_memory:
                # converting to 0 or 1 , For NN layer
                if data[1] == 1:
                    output = [0,1]
                elif data[1] == 0:
                    output = [1,0]
                    
                # save training data
                training_data.append([data[0], output])

        
        env.reset()
        scores.append(score)
    
    training_data_save = np.array(training_data)
    np.save('saved.npy',training_data_save)
    
    print('Average accepted score:',mean(accepted_scores))
    print('Median score for accepted scores:',median(accepted_scores))
    print(Counter(accepted_scores))
    
    return training_data


# In[4]:


def neural_network_model(input_size):

    network = input_data(shape=[None, input_size, 1], name='input')

    network = fully_connected(network, 128, activation='relu')
    network = dropout(network, 0.8)

    network = fully_connected(network, 256, activation='relu')
    network = dropout(network, 0.8)

    network = fully_connected(network, 512, activation='relu')
    network = dropout(network, 0.8)

    network = fully_connected(network, 256, activation='relu')
    network = dropout(network, 0.8)

    network = fully_connected(network, 128, activation='relu')
    network = dropout(network, 0.8)

    network = fully_connected(network, 2, activation='softmax')
    network = regression(network, optimizer='adam', learning_rate=LR, loss='categorical_crossentropy', name='targets')
    model = tflearn.DNN(network, tensorboard_dir='log')

    return model


# In[5]:


def train_model(training_data, model=False):

    X = np.array([i[0] for i in training_data]).reshape(-1,len(training_data[0][0]),1)
    y = [i[1] for i in training_data]

    if not model:
        model = neural_network_model(input_size = len(X[0]))
    
    model.fit({'input': X}, {'targets': y}, n_epoch=5, snapshot_step=500, show_metric=True, run_id='openai_learning')
    return model


# In[6]:


training_data = initial_population()


# In[7]:


model = train_model(training_data)


# In[8]:


scores = []
choices = []
for each_game in range(10):
    score = 0
    game_memory = []
    prev_obs = []
    env.reset()
    for _ in range(goal_steps):
        env.render()

        if len(prev_obs)==0:
            action = random.randrange(0,2)
        else:
            action = np.argmax(model.predict(prev_obs.reshape(-1,len(prev_obs),1))[0])

        choices.append(action)
                
        new_observation, reward, done, info = env.step(action)
        prev_obs = new_observation
        game_memory.append([new_observation, action])
        score = score + reward
        if done: break

    scores.append(score)

print('Average Score:',sum(scores)/len(scores))
print('choice 1:{}  choice 0:{}'.format(choices.count(1)/len(choices),choices.count(0)/len(choices)))
print(score_requirement)


# In[ ]:




