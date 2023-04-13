import cv2
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    index = 30
    img = cv2.imread("messigray.png", 0)
    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    # plt.plot(np.log(np.abs(fshift)))
    # plt.show()
    rows, cols = fshift.shape
    rrow = rows // 2
    ccol = cols // 2
    mask = np.zeros((rows, cols), np.uint8)
    mask[rrow - index: rrow + index, ccol - index: ccol + index] = 1
    f_res = fshift * mask
    f_ishift = np.fft.ifftshift(f_res)
    img_back = np.fft.ifft2(f_ishift)
    img_back = np.abs(img_back)
    plt.subplot(121), plt.imshow(img, cmap='gray'), plt.title('Original'), plt.xticks([]), plt.yticks([])
    plt.subplot(122), plt.imshow(img_back, cmap='gray'), plt.title('LPF'), plt.xticks([]), plt.yticks([])
    plt.show()
