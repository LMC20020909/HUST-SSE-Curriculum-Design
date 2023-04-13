import cv2
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    # img = cv2.imread('Fig3.jpg', 0)
    # plt.hist(img.ravel(), 256, [0, 256])
    # plt.show()
    img = cv2.imread('Fig3.jpg')
    color = ('b', 'g', 'r')
    # 对一个列表或数组既要遍历索引又要遍历元素时
    # 使用内置enumerate 函数会有更加直接，优美的做法
    # enumerate 会将数组或列表组成一个索引序列。
    # 使我们再获取索引和索引内容的时候更加方便
    for i, col in enumerate(color):
        hist = cv2.calcHist([img], [i], None, [256], [0, 256])
        plt.plot(hist, color=col)
        plt.xlim([0, 256])
    plt.show()

