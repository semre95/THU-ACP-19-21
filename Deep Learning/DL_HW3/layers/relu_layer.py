""" ReLU Layer """

import numpy as np


class ReLULayer():
    def __init__(self):
        """
        Applies the rectified linear unit function element-wise: relu(x) = max(x, 0)
        """
        self.trainable = False  # no parameters

    def forward(self, Input):
        ############################################################################

        self.x = Input
        return np.maximum(0, Input)

        ############################################################################

    def backward(self, delta):

        ############################################################################
        # TODO: Put your code here
        # Calculate the gradient using the later layer's gradient: delta

        return delta * (self.x > 0)

        ############################################################################
