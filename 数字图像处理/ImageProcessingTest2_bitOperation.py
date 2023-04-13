# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 20:27:29 2022

@author: 86182
"""
import cv2


def bit_operation():
    # 加载图像
    img1 = cv2.imread('1.jpg')
    img2 = cv2.imread('hustlogo.bmp')
    # I want to put logo on top-left corner, So I create a ROI
    rows, cols, channels = img2.shape
    roi = img1[0:rows, 0:cols]
    # Now create a mask of logo and create its inverse mask also
    img2gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    ret, mask_front = cv2.threshold(img2gray, 175, 255, cv2.THRESH_BINARY)  # 这是图像分割方法，后面讲到。
    mask_inv = cv2.bitwise_not(mask_front)
    # Now black-out the area of logo in ROI
    # 取roi 中与mask 中不为零的值对应的像素的值，其他值为0
    # 注意这里必须有mask=mask 或者mask=mask_inv, 其中的“mask=” 不能忽略
    # cv2.imshow('mask_front', mask_front)
    # 将roi中在mask中的对应点为黑的像素赋0，白的保留原值不变
    img1_bg = cv2.bitwise_and(roi, roi, mask=mask_front)
    # 取roi 中与mask_inv 中不为零的值对应的像素的值，其他值为0。
    # Take only region of logo from logo image.
    # cv2.imshow('mask_inv', mask_inv)
    img2_fg = cv2.bitwise_and(img2, img2, mask=mask_inv)
    # Put logo in ROI and modify the main image
    dst = cv2.add(img1_bg, img2_fg)
    img1[0:rows, 0:cols] = dst
    cv2.imshow('img1_bg', img1_bg)
    cv2.imshow('img2_fg', img2_fg)
    cv2.imshow('res', img1)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    bit_operation()
