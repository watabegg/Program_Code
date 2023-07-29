#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 10 14:51:32 2023

@author: hernan
"""
import math
import matplotlib.pyplot as plt
import numpy as np

def f1(x):
    return(math.pow(x,4) - 3*x + 1)  # x^4 -3x +1

def f1_der(x):
    return ( 4*math.pow(x,3) -3)

def central_df(f, x, h):
    return (f(x+h) -f(x-h))/(2*h)


# 100 linearly spaced numbers
x = np.linspace(-2,2,100)

# the function, which is y = x^2 here
#y = x**4 -3*x +1
y = [f1(i) for i in x]

#fig = plt.figure()
plt.title("$f_1$")
plt.plot(x,y, 'r')
# show the plot
plt.show()

h= 1
y_der = [f1_der(i) for i in x]
y_c_df = [central_df(f1, i, h) for i in x]
#fig = plt.figure()
plt.xlabel('x')
plt.ylabel('y')

plt.plot(x,y_der, 'r')
plt.plot(x,y_c_df, 'b')
plt.legend(["y_der","y_c_df" ])
# show the plot
plt.show()
