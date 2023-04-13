import cv2
import numpy as np


# 顺时针
def on_mouse(event, x, y, flag, param):
    global X, Y, img, index, ix, iy, jx, jy
    if event == cv2.EVENT_LBUTTONUP and index < 4:
        X[index], Y[index] = x, y
        if index == 0:
            cv2.line(img, (x, y), (x, y), (0, 0, 255), 3)
        elif index == 1:
            cv2.line(img, (x, y), (X[index - 1], Y[index - 1]), (0, 0, 255), 3)
        elif index == 2:
            cv2.line(img, (x, y), (X[index - 1], Y[index - 1]), (0, 0, 255), 3)
        elif index == 3:
            cv2.line(img, (x, y), (X[index - 1], Y[index - 1]), (0, 0, 255), 3)
            cv2.line(img, (x, y), (X[0], Y[0]), (0, 0, 255), 3)
        index += 1
    elif event == cv2.EVENT_LBUTTONDOWN and index == 4:
        ix, iy = x, y
    elif event == cv2.EVENT_LBUTTONUP and index == 4:
        cv2.rectangle(img, (ix, iy), (x, y), (0, 255, 0), 1)
        jx, jy = x, y
        index += 1


if __name__ == '__main__':
    img = cv2.imread('ppt.jpg')
    cols, rows = img.shape[:2]
    X = [-1, -1, -1, -1]
    Y = [-1, -1, -1, -1]
    ix, iy, jx, jy = -1, -1, -1, -1
    index = 0
    cv2.namedWindow('image')
    cv2.setMouseCallback('image', on_mouse)
    while 1:
        cv2.imshow('image', img)
        if index > 4:
            pts1 = np.float32([[X[0], Y[0]], [X[1], Y[1]], [X[2], Y[2]]])
            pts2 = np.float32([[ix, iy], [jx, iy], [jx, jy]])
            M = cv2.getAffineTransform(pts1, pts2)
            dst = cv2.warpAffine(img, M, (cols, rows))
            cv2.imshow('output', dst)
        if cv2.waitKey(20) & 0xFF == 27:
            break
    cv2.imwrite("ppt_output.jpg", dst)
    cv2.destroyAllWindows()
