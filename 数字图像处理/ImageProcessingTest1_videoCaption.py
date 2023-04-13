# -*- coding: utf-8 -*-
"""
Created on Thu Sep 22 19:33:52 2022

@author: 86182
"""
import cv2

linetype = cv2.LINE_AA
font = cv2.FONT_HERSHEY_SIMPLEX
isShow = True
caption = ['Today is Thursday', 'I can do all the things', 'I like you', 'who are you', "I'm sorry"]
i = 0


def click(event, *_):
    global isShow, i
    if event == cv2.EVENT_LBUTTONDOWN:
        isShow = not isShow
        if isShow:
            i = (i + 1) % 5


def show():
    cap = cv2.VideoCapture('vtest.avi')
    cv2.namedWindow('frame')
    cv2.setMouseCallback('frame', click)
    while cap.isOpened():
        ret, frame = cap.read()
        if ret:
            # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            if isShow:
                cv2.putText(frame, caption[i], (10, 500), font, 2, (255, 255, 255), 2)
            cv2.imshow('frame', frame)
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    show()

