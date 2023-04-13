import cv2
import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    img = cv2.imread('house.tif', 0)
    element = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
    dilate = cv2.dilate(img, element)
    erode = cv2.erode(img, element)
    result = cv2.absdiff(dilate, erode)
    retval, result = cv2.threshold(result, 40, 255, cv2.THRESH_BINARY)
    result = cv2.bitwise_not(result)
    cv2.imshow('result', result)
    cv2.waitKey(0)
    cv2.destroyAllWindows()