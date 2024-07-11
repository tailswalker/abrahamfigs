#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Nov  8 16:03:23 2021

@author: muon02
"""
import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
from matplotlib import animation

import pandas as pd


import ode_1D
import set_experiments

set_of_results = []

t = np.linspace(0, 5000, 50001)
y0 = np.zeros(1000)
y0[:5] = 10*np.ones(5)

nu = 0.9
d = 0.5
h = 1

new_set = set_experiments.sets_of_simulations.copy()

for k in range(len(set_experiments.sets_of_simulations)):
    parameters = set_experiments.sets_of_simulations[k]
    N_S = parameters[0]
    N_T = parameters[1]
    p = parameters[2]
    alpha = parameters[3]
    sol = odeint(ode_1D.dPdt, y0, t, args=(N_S,N_T,p,alpha,nu,d,h))
    
    new_set[k].append( #Last front mark CSC
        ode_1D.first_greater_than_one(sol[-1,:int(sol.shape[1]/2)])
        )
    new_set[k].append( #Last front mark CSC
        ode_1D.first_greater_than_one(sol[-1,int(sol.shape[1]/2):])
        )
    new_set[k].append( #Mean of CSC
        np.mean(sol[-1,:int(sol.shape[1]/2)])
        )
    new_set[k].append( #Mean of TD
        np.mean(sol[-1,int(sol.shape[1]/2):])
        )
    new_set[k].append( #Proportion at the begining
        sol[-1,0]-sol[-1,int(sol.shape[1]/2)]    
        )
    
    # ode_1D.create_anim(sol, "python"+str(N_S)+str(N_T)+
    #                    str(int(100*p))+str(alpha))
    print("Listo: ",parameters, "'\n")
    
data = pd.DataFrame(new_set, columns=['NS','NT','p','alpha','frontCSC','frontTD','meanCSC','meanTD','Dif_at_0'])

data.to_csv("big_info.csv")
