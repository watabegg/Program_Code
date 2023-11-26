import numpy as np
import matplotlib.pyplot as plt
import random as rand

LOOP = 10 ** 6
lam_1 = 2 # バスの到着間隔 単位時間にlam_1台
lam_2 = 5 # 乗客の到着間隔 単位時間にlam_2人

cus_list = [] # 各バスに乗る乗客の人数
time_list = [] # すべての乗客がバスを待つ時間

bus_delta = (-np.log(1-rand.random()))/lam_1
# バスの到着間隔のリスト
cus_del_sum = (-np.log(1-rand.random()))/lam_2 # 乗客の到着間隔

for i in range(LOOP):
    cus_sum = 0 # 乗客の合計
    while(cus_del_sum < bus_delta): 
        # 乗客の到着間隔の合計がバスの到着間隔を超えるまで
        cus_sum += 1 # バスの乗客を1人追加
        time_list.append(bus_delta - cus_del_sum) # 待ち時間をリストに追加
        cus_del_sum += (-np.log(1-rand.random()))/lam_2 # 乗客をもう一人並ばせる
    cus_list.append(cus_sum)
    bus_delta += (-np.log(1-rand.random()))/lam_1

pass_list = np.array([item for item in cus_list for _ in range(item)])

hlist = np.histogram(cus_list, range=(0,35), bins=35, density=False)
phlist = np.histogram(pass_list, range=(0,45), bins=45, density=False)
thlist = np.histogram(time_list, range=(0,4), bins=400, density=False)

print('単位時間に'+str(lam_1)+'台(λ₁)')
print('単位時間に'+str(lam_2)+'人(λ₂)')
print('乗客の平均:'+str(np.average(cus_list)))
print('同乗者の平均:'+str((sum(pass_list))/sum(cus_list)))
print('待ち時間の平均:'+str(np.average(time_list)))

plt.figure()
plt.xlabel('バスに乗る乗客(人)', fontname="MS Gothic")
plt.ylabel('相対度数', fontname="MS Gothic")
plt.bar(np.arange(0,35), hlist[0]/LOOP, width=1.0)
x = np.arange(0,35)
plt.plot(x, (lam_1/(lam_2))*np.exp(-(lam_1/(lam_2))*x), color='r')

# plt.figure()
# plt.xlabel('乗客から見た同乗者(人)', fontname="MS Gothic")
# plt.ylabel('相対度数', fontname="MS Gothic")
# plt.bar(np.arange(0,45), phlist[0]/LOOP, width=1.0) 

# plt.figure()
# plt.xlabel('乗客の待ち時間(時間)', fontname="MS Gothic")
# plt.ylabel('相対度数', fontname="MS Gothic")
# plt.bar(np.arange(0,4,0.01), thlist[0]/LOOP, width=0.01) 
plt.show()