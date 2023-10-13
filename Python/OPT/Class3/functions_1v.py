import numpy as np
# x^2 function


def squared_f(x):
    return x**2


def squared_df_analytic(x):
    return 2*x
# rastrigin function


def rastrigin(x):
    return 10.0 + x**2 - 10.0*np.cos(2.0*np.pi*x)


def rastrigin_df_analytic(x):
    return 2.0*x + 10.0*np.sin(2.0*np.pi*x)*2.0*np.pi


def gradient(x, f):
    m_epsilon = np.finfo(dtype=np.float32).eps
    epsilon = m_epsilon*2.0
    xx = np.array([x-epsilon, x, x+epsilon])
    yy = np.array([f(x) for x in xx])
    return np.gradient(yy, xx)[1]
