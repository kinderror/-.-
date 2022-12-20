import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('distribution.txt')

plt.hist(data, bins = 100, edgecolor = 'black')
plt.show()
