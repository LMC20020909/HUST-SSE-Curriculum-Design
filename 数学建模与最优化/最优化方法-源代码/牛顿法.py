import numpy as np


def fun(x):  # 4(x1^2-x2)^2+3(x1-1)^2
    return x[0] ** 2 + 4 * x[1] ** 2


def gfun(x):  # f(x)梯度函数
    return np.array([2 * x[0], 8 * x[1]])


def Gfun(x):  # f(x)的Heese矩阵
    return np.array([[2, 0], [0, 8]], dtype=float)


def Newton(x0, eps=10 ** (-6)):  # 基本牛顿法
    xk, count = x0, 0
    while np.linalg.norm(gfun(xk)) > eps:
        count += 1  # 迭代次数统计
        gk = gfun(xk)
        Gk = Gfun(xk)
        dk = -np.linalg.inv(Gk) @ gk
        xk = xk + dk
    return xk, count


if __name__ == '__main__':
    x0 = np.array([[1], [1]])
    x = Newton(x0)
    print('牛顿法:', '极小值点:', x[0].T, '极小值:', fun(x[0]), '迭代次数:', x[1])
