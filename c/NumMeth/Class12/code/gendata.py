#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jul 24 12:27:11 2022

@author: hernan
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import pandas as pd
 
fname ="data_poly_3"

np.random.seed(0)
n = 200
a = 2
b = 3
x = a - b * np.random.normal(0, 1, n)
y = x - 2 * (x ** 2) + 0.25 * (x ** 3) + 2.5*np.random.normal(-3, 3, n)
plt.scatter(x,y, s=10)
plt.show()

x_train, x_test, y_train, y_test = train_test_split( x, y, test_size=0.8, 
                                                          random_state=3)    

plt.scatter(x_train,y_train, s=10)
plt.scatter(x_test,y_test, s=10)
plt.show()

# create an Empty DataFrame object
df = pd.DataFrame()
df['x']=x
df['y']=y

df = df.sort_values(by=['x'], ascending=True)

df_train = pd.DataFrame()
df_train['x']=x_train
df_train['y']=y_train

df_test = pd.DataFrame()
df_test['x']=x_test
df_test['y']=y_test

(df.sort_values(by=['x'], ascending=True)).to_csv(fname+".txt", sep=' ', header=False, index=False)
(df_train.sort_values(by=['x'], ascending=True)).to_csv(fname+"_train.txt", sep=' ', header=[str(df_train.shape[0]),''], index=False)
(df_test.sort_values(by=['x'], ascending=True)).to_csv(fname+"_test.txt", sep=' ', header=[str(df_test.shape[0]),''], index=False)
