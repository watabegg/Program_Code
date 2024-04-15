import numpy as np
import matplotlib.pyplot as plt

x=np.arange(0.01, 10.0, 0.005)

dx=[0.01,0.1,0.5,1,2,4,8,10]
dy=[218,26,8,4,1,8,31,230]

plt.figure()
plt.plot(x,2.185093/x + 0.010431*np.exp(x), '-b')
plt.legend([r'$y=\frac{2.185093}{x}+0.010431e^x$'])
plt.scatter(dx,dy,c="red")
plt.xlabel('x')
plt.ylabel('y')
plt.savefig("./LaTeX/NumMeth/8/plot.png")
plt.show()
