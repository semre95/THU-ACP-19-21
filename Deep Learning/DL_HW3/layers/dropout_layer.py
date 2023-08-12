""" Dropout Layer """

import numpy as np

class DropoutLayer():
	def __init__(self, p=0.5):
		self.trainable = False
		self.p = p

	def forward(self, Input, is_training = True):
        
		############################################################################
		# TODO: Put your code here
		keep = 1 - self.p
		if not is_training:
			keep = 1
		self.Input = Input
		self.mask = np.random.binomial(1, keep, size=Input.shape)
		out = Input * self.mask
		if not is_training:
			out *= 1 - self.p
		return out
    
		############################################################################

	def backward(self, dout):

		############################################################################
		# TODO: Put your code here
		dX = dout * self.mask
        
		return dX
		############################################################################
