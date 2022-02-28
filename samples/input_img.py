'''
Author: your name
Date: 2021-11-04 15:09:52
LastEditTime: 2021-11-04 15:21:44
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: /Mask_RCNN/samples/input_img.py
'''
import cv2 
import numpy as np 

img = cv2.imread('city-3258896.jpg', cv2.IMREAD_COLOR)
print(type(img))
print(img.shape)