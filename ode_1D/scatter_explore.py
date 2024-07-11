#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 10 16:29:24 2021

@author: muon02
"""


import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

info = pd.read_csv('/home/muon02/Documents/Tesis/ode_1D/output/nov10/info2.csv')

sns.set_theme(style="white")

# Load the example mpg dataset
mpg = sns.load_dataset("mpg")

case1 = info[(info["alpha"]==1)&(info["p"]==0.25)].pivot("NS","NT","frontCSC")
case2 = info[(info["alpha"]==1)&(info["p"]==0.5)].pivot("NS","NT","frontCSC")
case3 = info[(info["alpha"]==1)&(info["p"]==0.75)].pivot("NS","NT","frontCSC")

fig, axs = plt.subplots(ncols=3)

sns.heatmap(case1, annot=True, fmt="d", cbar=False, ax=axs[0],vmin=0,vmax=200)
sns.heatmap(case2, annot=True, fmt="d", yticklabels=False, cbar=False, ax=axs[1],vmin=0,vmax=200)
sns.heatmap(case3, annot=True, fmt="d", yticklabels=False, cbar=False, ax=axs[2],vmin=0,vmax=200)

for k in range(3):
    axs[k].set_ylabel("")
    axs[k].set_xlabel("")

axs[0].set_ylabel(r"$N_{CSC}$")
axs[1].set_xlabel(r"$N_{TD}$")

axs[0].set_title(r"$\bar{p}=0.25$")
axs[1].set_title(r"$\bar{p}=0.50$")
axs[2].set_title(r"$\bar{p}=0.75$")

plt.show()
# Plot miles per gallon against horsepower with other semantics
# g = sns.relplot(x="NS", 
#             y="NT", 
#             size="frontCSC",
#             sizes=(40, 400), 
#             palette="muted",
#             height=6, 
#             data=info[(info["alpha"]==3)&(info["p"]==0.5)],
#             legend=False)

# plt.xticks([10,20,30,40])
# plt.yticks([10,20,30,40])
# plt.xlabel(r'$N_{CSC}$')
# plt.ylabel(r'$N_{TD}$')

#print(info[(info["alpha"]==3)&(info["p"]==0.5)][["NS","NT","frontCSC"]])

#sns.heatmap(case1, annot=True, cbar=False)
