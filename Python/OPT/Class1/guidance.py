import matplotlib.pyplot as plt

def f_x(x):
    return x**2 + x - 1

xvalues = range (1,11)

yvalues = [f_x(x) for x in xvalues]

plt.xlabel("x")
plt.ylabel("f(x)")
plt.title(r"Plot of $x^2 + x -1$ ")
plt.plot(xvalues,yvalues)
