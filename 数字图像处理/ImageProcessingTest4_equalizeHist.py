import cv2
import numpy as np

if __name__ == '__main__':
    img = cv2.imread('flower2.jpg', 0)
    equ = cv2.equalizeHist(img)
    res = np.hstack((img, equ))
    cv2.imshow('hist.jpg', res)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
