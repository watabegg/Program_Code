#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 22 14:03:55 2020

@author: hernan
"""
import pandas as pd
import matplotlib.pyplot as plt


#元のデータファイル名
fname_datas = ["nh_fish.txt","nh_wine.txt"]

for fname_data in fname_datas:
    fm = "../results/out_"+fname_data #モデルの誤差, モデルの係数と基本関数
    # モデルをエラーごとに並べ替える
    column_names = [i for i in range(0, 5)]
    #df_m_sort = pd.read_csv(fm, sep="\t", header=None, names = column_names)
    #df_m_sort.sort_values(by=[1]) 

    #調べるモデル
    for model_number in range(1,6):

        fd = "../data/"+fname_data #データ
        fe = "../results/mk"+str(model_number)+"_est_"+fname_data #補完の結果

        #出力されたモデルを取得する
        df_m = pd.read_csv(fm, sep="\t", header=None, skiprows = model_number -1 , nrows = 1)
        error = str(df_m.iloc[0,1])
        model = ' + '.join(list(df_m.iloc[0,2:]))


        #元のデータを読み込む
        df_d = pd.read_csv(fd, sep="\t", header=None, skiprows=1)

        #補間されたデータを読み込む
        df_e = pd.read_csv(fe, sep="\t", header=None)#

        # 元のデータと補間されたデータをプロットする
        plt.figure()
        plt.plot(df_d[0],df_d[1], 'ob')
        plt.plot(df_e[0],df_e[1], '-r')
        plt.title(fname_data + "\n  error  = " + str(error))
        plt.xlabel('x')
        plt.ylabel('y')
        plt.legend(["Data", model])
        plt.savefig("plot_" + fname_data + ".png")
        plt.show()
