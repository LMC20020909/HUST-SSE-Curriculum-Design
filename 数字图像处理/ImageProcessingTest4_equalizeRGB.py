import cv2
import numpy
from matplotlib import pyplot as plt


if __name__ == '__main__':
    img = cv2.imread('Fig6.png')
    cv2.imshow('Fig6', img)
    b, g, r = cv2.split(img)
    b = cv2.equalizeHist(b)
    g = cv2.equalizeHist(g)
    r = cv2.equalizeHist(r)
    res = cv2.merge([b, g, r])
    cv2.imshow('res', res)
    cv2.imwrite('Fig6_output2.png', res)
    if cv2.waitKey(0) & 0xFF == 'q':
        cv2.destroyAllWindows()