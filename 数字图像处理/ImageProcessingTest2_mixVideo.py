# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 20:49:07 2022

@author: 86182
"""
import cv2


def mix_video():
    cap = cv2.VideoCapture(0)
    cap1 = cv2.VideoCapture('vtest.avi')
    ret0, frame0 = cap.read()
    # cv2.imwrite('frame0.jpg', frame0)
    # img = cv2.imread('frame0.jpg')
    # img2 = cv2.imread('frame1.jpg')
    # img3 = cv2.subtract(img1, img2)
    # cv2.imshow('img2', img2)
    # cv2.imshow('img3', img3)
    # cv2.waitKey(0)
    while cap1.isOpened():
        ret, frame = cap.read()
        ret1, frame1 = cap1.read()
        if ret1:
            frame1 = cv2.resize(frame1, (frame.shape[1], frame.shape[0]))
            frame_mask = cv2.subtract(frame, frame0)
            frame_gray = cv2.cvtColor(frame_mask, cv2.COLOR_BGR2GRAY)
            # cv2.imshow('frame_gray', frame_gray)
            _, mask_front = cv2.threshold(frame_gray, 26, 255, cv2.THRESH_BINARY)
            mask_inv = cv2.bitwise_not(mask_front)
            frame1_bg = cv2.bitwise_and(frame1, frame1, mask=mask_inv)
            cv2.imshow('mask_front', mask_front)
            cv2.imshow('frame1_bg', frame1_bg)
            frame_me = cv2.bitwise_and(frame, frame, mask=mask_front)
            cv2.imshow('frame_me', frame_me)
            # print(frame_me.shape)
            # print(mask_front.shape)
            frame_res = cv2.add(frame_me, frame1_bg)
            cv2.imshow('frame', frame_res)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cap1.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    mix_video()