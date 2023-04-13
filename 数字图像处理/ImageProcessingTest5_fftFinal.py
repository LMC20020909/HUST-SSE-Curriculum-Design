import cv2
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    index = 30
    thre = 10
    img_ori = cv2.imread('test.png')
    img = cv2.cvtColor(img_ori, cv2.COLOR_BGR2GRAY)
    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    rows, cols = fshift.shape
    rrow = rows // 2
    ccol = cols // 2
    # 高通
    mask1 = np.ones((rows, cols), np.uint8)
    mask1[rrow - index: rrow + index, ccol - index: ccol + index] = 0
    # 带通
    mask2 = np.zeros((rows, cols), np.uint8)
    mask2[rrow - index: rrow + index, ccol - index: ccol + index] = 1
    mask2[rrow - thre: rrow + thre, ccol - thre: ccol + thre] = 0
    # 低通
    mask3 = np.zeros((rows, cols), np.uint8)
    mask3[rrow - index: rrow + index, ccol - index: ccol + index] = 1
    f1 = fshift * mask1
    f2 = fshift * mask2
    f3 = fshift * mask3
    f_ishift1 = np.fft.ifftshift(f1)
    f_ishift2 = np.fft.ifftshift(f2)
    f_ishift3 = np.fft.ifftshift(f3)
    HPF = np.abs(np.fft.ifft2(f_ishift1))
    BPF = np.abs(np.fft.ifft2(f_ishift2))
    LPF = np.abs(np.fft.ifft2(f_ishift3))
    # plt.subplot(321), plt.imshow(img, cmap='gray'), plt.title('Original'), plt.xticks([]), plt.yticks([])
    plt.subplot(331), plt.imshow(HPF, cmap='gray'), plt.title('HPF'), plt.xticks([]), plt.yticks([])
    plt.subplot(332), plt.imshow(BPF), plt.title('BPF'), plt.xticks([]), plt.yticks([])
    plt.subplot(333), plt.imshow(LPF, cmap='gray'), plt.title('LPF'), plt.xticks([]), plt.yticks([])
    # rgb
    ans_img = cv2.merge([HPF, BPF, LPF])
    plt.subplot(334), plt.imshow(ans_img.astype('uint8')), plt.title('HBL'), plt.xticks([]), plt.yticks([])
    ans_img = cv2.merge([HPF, LPF, BPF])
    plt.subplot(335), plt.imshow(ans_img.astype('uint8')), plt.title('HLB'), plt.xticks([]), plt.yticks([])
    ans_img = cv2.merge([BPF, HPF, LPF])
    plt.subplot(336), plt.imshow(ans_img.astype('uint8')), plt.title('BHL'), plt.xticks([]), plt.yticks([])
    ans_img = cv2.merge([BPF, LPF, HPF])
    plt.subplot(337), plt.imshow(ans_img.astype('uint8')), plt.title('BLH'), plt.xticks([]), plt.yticks([])
    ans_img = cv2.merge([LPF, BPF, HPF])
    plt.subplot(338), plt.imshow(ans_img.astype('uint8')), plt.title('LBH'), plt.xticks([]), plt.yticks([])
    ans_img = cv2.merge([LPF, HPF, BPF])
    plt.subplot(339), plt.imshow(ans_img.astype('uint8')), plt.title('LHB'), plt.xticks([]), plt.yticks([])
    plt.show()

