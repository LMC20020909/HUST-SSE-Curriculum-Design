# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 20:11:14 2022

@author: 86182
"""
import cv2


def arithmetic():
    img = cv2.imread('woman.jpg', 0)
    img1 = cv2.add(img, 80)
    img2 = cv2.subtract(img, 80)
    img3 = cv2.multiply(img, 1.5)
    cv2.imshow('img', img)
    cv2.imshow('add', img1)
    cv2.imshow('subtract', img2)
    cv2.imshow('multiply', img3)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    arithmetic()
