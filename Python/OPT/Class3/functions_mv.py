import numpy as np
m_epsilon = np.finfo(dtype=np.float32).eps
epsilon = m_epsilon*2
##################################
# sum(x^2)
##################################


def squared_f(x):
    return np.sum(np.array([x[x_i]**2 for x_i in range(x.shape[0])]))


def squared_df_analytic(x):
    return 2*x


def squared_h_analytic(x):
    N = x.shape[0]
    shape = (N, N)
    H = np.full(shape, 0.)
    for dim in range(N):
        H[dim, dim] = 2.0
    return H
##################################
# rastrigin
##################################


def rastrigin(x, n=None, A=10.):
    if n is None:
        n = x.shape[0]
    return A*n + np.sum(x**2 - A*np.cos(2*np.pi*x))


def rastrigin_df_analytic(x, A=10.):
    return 2*x + A*np.sin(2*np.pi*x)*2*np.pi


def rastrigin_h_analytic(x, A=10.):
    N = len(x)
    H = np.zeros((N, N))
    for i in range(N):
        H[i, i] = 2.0 + A*4.0*np.pi**2 * np.cos(2*np.pi*x[i, 0]) 
    return H
    # #################################
    # numerical gradient generic functions
    # #################################


def gradient(x, f):
    print("mv gradient")

    gradient = np.empty(x.shape)
    for i in range(len(x)):
        x_eps = np.zeros(x.shape)
        x_eps[i] = epsilon
        # calculate by central difference
        partial_gradient = (f(x + x_eps) - f(x - x_eps))/(2.*epsilon)  
        gradient[i] = partial_gradient
    return gradient


def hessian(x, f):
    dimensions = x.shape[0]
    H = np.empty((dimensions, dimensions))
    for i in range(dimensions):
        x_eps = np.zeros((dimensions, 1))
        x_eps[i] = epsilon
        # calculate by central difference
        row_gradient = (gradient(x + x_eps, f) - gradient(x - x_eps, f)) / (2.*epsilon)
        H[i, :] = row_gradient.T
    return H

