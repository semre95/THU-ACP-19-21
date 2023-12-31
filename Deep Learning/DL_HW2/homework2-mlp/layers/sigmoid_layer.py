""" Sigmoid Layer """

import numpy as np


class SigmoidLayer():
    def __init__(self):
        """
        Applies the element-wise function: f(x) = 1/(1+exp(-x))
        """
        self.trainable = False

    def forward(self, Input):
        ############################################################################
        # TODO: Put your code here
        # Apply Sigmoid activation function to Input, and return results.

        self.Input = Input

        exp_scores = 1 / (1 + np.exp(-Input))
        return exp_scores

    ############################################################################

    def backward(self, delta):

        ############################################################################
        # TODO: Put your code here
        # Calculate the gradient using the later layer's gradient: delta

        exp_scores = 1 / (1 + np.exp(-self.Input))
        return delta * exp_scores * (1 - exp_scores)

        ############################################################################
