# This import registers the 3D projection, but is otherwise unused.
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

import matplotlib.pyplot as plt
import numpy as np

fdata_txt = 'data'
xList = []
yList = []
zList = []
with open(fdata_txt, 'r') as f:
    # skip first two line
    next(f)
    next(f)
    for line in f:
        list = line.split(' ')
        xList.append(float(list[5]))
        yList.append(float(list[9]))
        zList.append(float(list[12]))
        print(list[5])
        print(list[9])
        print(list[12])

zMax = zList[0]
zIndexMax = 0
index = 0
for i in zList:
    if i > zMax:
        zMax = i
        zIndexMax = index
    index += 1
print("Maximal value is", zMax, "at (", xList[zIndexMax], ",", yList[zIndexMax], ")")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(xList, yList, zList, c='b', marker='o')

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
