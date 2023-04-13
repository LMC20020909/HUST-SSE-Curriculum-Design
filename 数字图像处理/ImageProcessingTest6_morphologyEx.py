import cv2
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    img = cv2.imread('j.png', 0)
    img_open = cv2.imread('j_erosion.png', 0)
    img_close = cv2.imread('j_dilation.png', 0)
    kernel = np.ones((5, 5), np.uint8)
    opening = cv2.morphologyEx(img_open, cv2.MORPH_OPEN, kernel)
    closing = cv2.morphologyEx(img_close, cv2.MORPH_CLOSE, kernel)
    gradient = cv2.morphologyEx(img, cv2.MORPH_GRADIENT, kernel)
    plt.subplot(321), plt.imshow(img_open, cmap='gray'), plt.title('open_original'), plt.xticks([]), plt.yticks([])
    plt.subplot(322), plt.imshow(opening, cmap='gray'), plt.title('opening'), plt.xticks([]), plt.yticks([])
    plt.subplot(323), plt.imshow(img_close, cmap='gray'), plt.title('close_original'), plt.xticks([]), plt.yticks([])
    plt.subplot(324), plt.imshow(closing, cmap='gray'), plt.title('closing'), plt.xticks([]), plt.yticks([])
    plt.subplot(325), plt.imshow(img, cmap='gray'), plt.title('original'), plt.xticks([]), plt.yticks([])
    plt.subplot(326), plt.imshow(gradient, cmap='gray'), plt.title('gradient'), plt.xticks([]), plt.yticks([])
    plt.show()
