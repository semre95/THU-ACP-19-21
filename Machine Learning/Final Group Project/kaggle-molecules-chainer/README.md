Kaggle Predicting Molecular Properties

Download and save all files from the dataset (https://www.kaggle.com/c/14313/download-all) to the folder dataset

Download files test_ob_charges.csv and train_ob_charges.csv and save them to the folder input  (https://www.kaggle.com/asauve/v7-estimation-of-mulliken-charges-with-open-babel)


First method can be launched as a single notebook (Champs_scalar_coupling.ipynb)

Second method should be run in such order:
- run \kaggle-molecules-chainer\source\01_preprocess\preprocess.py
- run \kaggle-molecules-chainer\source\02_triplet_update\main.py
- run \kaggle-molecules-chainer\source\03_node_edge_update\main.py
- run \kaggle-molecules-chainer\source\04_submission\submission.py

# References

- https://github.com/toshi-k/kaggle-champs-scalar-coupling — this repository was used as reference to create graph neural network for predicting scalar coupling constants

- https://github.com/jensengroup/xyz2mol — this repository was used as library for molecular scructure parsing 

- https://www.kaggle.com/asauve/v7-estimation-of-mulliken-charges-with-open-babel — this link was used to get mulliken charges with with Open Babel library

- https://github.com/pfnet-research/chainer-chemistry - Chainer Chemistry: A Library for Deep Learning in Biology and Chemistry
