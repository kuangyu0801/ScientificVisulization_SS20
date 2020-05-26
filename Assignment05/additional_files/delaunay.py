#!/usr/bin/env python3

# usage: python delaunay.py [[0,1,3],[1,2,3]]
# the parameter is a list of three-tuples of indices
# every tuple describes a triangle
# current maximum index = 5

import sys
import numpy as np
import matplotlib.pyplot as plt

if len(sys.argv) < 2:
    print("No triangle data provided. Please use them as argument")

''' Create 2D visualization '''
fig, ax = plt.subplots()

''' Set vertices, creating lines forming the triangles '''
vertices = np.array([[1, 9], [6, 6], [4, 1], [11, 19], [5, 15], [16, 11]])
indices = np.array([0, 1, 2, 3, 4, 5])

triangles = []
if len(sys.argv) > 1:
    triangles = np.array(eval(sys.argv[1]))

''' Plot line segments for each triangle '''
for tri in triangles:
    coord0 = vertices[tri[0]]
    coord1 = vertices[tri[1]]
    coord2 = vertices[tri[2]]
    ax.plot([coord0[0],coord1[0]], [coord0[1],coord1[1]], color='b')
    ax.plot([coord2[0],coord1[0]], [coord2[1],coord1[1]], color='b')
    ax.plot([coord0[0],coord2[0]], [coord0[1],coord2[1]], color='b')

''' Plot points '''
ax.plot(vertices[:, 0], vertices[:, 1], 'rx')

''' Plot labels for points '''
for id in indices:
    pt = vertices[id]
    ax.annotate(str(id), pt, textcoords="offset points", xytext=(10,-10), ha='center')


''' Set axes' information '''
ax.set_xlim(0, 17)
ax.set_xticks(np.arange(0, 17, 1))

ax.set_ylim(0, 20)
ax.set_yticks(np.arange(0, 20, 1))

''' Set aspect ratio and draw a grid '''
ax.set_aspect(1)
plt.grid()

''' Show figure '''
plt.show()