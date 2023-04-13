import cv2
import numpy
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    img = cv2.imread('lena.bmp')
    kernel = np.ones((5, 5), np.float32) / 25
    # ddepth是处理结果图像的图像深度，一般使用-1表示与原始图像使用相同的图像深度
    dst = cv2.filter2D(img, -1, kernel)
    plt.subplot(121)  # plt.subplot(1, 2, 1)
    plt.imshow(img)
    plt.title('Original')
    plt.xticks([])
    plt.yticks([])
    plt.subplot(122)    # plt.subplot(1, 2, 2)
    plt.imshow(dst)
    plt.title('Averaging')
    # xticks(ticks=None, labels=None, **kwargs)
    # ticks：x轴刻度位置的列表，若传入空列表，即不显示x轴
    # labels：放在指定刻度位置的标签文本。当ticks参数有输入值，该参数才能传入参数
    # **kwargs：文本属性用来控制标签文本的展示，例如字体大小、字体样式等
    plt.xticks([])
    plt.yticks([])
    plt.show()
