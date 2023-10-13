import functions_1v as functions
import numpy as np
import matplotlib.pyplot as plt
import random

xmin = -3
xmax = 3

f = functions.squared_f
xx = np.arange(xmin, xmax, 0.01)
plt.plot(xx, f(xx))
plt.show()

x = []
for i in range(10):
    r = random.uniform(xmin, xmax)
    x.append(r)
x.sort()

xpa_s = [functions.squared_df_analytic(e) for e in x]
xpg_s = [functions.gradient(e, f) for e in x]
for i in range(len(x)):
    print("{:7.2f} {:7.2f} {:7.2f}".format(x[i], xpa_s[i], xpg_s[i]))

f = functions.rastrigin
xx = np.arange(xmin, xmax, 0.01)
plt.plot(xx, f(xx))
plt.show()

xpa_r = [functions.rastrigin_df_analytic(e) for e in x]
xpg_r = [functions.gradient(e, f) for e in x]
for i in range(len(x)):
    print("{:7.2f} {:7.2f} {:7.2f}".format(x[i], xpa_r[i], xpg_r[i]))
