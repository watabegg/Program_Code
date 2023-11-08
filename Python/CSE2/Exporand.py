import numpy as np
import matplotlib.pyplot as plt
import random as rand
import itertools

LOOP = 10 ** 6
lamb = 1 #λの値，変更してもよい
maxnum = 15 #グラフの最大出力，λを変えたときに変えるかも

randnum = [(-np.log(1-rand.random()))/lamb for i in range(LOOP)] #指数分布に従う乱数のリスト

hlist = np.histogram(randnum, range=(0,maxnum), bins=maxnum * 10, density=False) #乱数を0.1ずつの区分に分けて個数を計算
#print(hlist[0]) #試しに出力

plt.figure() #相対頻度のグラブ
plt.hist(randnum, range=(0, maxnum), bins=maxnum * 10) 

#print(np.array(list(itertools.accumulate(hlist[0])))/LOOP) #試しに出力
print('平均:' + str(np.average(randnum))) #平均値出力
print('期待値:' + str(1/lamb)) #理論値平均値出力

x = np.arange(0,maxnum,0.1)
plt.figure() #累積相対度数のグラフ
plt.xlabel()
plt.ylabel()
plt.plot(x,1-np.exp(-lamb*x),color='r')
plt.bar(np.arange(0,maxnum,0.1), np.array(list(itertools.accumulate(hlist[0])))/LOOP, width=0.1) #hlistの累積和を計算してnumpyの配列に変更
plt.show()

