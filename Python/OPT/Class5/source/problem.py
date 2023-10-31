#!/usr/bin/env python3
# -*- coding: utf-8 -*-
""" 
Created on Wed May 8 13:14:59 2019 
@author: hernan 
EA Seminar 
Problems classes and benchmark functions 
Single-objective 
- Knapsack Problem 
"""


class Knapsack:
    """ Knapsack Problem 
    Examples: 
    low-dimensional/f1_l-d_kp_10_269.txt 
    large_scale/knapPI_1_10000_1000_1.txt 
    File format 
    nitems capacity 
    p1 w1 
    p2 w2 
    ... 

    pi, profit of ith-item 
    wi, weight of i-th item 

    """

    def __init__(self, fname):
        """Constructor  
        Parameters 
        ---------- 
        fname: string 
        file name where the problem is described 
        """
        self.fname = fname
        fproblem = open(self.fname)
        line = (fproblem.readline()).split()
        self.nitems = int(line[0])
        self.capacity = int(line[1])
        self.profit = []
        self.weigth = []
        for i in range(self.nitems):
            line = (fproblem.readline()).split()
            self.profit.append(int(line[0]))
            self.weigth.append(int(line[1]))
        fproblem.close()

    def fitness(self, x):
        """Fitness function  
        Parameters 
        ---------- 
        x: list 
        Variables 
        
        Returns 
        ------- 
        Tuple  
        Fitness values 
        """
        f = 0
        for i in range(len(x)):
            f = f + self.profit[i]*x[i]
        g = 0
        for i in range(len(x)):
            g = g + self.weigth[i]*x[i]

        # penalization term if
        if g > self.capacity:
            f = -(g-self.capacity)
        return f,