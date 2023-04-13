# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 19:54:22 2022

@author: 86182
"""
import cv2


def mix():
    img1 = cv2.imread('flower2.jpg')
    img2 = cv2.imread('diamond2.jpg')

    # dst = a * img1 + b * img2 + c
    dst = cv2.addWeighted(img1, 0.7, img2, 0.3, 0)
    cv2.namedWindow('dst')
    cv2.imshow('dst', dst)
    k = cv2.waitKey(0) & 0xFF
    if k == 27:
        cv2.destroyAllWindows()


if __name__ == '__main__':
    mix()