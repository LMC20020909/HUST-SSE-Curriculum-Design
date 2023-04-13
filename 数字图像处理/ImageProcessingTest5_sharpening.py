import cv2
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    img = cv2.imread('moon.jpg', 0)
    laplacian = cv2.Laplacian(img, cv2.CV_64F, ksize=3)
    # print(laplacian[250:260, 230:240])
    img = img.astype("float64")
    print(laplacian)
    la = cv2.subtract(img, laplacian)
    for i in range(0,la.shape[0]):
        for j in range(0, la.shape[1]):
            la[i,j] = max(0, la[i,j])
    sobelx = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=5)
    sobely = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=5)
    plt.subplot(2, 2, 1), plt.imshow(img, cmap='gray'), plt.title('Original'), plt.xticks([]), plt.yticks([])
    plt.subplot(2, 2, 2), plt.imshow(laplacian, cmap='gray'), plt.title('Laplacian'), plt.xticks([]), plt.yticks([])
    plt.subplot(2, 2, 3), plt.imshow(la, cmap='gray'), plt.title('Sobel X'), plt.xticks([]), plt.yticks([])
    plt.subplot(2, 2, 4), plt.imshow(sobely, cmap='gray'), plt.title('Sobel Y'), plt.xticks([]), plt.yticks([])
    plt.show()
