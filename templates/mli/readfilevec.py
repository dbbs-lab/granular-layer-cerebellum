# -*- coding: utf-8 -*-
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np

#fin = open("frvector.txt", "r")
#fin.readlines()

a = np.genfromtxt('frvector.txt')


a = a.reshape(7,30)
print a


fig = plt.figure()
ax = axes3d.Axes3D(fig)
X,Y = np.meshgrid(range(0,304,10), range(0,30,3))
print X.shape
print Y.shape
ax.plot_surface(X, Y, a, rstride=1, cstride=1, cmap=cm.jet)

plt.show()