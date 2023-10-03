#!/usr/bin/env python3
# -*- coding: utf-8 -*-
""" 
Created on Mon Oct 5 17:36:56 2020 
@author: hernan 
"""
import matplotlib.pyplot as plt
import numpy as np

def sin(x):
    return np.sin(x)


def p3d(x):
    return np.sin(x**3 - 5*(x+0.1)**2) / (x**3 + (x+0.1)**-2)


def exhaustive_search(f, x_min, x_max, delta):

    txtname = "./text/exsearch_p3d_" + str(x_min) + "_" + str(x_max) + "_" + str(delta) + ".txt"
    fi = open(txtname, 'w')
    points = []
    fvalues = []
    x = x_min
    fx = f(x)
    fbest = fx
    xbest = x
    while x < x_max:
        points.append(x)
        fvalues.append(fx)

        x = x + delta
        fx = f(x)
        if x <= x_max:
            if fx > fbest:
                fbest = fx
                xbest = x
        fi.write("f({}): {}\n".format(x, fx))

    fi.write("best f({}): {}".format(xbest, fbest))
    fi.close()

    return points, fvalues, xbest, fbest

# 関数を選ぶ
#f = sin
f = p3d
# 変数の範囲を設定
x_min = -2
x_max = -1.1
# 探索の間隔を設定
delta = 0.001
# 全探索を呼び出す
x_search, fx_search, xbest, fbest = exhaustive_search(f, x_min, x_max, delta) 
x_search = np.array(x_search)
fx_search = np.array(fx_search)
# 関数をプロットする
x_sample = np.arange(x_min, x_max, 0.001)
plt.plot(x_sample, f(x_sample))
# 探索点をプロットする
plt.plot(x_search, fx_search, 'ro')
plt.plot(x_search[0], fx_search[0], 'bo')
plt.plot(xbest, fbest, 'ko')
plt.xlabel("x")
plt.ylabel("f(x)")
#plt.legend(['関数','探索された x','探索の出発点','最高の探索点'])
plt.legend(['function', 'searched $x$', 'starting $x_0$', 'best $x$']) 
dirname = "C://Program_Code/LaTeX/OPT/class2/"
filename = dirname + "exsearch_p3d_" + str(x_min) + "_" + str(x_max) + "_" + str(delta) + ".png"
plt.savefig(filename)
plt.show()
