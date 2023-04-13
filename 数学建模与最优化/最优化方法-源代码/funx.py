import numpy as np
from matplotlib import pyplot as plot
from mpl_toolkits.mplot3d import Axes3D

def fun(x):  # 4(x1^2-x2)^2+3(x1-1)^2
    return 4*x[0]**4-8*x[0]**2*x[1]+4*x[1]**2+3*x[0]**2-6*x[0]+3

def gfun(x):  # f(x)梯度函数
    return np.array([16*x[0]**3-16*x[0]*x[1]+6*x[0]-6,-8*x[0]**2+8*x[1]])

def Gfun(x):  # f(x)的Heese矩阵
    return np.array([[48*x[0]**2-16*x[1]+6,-16*x[0]],[-16*x[0],8]],dtype=float)

def surface():  # 绘制三维图像
    figure = plot.figure()
    axes = Axes3D(figure)
    x1 = np.arange(-10,10,0.25);x2 = np.arange(-10,10,0.25)
    X1,X2 = np.meshgrid(x1,x2)
    Y = fun([X1,X2])
    axes.plot_surface(X1,X2,Y,cmap='rainbow')
    plot.show()

if __name__ == '__main__':
    surface()