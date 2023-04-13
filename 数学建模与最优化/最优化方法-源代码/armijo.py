import numpy as np
from funx import fun,gfun

def armijo(x0,dk,beta=0.5,sigma=0.2):
    xk,m,count = x0,0,0
    while m<20:
        if fun(xk+beta**m*dk) <= fun(xk)+sigma*beta**m*np.matmul(gfun(xk).T,dk):
            break
        m += 1
    alpha = beta**m
    return alpha