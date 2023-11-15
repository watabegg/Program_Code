import numpy as np
import matplotlib.pyplot as plt
import random as rand
import itertools

LOOP = 10 ** 6
lam_1 = 1 # バスの到着間隔 単位時間にlam_1台
lam_2 = 5 # 乗客の到着間隔 単位時間にlam_2人

cus_list = []
time_list = []

bus_delta = [(-np.log(1-rand.random()))/lam_1 for i in range(LOOP)] # バスの到着間隔
bus_delta_sum = list(itertools.accumulate(bus_delta))
cus_del_sum = (-np.log(1-rand.random()))/lam_2 # 乗客の到着間隔

for i in range(LOOP):
    cus_sum = 0 # 乗客の合計
    while(cus_del_sum < bus_delta_sum[i]): # 乗客の到着間隔の合計がバスの到着間隔を超えるまで
        cus_sum += 1
        time_list.append(bus_delta_sum[i] - cus_del_sum)
        cus_del_sum += (-np.log(1-rand.random()))/lam_2
    cus_list.append(cus_sum)

hlist = np.histogram(cus_list, range=(0,35), bins=35, density=False)

pass_list = np.array([item for item in cus_list for _ in range(item)])-1
phlist = np.histogram(pass_list, range=(0,35), bins=35, density=False)

thlist = np.histogram(time_list, range=(0,4), bins=400, density=False)

print('単位時間に'+str(lam_1)+'台')
print('単位時間に'+str(lam_2)+'人')
print('乗客の平均:'+str(np.average(cus_list)))
print('同乗者の平均:'+str((sum(pass_list))/sum(cus_list)))
print('待ち時間の平均:'+str(np.average(time_list)))

plt.figure()
plt.xlabel('cust num')
plt.bar(np.arange(0,35), hlist[0], width=1.0) # 相対度数のヒストグラム

plt.figure()
plt.xlabel('cust num')
plt.bar(np.arange(0,35), phlist[0], width=1.0) # 相対度数のヒストグラム

plt.figure()
plt.xlabel('cust num')
plt.bar(np.arange(0,4,0.01), thlist[0], width=0.01) # 相対度数のヒストグラム
plt.show()