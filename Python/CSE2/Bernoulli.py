import numpy as np
import matplotlib.pyplot as plt
import random

LOOP = 10 ** 6
P = 0.1
counter = []

for i in range(LOOP):
    count = 1
    while random.random() > P:
        count += 1
    counter.append(count)

hlist = np.histogram(counter, range=(1,50), bins=49, density=False)
# print(hlist[0]) #各到着間隔の個数リスト
# plt.figure()
# plt.hist(counter, range=(0, 50), bins=50) #到着間隔のヒストグラム
# print(hlist[0]/LOOP) #hlistを相対度数(確率)に計算したやつ
plt.figure()
plt.xlabel('Arrival Interval')
plt.bar(np.arange(1,50), hlist[0]/LOOP, width=1.0) # 相対度数のヒストグラム
plt.show()