import cv2
import numpy as np

if __name__ == '__main__':
    cap = cv2.VideoCapture(0)
    while 1:
        # 获取每一帧
        ret, frame = cap.read()
        # 转换到HSV
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        # 设定蓝色的阈值
        lower_blue = np.array([110, 50, 50])
        upper_blue = np.array([130, 255, 255])
        # 根据阈值构建掩模
        mask = cv2.inRange(hsv, lower_blue, upper_blue)
        kernel = np.ones((8, 8), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        xy = np.where(mask == 255)
        y = list(xy)[0]
        x = list(xy)[1]
        x_min, x_max = min(x), max(x)
        y_min, y_max = min(y), max(y)
        cv2.rectangle(frame, (x_min, y_min), (x_max, y_max), (0, 255, 0), 2)
        # mask = cv2.erode(mask, kernel, iterations=1)
        # 对原图像和掩模进行位运算
        res = cv2.bitwise_and(frame, frame, mask=mask)
        # 显示图像
        cv2.imshow('frame', frame)
        cv2.imshow('mask', mask)
        cv2.imshow('res', res)
        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break
    # 关闭窗口
    cv2.destroyAllWindows()
