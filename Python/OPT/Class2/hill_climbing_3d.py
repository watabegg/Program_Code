import matplotlib.pyplot as plt
import numpy as np
import copy as cp

def sin_2v(x1,x2):
    return (np.sin(x1) + np.sin(x2)) / 2


def p3d_2v(x1,x2):
    return (np.sin(x1**3 - 5*(x1+0.1)**2) / (x1**3 + (x1+0.1)**-2) + np.sin(x2**3 - 5*(x2+0.1)**2) / (x2**3 + (x2+0.1)**-2)) / 2


def hill_climbing(f, x0, delta, x_min, x_max):
    txtname = "./text/hillclimb3d_sin_" + str(x_min) + "_" + str(x_max) + "_" + str(delta) + "_" + str(x0) + ".txt"
    fi = open(txtname, 'w')
    evaluations = np.array([
        [f(x0[0]-delta,x0[1]-delta), f(x0[0]-delta,x0[1]), f(x0[0]-delta,x0[1]+delta)],
        [f(x0[0],x0[1]-delta), f(*x0), f(x0[0],x0[1]+delta)],
        [f(x0[0]+delta,x0[1]-delta), f(x0[0]+delta,x0[1]), f(x0[0]+delta,x0[1]+delta)]
        ])  
    points = [x0]
    fvalues = [evaluations[1]]

    index_max = np.unravel_index(np.argmax(evaluations), evaluations.shape)

    sign = np.array([1.0,1.0]) #登る方向
    climb = True
    if index_max[0] == 0:
        sign[0] = -1.0
        if index_max[1] == 0:
            sign[1] = -1.0
        elif index_max[1] == 2:
            sign[1] = 1.0
        else:
            sign[1] = 0.0
    elif index_max[0] == 2:
        sign[0] = 1.0
        if index_max[1] == 0:
            sign[1] = -1.0
        elif index_max[1] == 2:
            sign[1] = 1.0
        else:
            sign[1] = 0.0
    else:
        sign[0] = 0.0
        if index_max[1] == 0:
            sign[1] = -1.0
        elif index_max[1] == 2:
            sign[1] = 1.0
        else:
            climb = False

    
    x = x0 + np.array([sign[0]*delta,sign[1]*delta])
    fx = evaluations[index_max]
    fbest = fx
    while climb == True:
        points.append(x)
        fvalues.append(fx)

        x = x + np.array([sign[0]*delta,sign[1]*delta])
        fx = f(*x)
        if fx > fbest and (all(x <= x_max) and all(x >= x_min)):
            fbest = fx
            fi.write("f({}): {}\n".format(x, fx))
        else:
            climb = False

    return points, fvalues


# 関数を選ぶ
f = sin_2v
# f = p3d_2v
# 変数の範囲を設定
x_min = np.array([0,0])
x_max = np.array([np.pi, np.pi])
# 探索の出発点
x0 = np.array([0.6,0.6])  # x_min < x0 < x_max
# 探索方向を決定するための間隔
delta = 0.01
# 山のりを呼び出す
points, fvalues = hill_climbing(f, x0, delta, x_min, x_max) 
# points = np.array(points)
# fvalues = np.array(fvalues)
# # 関数をプロットする
# x = np.arange(x_min, x_max, 0.01)
# plt.plot(x, f(x))
# # 探索点をプロットする
# plt.plot(points, fvalues, 'ro')
# plt.plot(points[0], fvalues[0], 'bo')
# plt.plot(points[len(points)-1], fvalues[len(fvalues)-1], 'ko')  
# plt.xlabel("x")
# plt.ylabel("f(x)")
# # plt.legend(['関数','探索された x','探索の出発点','最高の探索点']) 
# plt.legend(['function', 'searched $x$', 'starting $x_0$', 'best $x$'])
# dirname = "C://Program_Code/LaTeX/OPT/class2/"
# filename = dirname + "hillclimib_p3d_" + str(x_min) + "_" + str(x_max) + "_" + str(delta) + "_" + str(x0) + ".png"
# plt.savefig(filename)
# plt.show()
