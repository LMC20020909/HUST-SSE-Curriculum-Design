# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 19:07:19 2022

@author: 86182
"""
import cv2
import numpy as np

# 当鼠标按下时变为True
drawing = False
# 如果mode 为true 绘制矩形。按下'm' 变成绘制曲线。
mode = True
ix, iy = -1, -1
colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]
color_rec = colors[0]
color_cir = colors[2]


# 创建回调函数
def draw_circle(event, x, y, flags, img):
    global ix, iy, drawing, mode
    # 当按下左键是返回起始位置坐标
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y

    # 当鼠标左键按下并移动是绘制图形。event 可以查看移动，flag 查看是否按下
    elif event == cv2.EVENT_MOUSEMOVE and flags == cv2.EVENT_FLAG_LBUTTON:
        if drawing:
            if mode:
                cv2.rectangle(img, (ix, iy), (x, y), color_rec, -1)
            else:
                r = int(np.sqrt((x - ix) ** 2 + (y - iy) ** 2))
                cv2.circle(img, (x, y), r, color_cir, -1)

    # 当鼠标松开停止绘画。
    elif event == cv2.EVENT_LBUTTONUP:
        if mode:
            cv2.rectangle(img, (ix, iy), (x, y), color_rec, -1)
        else:
            cv2.circle(img, (x, y), 5, color_cir, -1)


def paint():
    global ix, iy, drawing, mode, colors, color_rec, color_cir
    img = np.zeros((512, 512, 3), np.uint8)
    cv2.namedWindow('image')
    cv2.setMouseCallback('image', draw_circle, img)
    while 1:
        cv2.imshow('image', img)
        k = cv2.waitKey(1) & 0xFF
        if k == ord('m'):
            mode = not mode
        elif k == ord('b'):
            color_rec = colors[0] if mode else color_rec
            color_cir = colors[0] if not mode else color_cir
        elif k == ord('g'):
            color_rec = colors[1] if mode else color_rec
            color_cir = colors[1] if not mode else color_cir
        elif k == ord('r'):
            color_rec = colors[2] if mode else color_rec
            color_cir = colors[2] if not mode else color_cir
        elif k == 27:
            break
    cv2.destroyAllWindows()


if __name__ == '__main__':
    paint()
