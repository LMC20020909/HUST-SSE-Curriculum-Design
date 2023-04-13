# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 18:48:28 2022

@author: 86182
"""
import cv2


def camera():
    cap = cv2.VideoCapture(0)  # 摄像头编号
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    # 创建视频流写入对象，VideoWriter_fourcc为视频编解码器，20为帧播放速率，（640，480）为视频帧大小
    out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480))
    while cap.isOpened():
        ret, frame = cap.read()
        if ret:
            frame = cv2.flip(frame, 0)
            out.write(frame)
            cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()
    out.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    camera()
