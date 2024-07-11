#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Nov  7 22:27:27 2021

@author: muon02
"""

N_S = [i+4 for i in range(20)]

N_T = [i+4 for i in range(20)]

p = [ 0.250, 0.5, 0.750]

alpha = [0,1,2,3]#[i for i in range(3)]

sets_of_simulations = []

for ns in N_S:
    for nt in N_T:
        for pi in p:
            for alphai in alpha:
                sets_of_simulations.append([ns,nt,pi,alphai])

if __name__=='__main__':
    pass