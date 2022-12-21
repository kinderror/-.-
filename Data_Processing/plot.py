import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('distribution.txt')

sum = 0
for i in range(len(data)):
    sum += data[i]
mean = sum / len(data)
print('Mean velocity:', mean, '(0.886 needed)')
print('Dispersion:', 1 - mean ** 2)

plt.hist(data, bins = 100, edgecolor = 'black')
plt.title('Maxwell Distribution for N = 100 000')
plt.xlabel('v')
plt.ylabel('f(v)')
plt.show()
