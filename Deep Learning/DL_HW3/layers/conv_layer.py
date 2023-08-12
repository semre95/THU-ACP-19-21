# -*- encoding: utf-8 -*-

import numpy as np
# This a library presented by  Stanford Course CS231n we have used this on our ML course last semester.
#It makes it more convinient to do the CNN task. It has np.pad used inside the library.
#https://github.com/huyouare/CS231n/blob/master/assignment2/cs231n/im2col.py
from im2col import *

class ConvLayer():
	"""
	2D convolutional layer.
	This layer creates a convolution kernel that is convolved with the layer
	input to produce a tensor of outputs.
	Arguments:
		inputs: Integer, the channels number of input.
		filters: Integer, the number of filters in the convolution.
		kernel_size: Integer, specifying the height and width of the 2D convolution window (height==width in this case).
		pad: Integer, the size of padding area.
		trainable: Boolean, whether this layer is trainable.
	"""
	def __init__(self, inputs, filters, kernel_size, pad = 0, trainable=True, stride = 1):
		self.inputs = inputs
		self.filters = filters
		self.kernel_size = kernel_size
		self.pad = pad
        
		assert pad < kernel_size, "pad should be less than kernel_size"
		self.trainable = trainable
		self.stride = stride

		self.XavierInit()

		self.grad_W = np.zeros_like(self.W)
		self.grad_b = np.zeros_like(self.b)

	def XavierInit(self):
		raw_std = (2 / (self.inputs + self.filters))**0.5
		init_std = raw_std * (2**0.5)

		self.W = np.random.normal(0, init_std, (self.filters, self.inputs, self.kernel_size, self.kernel_size))
		self.b = np.random.normal(0, init_std, (self.filters,))

	def forward(self, Input):
		'''
		forward method: perform convolution operation on the input.
		Agrs:
			Input: A batch of images, shape-(batch_size, channels, height, width)
		'''
		############################################################################
		# TODO: Put your code here
		# Apply convolution operation to Input, and return results.
		# Tips: you can use np.pad() to deal with padding.
		self.Input = Input

		n_x, d_x, h_x, w_x = Input.shape
		n_filters, d_filter, h_filter, w_filter = self.W.shape
		height_out = (h_x - h_filter + 2 * self.pad) // self.stride + 1  # feature map height
		width_out = (w_x - w_filter + 2 * self.pad) // self.stride + 1  # feature map length

		self.X_col = im2col_indices(Input, self.kernel_size, self.kernel_size, padding=self.pad, stride=self.stride)
		W_col = self.W.reshape(self.filters, -1)
		outputs = W_col @self.X_col + self.b.reshape(self.filters, 1)

		outputs = outputs.reshape(self.filters, height_out, width_out, n_x)
		outputs = outputs.transpose(3, 0, 1, 2)

		return outputs

		############################################################################


	def backward(self, delta):
		'''
		backward method: perform back-propagation operation on weights and biases.
		Args:
			delta: Local sensitivity, shape-(batch_size, filters, output_height, output_width)
		Return:
			delta of previous layer
		'''
		############################################################################
		# TODO: Put your code here
		# Calculate self.grad_W, self.grad_b, and return the new delta.
		db = np.sum(delta, axis=(0, 2, 3))
		self.grad_b = db.reshape(self.filters)

		delta_reshaped = delta.transpose(1, 2, 3, 0).reshape(self.filters, -1)
		dW = delta_reshaped @ self.X_col.T
		self.grad_W = dW.reshape(self.W.shape)

		W_reshape = self.W.reshape(self.filters, -1)
		dX_col = W_reshape.T @ delta_reshaped
		dX = col2im_indices(dX_col, self.Input.shape, self.kernel_size, self.kernel_size,padding=self.pad, stride=self.stride)
		return dX

		############################################################################



