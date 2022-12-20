import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

data = np.loadtxt('random_walk.txt')

dt = 0.01
t = data[:, 0]
x = data[:, 1]
y = data[:, 2]

fig = plt.figure(figsize=(5, 4))
ax = fig.add_subplot(autoscale_on=False, xlim=(0, 40), ylim=(0, 40))
ax.set_aspect('equal')
ax.grid()

history_len = len(data)
trace, = ax.plot([], [], '.-', lw=1, ms=2)
time_template = 'time = %.1fs'
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)
history_x, history_y = deque(maxlen=history_len), deque(maxlen=history_len)


def animate(i):
    if i == 0:
        history_x.clear()
        history_y.clear()

    history_x.appendleft(x[10*i])
    history_y.appendleft(y[10*i])

    trace.set_data(history_x, history_y)
    time_text.set_text(time_template % (i*10*dt))
    return trace, time_text


ani = animation.FuncAnimation(
    fig, animate, len(data), interval=dt*100, blit=True)
plt.show()
