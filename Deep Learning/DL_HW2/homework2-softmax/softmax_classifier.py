import numpy as np


def softmax_classifier(W, X, label, lamda):
    """
      Softmax Classifier

      Inputs have dimension D, there are C classes, a minibatch have N examples.
      (In this homework, D = 784, C = 10)

      Inputs:
      - W: A numpy array of shape (D, C) containing weights.
      - input: A numpy array of shape (N, D) containing a minibatch of data.
      - label: A numpy array of shape (N, C) containing labels, label[i] is a
        one-hot vector, label[i][j]=1 means i-th example belong to j-th class.
      - lamda: regularization strength, which is a hyerparameter.

      Returns:
      - loss: a single float number represents the average loss over the minibatch.
      - gradient: shape (D, C), represents the gradient with respect to weights W.
      - prediction: shape (N, 1), prediction[i]=c means i-th example belong to c-th class.
    """

    num_train = X.shape[0]
    y = np.where(label == 1)[1]  # scalar value labels

    scores = np.dot(X, W)  # compute logits
    exp_scores = np.exp(scores)  # compute exp logits
    prob_scores = exp_scores / np.sum(exp_scores, axis=1, keepdims=True)  # compute probabilities
    correct_log_probs = -np.log(prob_scores[range(num_train), y])  # compute loss for each row
    loss = np.sum(correct_log_probs)  # compute total loss
    loss /= num_train  # divide total loss by the number of rows
    loss += 0.5 * lamda * np.sum(W ** 2)  # apply regularization

    # compute gradient
    dscores = prob_scores
    dscores[range(num_train), y] -= 1
    gradient = np.dot(X.T, dscores)
    gradient /= num_train
    gradient += lamda * W  # derivative regularization

    prediction = np.argmax(exp_scores, axis=1)

    return loss, gradient, prediction