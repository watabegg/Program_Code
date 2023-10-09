import matplotlib.pyplot as plt
import numpy as np


def sin(x):
    return np.sin(x)


def p3d(x):
    return np.sin(x**3 - 5*(x+0.1)**2) / (x**3 + (x+0.1)**-2)


def hill_climbing(f, x0, delta, x_min, x_max):
    txtname = "./text/hillclimb_p3d_" + str(x_min) + "_" + str(x_max) + "_" + str(delta) + "_" + str(x0) + ".csv"
    fi = open(txtname, 'w')
    evaluations = np.array([f(x0-delta), f(x0), f(x0+delta)])  
    points = [x0]
    fvalues = [evaluations[1]]

    index_max = np.argmax(evaluations)

    sign = 1.0
    climb = True
    if index_max == 0:
        sign = -1.0
    elif index_max == 2:
        sign = 1.0
    else:
        climb = False
    
    x = x0 + (sign*delta)
    fx = evaluations[index_max]
    fbest = fx
    while climb == True:
        points.append(x)
        fvalues.append(fx)

        x = x + (sign*delta)
        fx = f(x)
        if fx > fbest and (x <= x_max and x >= x_min):
            fbest = fx
            fi.write("f({}): {}\n".format(x, fx))
        else:
            climb = False

    return points, fvalues


# 関数を選ぶ
# f = sin
f = p3d
# 変数の範囲を設定
x_min = -2
x_max = -1.1
# 探索の出発点
x0 = -1.3  # x_min < x0 < x_max
# 探索方向を決定するための間隔
delta = 0.01
# 山のりを呼び出す
points, fvalues = hill_climbing(f, x0, delta, x_min, x_max) 
points = np.array(points)
fvalues = np.array(fvalues)
# 関数をプロットする
x = np.arange(x_min, x_max, 0.01)
plt.plot(x, f(x))
# 探索点をプロットする
plt.plot(points, fvalues, 'ro')
plt.plot(points[0], fvalues[0], 'bo')
plt.plot(points[len(points)-1], fvalues[len(fvalues)-1], 'ko')  
plt.xlabel("x")
plt.ylabel("f(x)")
# plt.legend(['関数','探索された x','探索の出発点','最高の探索点']) 
plt.legend(['function', 'searched $x$', 'starting $x_0$', 'best $x$'])
dirname = "C://Program_Code/LaTeX/OPT/class2/"
filename = dirname + "hillclimib_p3d_" + str(x_min) + "_" + str(x_max) + "_" + str(delta) + "_" + str(x0) + ".png"
plt.savefig(filename)
plt.show()
