# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 18:56:06 2022

@author: 86182
"""
import numpy as np
import cv2


def draw():
    # Create a black image
    img = np.zeros((512, 512, 3), np.uint8)  # np.uint8 是数据类型

    # Draw a diagonal blue line with thickness of 5 px
    cv2.line(img, (0, 0), (511, 511), (255, 0, 0), 5)

    cv2.rectangle(img, (384, 0), (510, 128), (0, 255, 0), 3)

    cv2.circle(img, (447, 63), 63, (0, 0, 255), -1)

    cv2.ellipse(img, (256, 256), (100, 50), 0, 0, 180, 255, -1)

    pts = np.array([[10, 5], [20, 30], [70, 20], [50, 10]], np.int32)
    pts = pts.reshape((-1, 1, 2))
    cv2.polylines(img, [pts], True, (0, 255, 255))

    linetype = cv2.LINE_AA
    font = cv2.FONT_HERSHEY_SIMPLEX
    cv2.putText(img, 'OpenCV', (10, 500), font, 4, (255, 255, 255), 2)

    cv2.imshow('line', img)
    k = cv2.waitKey(0) & 0xFF
    if k == 27:
        cv2.destroyAllWindows()


if __name__ == '__main__':
    draw()