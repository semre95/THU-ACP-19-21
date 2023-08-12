""" Euclidean Loss Layer """

import numpy as np


class EuclideanLossLayer():
    def __init__(self):
        self.acc = 0.
        self.loss = 0.

    def forward(self, logit, gt):
        """
          Inputs: (minibatch)
          - logit: forward results from the last FCLayer, shape(batch_size, 10)
          - gt: the ground truth label, shape(batch_size, 10)
        """

        ############################################################################
        # TODO: Put your code here
        # Calculate the average accuracy and loss over the minibatch, and
        # store in self.accu and self.loss respectively.
        # Only return the self.loss, self.accu will be used in solver.py.

        self.logit = logit
        self.gt = gt
        N = gt.shape[0]
        self.loss = 0.5*(((logit-gt)*(logit-gt)).sum())/N
        self.acc = (logit.argmax(axis=1) == gt.argmax(axis=1)).sum() / N

        ############################################################################

        return self.loss

    def backward(self):

        ############################################################################
        # TODO: Put your code here
        # Calculate and return the gradient (have the same shape as logit)
        gradient = self.logit - self.gt
        return gradient

        ############################################################################