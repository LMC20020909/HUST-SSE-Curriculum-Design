import numpy as np
import sympy
from sympy.abc import alpha
from funx import fun,gfun
from armijo import armijo

def line_search(xk,dk):  # 精确线搜索
    alphak = None
    eq = np.dot(gfun(xk+alpha*dk).T,dk)[0]
    alpha0 = sympy.solve(eq,[alpha])
    if len(alpha0) > 1:
        for a in alpha0:
            a = a[0]
            try:
                if fun(xk + float(a) * dk) < fun(xk):
                    alphak = float(a)
                    break
            except TypeError:
                continue
    else:
        alphak = float(alpha0[alpha])

    if alphak is None:  # 精准线搜索失效，手动选取步长因子alphak
        alphak = 0.01
        print('精准线搜索失效，使用固定步长法')
    return alphak

def Min(x0,cho=1,eps=10**(-5)):  # 核心函数
    xk = x0
    count = 0
    while np.linalg.norm(gfun(xk)) > eps:  # 梯度导数的范数
        count += 1
        dk = -gfun(xk)
        if cho == 2:
            alpha = line_search(xk,dk)  # 精准线搜索步长
        elif cho == 3:
            alpha = armijo(xk,dk)  # 非精准线搜索步长
        else:
            alpha = 0.01
        xk = xk+alpha*dk
        # print('x_(k+1)点:',x_k1.T, ' 函数值:',fun(x_k1))
    return xk,count

if __name__ == '__main__':
    x0 = np.array([[0],[0]])
    x1 = Min(x0,1)  # 固定步长
    x2 = Min(x0,2)  # 精确线搜索
    x = Min(x0,3)  # 非精确线搜索
    print('固定步长法，近似极小值点',x1[0].T,'函数值:',fun(x1[0]),'迭代次数:',x1[1])
    print('精确线搜索，近似极小值点',x2[0].T,'函数值:',fun(x2[0]),'迭代次数:',x2[1])
    print('非精确线搜索，近似极小值点',x[0].T,'函数值:',fun(x[0]),'迭代次数:',x[1])
