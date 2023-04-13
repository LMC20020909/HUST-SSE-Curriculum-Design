import cv2
import numpy as np
import math
from matplotlib import pyplot as plt


def rgbtohsi(rgb_img):
    rows = int(rgb_img.shape[0])
    cols = int(rgb_img.shape[1])
    b, g, r = cv2.split(rgb_img)
    # 归一化到[0,1]
    b = b / 255.0
    g = g / 255.0
    r = r / 255.0
    hsi_tmpimg = rgb_img.copy()
    H, S, I = cv2.split(hsi_tmpimg)
    for i in range(rows):
        for j in range(cols):
            num = 0.5 * ((r[i, j] - g[i, j]) + (r[i, j] - b[i, j]))
            den = np.sqrt((r[i, j] - g[i, j]) ** 2 + (r[i, j] - b[i, j]) * (g[i, j] - b[i, j]))
            theta = float(np.arccos(num / den))

            if den == 0:
                H = 0
            elif b[i, j] <= g[i, j]:
                H = theta
            else:
                H = 2 * math.pi - theta

            min_RGB = min(min(b[i, j], g[i, j]), r[i, j])
            sum = b[i, j] + g[i, j] + r[i, j]
            if sum == 0:
                S = 0
            else:
                S = 1 - 3 * min_RGB / sum

            # H = H / (2 * math.pi)
            I = sum / 3.0
            # 输出HSI图像，扩充到255以方便显示，一般H分量在[0,2pi]之间，S和I在[0,1]之间
            hsi_tmpimg[i, j, 0] = H * 255
            hsi_tmpimg[i, j, 1] = S * 255
            hsi_tmpimg[i, j, 2] = I * 255
    return hsi_tmpimg


def hsitobgr(hsi_img):
    rows = int(hsi_img.shape[0])
    cols = int(hsi_img.shape[1])
    hh, ss, ii = cv2.split(hsi_img)
    hh = hh / 255.0
    ss = ss / 255.0
    ii = ii / 255.0
    rgb_tmpimg = hsi_img.copy()
    B, G, R = cv2.split(rgb_tmpimg)
    for i in range(rows):
        for j in range(cols):
            if hh[i, j] < 2 / 3.0 * math.pi:
                R = ii[i, j] * (1 + ss[i, j] * np.cos(hh[i, j]) / np.cos(1 / 3.0 * math.pi - hh[i, j]))
                B = ii[i, j] * (1 - ss[i, j])
                G = 3 * ii[i, j] - (B+R)
            elif hh[i, j] < 4 / 3.0 * math.pi:
                R = ii[i, j] * (1 - ss[i, j])
                G = ii(i, j) * (1 + ss[i, j] * np.cos(hh[i, j] - 2/3.0 * math.pi) / np.cos(math.pi - hh[i, j]))
                B = 3 * ii[i, j] - (G+R)
            elif hh[i, j] < 2 * math.pi:
                B = ii[i, j] * (1 + ss[i, j] * np.cos(hh[i, j] - 4/3.0 * math.pi) / np.cos(300/180.0 * math.pi - hh[i, j]))
                G = ii[i, j] * (1 - ss[i, j])
                R = 3 * ii[i, j] - (B+G)
            rgb_tmpimg[i, j, 0] = B * 255
            rgb_tmpimg[i, j, 1] = G * 255
            rgb_tmpimg[i, j, 2] = R * 255
    return rgb_tmpimg


if __name__ == '__main__':
    rgb_img = cv2.imread("Fig6.png")
    hsv_img = cv2.cvtColor(rgb_img, cv2.COLOR_BGR2HSV)
    cv2.imshow("hsv", hsv_img)
    h, s, v = cv2.split(hsv_img)
    equ = cv2.equalizeHist(v)
    res_img = cv2.merge([h, s, equ])
    cv2.imshow("hsv_equ", res_img)
    ans_img = cv2.cvtColor(res_img, cv2.COLOR_HSV2BGR)
    cv2.imshow("original", rgb_img)
    cv2.imshow("ans", ans_img)
    cv2.imwrite("Fig6_output.jpg", ans_img)
    # hsi_img = rgbtohsi(rgb_img)
    #
    # cv2.imshow('rgb_lwpImg', rgb_img)
    # cv2.imshow('hsi_lwpImg', hsi_img)
    # h, s, i = cv2.split(hsi_img)
    # equ = cv2.equalizeHist(i)
    # res_img = cv2.merge([h, s, equ])
    # cv2.imshow('res_img', res_img)
    # ans = hsitobgr(res_img)
    # cv2.imshow("ans", ans)
    key = cv2.waitKey(0) & 0xFF
    if key == ord('q'):
        cv2.destroyAllWindows()
