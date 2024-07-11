#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
from matplotlib import animation

path = '/home/muon02/Documents/Tesis/ode_1D/output/dic4/'


def dPdt(P,t,N_S,N_T,p,alpha,nu,d,h):
    n = P.shape[0] #length of the system
    dρdt = np.zeros(n)
    for i in range(int(n/2)):
        i_csc = i
        i_td = i + int(n/2)
        ρS, ρT = P[[i_csc,i_td]].copy()
        N = min(N_S,N_T)
        pMUT = p*(1-ρT/N)**alpha
        excludS = (N-ρS)/N
        excludT = (N-ρT)*(N-(ρT+1))/(N*(N-1))
        if i_csc==0:
            difussion_csc = (P[i_csc+1]-P[i_csc])/(h**2) #cs neumman fronteier
            difussion_td = (P[i_td+1]-P[i_td])/(h**2)
        elif i_td == (n-1):
            difussion_csc = (P[i_csc-1]-2*P[i_csc])/(h**2) #cs frozen fronteier (as a cliff)
            difussion_td = (P[i_td-1]-2*P[i_td])/(h**2)
        else:
            difussion_csc = (P[i_csc-1]+P[i_csc+1]-2*P[i_csc])/(h**2) #cs frozen fronteier (as a cliff)
            difussion_td = (P[i_td-1]+P[i_td+1]-2*P[i_td])/(h**2)
        dρdt[i_csc] = (1/N_S)*difussion_csc+(1/N)*nu*(ρS/N)*excludS*pMUT-(1/N)*nu*(ρS/N)*(1-pMUT)*excludT
        dρdt[i_td] = (1/N_T)*difussion_td+2*(1/N)*nu*(ρS/N)*excludT*(1-pMUT)-(1/N)*d*(ρT/N)
    return dρdt

def create_anim(SolutionODE, saveanimname = 'foo'):
    numberofnodes = int(SolutionODE.shape[1]/2)
    cellsCSC_I = SolutionODE[:,:numberofnodes]
    cellsTD_I = SolutionODE[:,numberofnodes:]
    ylim = max(cellsCSC_I.max(),cellsTD_I.max())
    
    fig, ax = plt.subplots()
    ax.set(xlabel='Column', ylabel='Cells',
        xlim=[0,100],ylim=[0,ylim])
    ax.grid()
    line1, = ax.plot([],[],'b-',label="CSC")
    line2, = ax.plot([],[],'r-',label="TD")
    ax.axhline(1, color='green')
    plt.legend(loc="upper right")
    def drawframe(n):
        line1.set_data(range(400),cellsCSC_I[n*250,0:400])
        line2.set_data(range(400),cellsTD_I[n*250,0:400])
        return (line1,line2,)
    anim = animation.FuncAnimation(fig, drawframe,
                               frames=range(200),blit=True)
    anim.save(path+saveanimname+'.gif',fps=15)
    
def first_greater_than_one(array):
    return array[array>1].shape[0]
        
#%%

if __name__=='__main__':
    
    t = np.linspace(0, 5000, 50001)
    N_S = 100
    N_T = 10
    p = 0.75
    alpha = 1
    nu = 0.9
    d = 0.5
    h = 1
    y0 = np.zeros(1000)
    y0[:5] = 10*np.ones(5)
    sol = odeint(dPdt, y0, t, args=(N_S,N_T,p,alpha,nu,d,h))
    
    # plt.plot(sol[-1,:int(len(y0)/2)], color='blue')
    # plt.plot(sol[-1,int(len(y0)/2):], color='red')
    # plt.hlines(first_greater_than_one(sol[-1,:int(len(y0)/2)]),
    #            xmin=0, xmax=sol[-1,:int(len(y0)/2)].shape[0],
    #            color='green'
    #            )
    # plt.hlines(first_greater_than_one(sol[-1,int(len(y0)/2):]),
    #            xmin=0, xmax=sol[-1,:int(len(y0)/2)].shape[0],
    #            color='orange'
    #            )
    # plt.xlabel("pasos k")
    # plt.show()
    
    #print(first_greater_than_one(sol[-1,:int(sol.shape[1]/2)]))
    
    #create_anim(sol, "pythonDtmasqueDs")
    
    #%%
    
    numberofnodes = int(sol.shape[1]/2)
    cellsCSC_I = sol[:,:numberofnodes]
    cellsTD_I = sol[:,numberofnodes:]
    ylim = max(cellsCSC_I.max(),cellsTD_I.max())
    
    fig, axs = plt.subplots(nrows=2, ncols=3, constrained_layout=True)
    k=0
    caso_inicial = 100
    step=1200
    for ax in axs.reshape(-1):
        ax.set(xlim=[0,100],ylim=[0,ylim], title='Tiempo='+str(caso_inicial + k*step))
        ax.grid()
        ax.plot(range(400),cellsCSC_I[caso_inicial +k*step,0:400],'b-',label="CSC")
        ax.plot(range(400),cellsTD_I[caso_inicial +k*step,0:400],'r-',label="TD")
        ax.axhline(1, color='green')
        k+=1
    lg = plt.legend(bbox_to_anchor=(1,1), loc="center left")
    plt.savefig(path+'casoExplor.png',
                bbox_extra_artists=(lg,)
            )
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    