#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 22 14:03:55 2020

@author: hernan
"""
import pandas as pd
import matplotlib.pyplot as plt


data_root_fname = "data_poly_3"

de = pd.read_csv("../results/out_"+data_root_fname+"_train.txt", header=None)
de = de[0].str.split('\t', expand=True)
de[1]=pd.to_numeric(de[1])
de[2]=pd.to_numeric(de[2])

#model = ' + '.join(list(de.iloc[0,2:]))

dr = pd.read_csv("../data/"+data_root_fname+".txt", sep=" ", header=None)#
n_models=11
for k in range(1,n_models+1):
    fn = "mk"+str(k)+"_est_"+data_root_fname+"_train.txt"
    dn = pd.read_csv("../results/"+fn, sep="\t", header=None)#
    
    error = str(de.iloc[k-1,1])

    plt.figure()
    plt.plot(dr[0],dr[1], 'ob')
    plt.plot(dn[0],dn[1], '-r')
    plt.title(fn + "\n  error  = " + str(error))
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend([data_root_fname,fn])
    plt.savefig("../results/fig"+fn+".pdf")
    plt.show()



plt.figure()
plt.plot(de[0],list(de[:n_models][1]), '-ob')
plt.plot(de[0],de[:n_models][2], '-or')
plt.xlabel('model')
plt.ylabel('error')
plt.xticks(de[0])
plt.legend(["train","test"])
plt.savefig("../results/models_error.pdf")


