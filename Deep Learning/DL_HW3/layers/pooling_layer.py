# -*- encoding: utf-8 -*-

import numpy as np
#This a library presented by  Stanford Course CS231n we have used this on our ML course last semester.
#It makes it more convinient to do the CNN task. It has np.pad used inside the library too.
#https://github.com/huyouare/CS231n/blob/master/assignment2/cs231n/im2col.py
from im2col import *


class MaxPoolingLayer():
	def __init__(self, kernel_size, pad):
		'''
		This class performs max pooling operation on the input.
		Args:
		kernel_size: The height/width of the pooling kernel.
		pad: The width of the pad zone.
		'''

		self.kernel_size = kernel_size
		self.pad = pad
		self.trainable = False

	def forward(self, Input, **kwargs):
		'''
		This method performs max pooling operation on the input.
		Args:
			Input: The input need to be pooled.
		Return:
			The tensor after being pooled.
		'''
		############################################################################
		# TODO: Put your code here
		# Apply convolution operation to Input, and return results.
		# Tips: you can use np.pad() to deal with padding.
		self.Input = Input
		n, d, h, w = Input.shape 
        
		height_out = (h - self.kernel_size + 2 * self.pad) // self.kernel_size + 1 
		weight_out = (w - self.kernel_size + 2 * self.pad) // self.kernel_size + 1  

		# First, reshape it to make im2col arrange it fully in column
		X_reshaped = Input.reshape(n * d, 1, h, w)

		self.X_col = im2col_indices(X_reshaped, self.kernel_size, self.kernel_size, padding=self.pad, stride=self.kernel_size)

		# Next, at each possible patch location, i.e. at each column, we're taking the max index
		self.max_idx = np.argmax(self.X_col, axis=0)

		# Finally, we get all the max value at each column
		res = self.X_col[self.max_idx, range(self.max_idx.size)]

		# Reshape to the output size
		res = res.reshape(height_out, weight_out, n, d)

		# Transpose to get size
		res = res.transpose(2, 3, 0, 1)

		return res
		############################################################################

	def backward(self, dout):
		'''
		Args:
		delta: Local sensitivity, shape-(batch_size, filters, output_height, output_width)
		Return:
		delta of previous layer
		'''
		############################################################################
		# TODO: Put your code here
		# Calculate and return the new delta.
        
		n, d, h, w = self.Input.shape

		# forward step
		dX_col = np.zeros_like(self.X_col)

		# Flaten and Transpose the step to get the correct arrangement
		dout_flat = dout.transpose(2, 3, 0, 1).ravel()

		# Fill the maximum index of each column with the gradient

		# Essentially putting each of the grads
		# to one of the (kernel_size**2) row in all locations, one at each column
		dX_col[self.max_idx, range(self.max_idx.size)] = dout_flat

		# We now have the stretched matrix later undo the operation with the library
		dX = col2im_indices(dX_col, (n * d, 1, h, w), self.kernel_size, self.kernel_size, padding=0, stride=self.kernel_size)

		# Reshape back
		dX = dX.reshape(self.Input.shape)

		return dX


		############################################################################
