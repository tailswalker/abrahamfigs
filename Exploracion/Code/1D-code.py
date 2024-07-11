#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import pandas
from math import floor

from matplotlib import animation
from IPython.display import HTML
plt.rcParams['figure.dpi'] = 80

import subprocess 
import os

path = "/home/muon02/Documents/Tesis/lgca_1d/build/"

def extrac_info(document):
    # Input
    data_file = path+document

    # Delimiter
    data_file_delimiter = ' '

    # The max column count a line in the file could have
    largest_column_count = 0

    # Loop the data lines
    with open(data_file, 'r') as temp_f:
        # Read the lines
        lines = temp_f.readlines()

        for l in lines:
            # Count the column count for the current line
            column_count = len(l.split(data_file_delimiter)) + 1
        
            # Set the new most column count
            largest_column_count = column_count if largest_column_count < column_count else largest_column_count

    # Generate column names (will be 0, 1, 2, ..., largest_column_count - 1)
    column_names = [i for i in range(0, largest_column_count)]

    # Read csv
    df = pandas.read_csv(data_file, header=None, delimiter=data_file_delimiter, names=column_names)
    # print(df)
    df = df.fillna(0)
    df.drop(df.columns[-1], axis=1, inplace=True)
    return df

# parametros generales
nu = 0.7
alpha = 2
d = 0.05

def make_info(N_s, N_t, p_sym,time=30001):
    data_par_terminal = str(N_s) + " " + str(N_t) 
    data_par_terminal = data_par_terminal + " " + str(nu) + " " + str(alpha)
    data_par_terminal = data_par_terminal + " " + str(p_sym) + " " + str(d) 
    data_par_terminal = data_par_terminal + " " + str(time)
    subprocess.run("cd "+path+" && ./lgca 100 "+data_par_terminal, capture_output=True, shell=True)


    cellsCSC = extrac_info("ydataS"+str(N_s)+str(N_t)+str(floor(p_sym*10))+".csv")
    cellsTD = extrac_info("ydataT"+str(N_s)+str(N_t)+str(floor(p_sym*10))+".csv")

    os.remove(path+"ydataS"+str(N_s)+str(N_t)+str(floor(p_sym*10))+".csv")
    os.remove(path+"ydataT"+str(N_s)+str(N_t)+str(floor(p_sym*10))+".csv")
    
    return (cellsCSC,cellsTD)

N_sS = 40
N_tS = 20

p_asymmas = 0.7

cellsCSC_I,cellsTD_I = make_info(N_sS, N_tS, p_asymmas)

ylim = max(cellsCSC_I.values.max(),cellsTD_I.values.max())

fig, ax = plt.subplots()
ax.set(xlabel='Column', ylabel='Cells',
       title=r'Y-density ($b_S$='+str(N_sS)+', $b_T$='+str(N_tS)+' )', xlim=[0,100],ylim=[0,ylim])
ax.grid()
line1, = ax.plot([],[],'b-',label="CSC")
line2, = ax.plot([],[],'r-',label="TD")
plt.legend(loc="upper right")
def drawframe(n):
    line1.set_data(range(100),cellsCSC_I.iloc[n*200,0:100])
    line2.set_data(range(100),cellsTD_I.iloc[n*200,0:100])
    return (line1,line2)
anim = animation.FuncAnimation(fig, drawframe,
                               frames=range(60),blit=True)

plt.show()

