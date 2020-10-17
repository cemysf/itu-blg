#! /usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

input_file="440_FO_Matrix.txt"

matrix=[]

# Read file into an array
with open(input_file) as f:
	for line in f:
		matrix.append(line.split())

# Copy matrix into numpy array
numpy_array=np.array(matrix, dtype=np.float)

# Plot numpy array
fig = plt.figure()
ax= fig.add_subplot(1,1,1)
ax.imshow(numpy_array, cmap=plt.cm.Greens, origin="lower")
ax.xaxis.tick_top()
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['bottom'].set_visible(False)
ax.spines['left'].set_visible(False)
plt.gca().invert_yaxis()

# Show and write
plt.show()
fig.savefig("adjMatrix_output.png", dpi=350)


