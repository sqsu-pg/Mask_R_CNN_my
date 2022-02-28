'''
Author: your name
Date: 2021-11-02 15:21:40
LastEditTime: 2022-01-20 00:17:03
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: /Mask_RCNN/samples/Mask_class.py
'''
#!/usr/bin/env python
# coding: utf-8

# # Mask R-CNN Demo
# 
# A quick intro to using the pre-trained model to detect and segment objects.


import os
#os.environ[‘TF_CPP_MIN_LOG_LEVEL’] = ‘2’
import sys
import random
import math
import numpy as np
import skimage.io
import matplotlib
import matplotlib.pyplot as plt

import cv2 as cv

#Root directory of the project
ROOT_DIR1 = os.path.abspath("/home/george/Mask_RCNN")
sys.path.append(ROOT_DIR1)


from mrcnn import utils
import mrcnn.model as modellib
from mrcnn import visualize

#Import Mask RCNN
sys.path.append(os.path.join(ROOT_DIR1, "samples/coco/"))
import coco

from tensorflow.compat.v1 import ConfigProto
from tensorflow.compat.v1 import InteractiveSession

config = ConfigProto()
config.gpu_options.allow_growth = True
session = InteractiveSession(config=config)

class Mask:
    def __init__(self):
       print ("Initializing Mask RCNN network....") 
       ROOT_DIR = os.path.abspath("/home/george/Mask_RCNN")
       MODEL_DIR = os.path.join(ROOT_DIR, "logs")

       # Local path to trained weights file
       COCO_MODEL_PATH = os.path.join(ROOT_DIR, "mask_rcnn_coco.h5")   

       if not os.path.exists(COCO_MODEL_PATH):
           utils.download_trained_weights(COCO_MODEL_PATH)

       # Directory of images to run detection on
       self.IMAGE_DIR = os.path.join(ROOT_DIR, "images")

       class InferenceConfig(coco.CocoConfig):##类的继承
           #Set batch size to 1 since we'll be running inference on
           ##one image at a time, Batch size = GPU_COUNT * IMAGES_PER_GPU
           GPU_COUNT = 1
           IMAGES_PER_GPU = 1
       
       config = InferenceConfig()
       config.display()
       
       ##Create model object in inference mode.
       self.model = modellib.MaskRCNN(mode = "inference", model_dir = MODEL_DIR, config = config)##创建模型对象

       self.model.load_weights(COCO_MODEL_PATH, by_name=True)

       ##COCO Class names
       ## Index of the class in the list is its ID. For example, to get ID of
       ## the teddy bear class, use: class_names.index('teddy_bear')
       self.class_names = ['BG', 'person', 'bicycle', 'car', 'motorcycle', 'airplane',
               'bus', 'train', 'truck', 'boat', 'traffic light',
               'fire hydrant', 'stop sign', 'parking meter', 'bench', 'bird',
               'cat', 'dog', 'horse', 'sheep', 'cow', 'elephant', 'bear',
               'zebra', 'giraffe', 'backpack', 'umbrella', 'handbag', 'tie',
               'suitcase', 'frisbee', 'skis', 'snowboard', 'sports ball',
               'kite', 'baseball bat', 'baseball glove', 'skateboard',
               'surfboard', 'tennis racket', 'bottle', 'wine glass', 'cup',
               'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple',
               'sandwich', 'orange', 'broccoli', 'carrot', 'hot dog', 'pizza',
               'donut', 'cake', 'chair', 'couch', 'potted plant', 'bed',
               'dining table', 'toilet', 'tv', 'laptop', 'mouse', 'remote',
               'keyboard', 'cell phone', 'microwave', 'oven', 'toaster',
               'sink', 'refrigerator', 'book', 'clock', 'vase', 'scissors',
               'teddy bear', 'hair drier', 'toothbrush']
       
       print ("Initialated Mask RCNN network....")
    
    def GetDynSeg(self):
        file_names = next(os.walk(self.IMAGE_DIR))[2]
        image = skimage.io.imread(os.path.join(self.IMAGE_DIR, random.choice(file_names)))
        print (image)

        results = self.model.detect([image], verbose=1)
        
        r = results[0]
        r_mask = r['masks']
        visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], 
                            self.class_names, r['scores'])
    
    def GetDynSeg1(self, image, image2=None):
        
        h = image.shape[0]
        w = image.shape[1]
        if len(image.shape) == 2:
            im = np.zeros((h,w,3))
            im[:,:,0]=image
            im[:,:,1]=image
            im[:,:,2]=image
            image = im
        mask = np.zeros((h,w))
        print(mask.shape)
        # if image2 is not None:
        # 	args+=[image2]
        #Run detection
        print ("开始检测")
        results = self.model.detect([image], verbose=0)
        print ("检测成功")
        # Visualize results
        r = results[0]
        i = 0
        for roi in r['rois']:
            if self.class_names[r['class_ids'][i]] == 'person':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'bicycle':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'car':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'motorcycle':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'airplane':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'bus':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'train':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'truck':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'boat':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'bird':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'cat':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'dog':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'horse':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'sheep':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'cow':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'elephant':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'bear':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'zebra':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.
            if self.class_names[r['class_ids'][i]] == 'giraffe':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = 1.		
            i+=1
        
        
        print('GetSeg mask shape:',mask.shape)
        mask = (mask*255).astype(np.uint8)
        im_res = np.zeros((h,w,3))
        im_res[:,:,0]=mask
        im_res[:,:,1]=mask
        im_res[:,:,2]=mask
        print ("显示Mask");
        plt.figure("Mask_result")
        plt.imshow(im_res)
        plt.axis('on')
        plt.title('image')
        plt.show()


        return im_res.astype(np.uint8)
    
    def get_img(self, image):
        if len(image.shape) == 2:
            im = np.zeros((h,w,3))
            im[:,:,0]=image
            im[:,:,1]=image
            im[:,:,2]=image
            image = im

        return image

    def GetAndSaveMask(self, path):
        
        str1 = path + "/image_0"
        #str2 = path + "/image_1"
        dir_path = [str1]
        print("处理的所有文件夹为: ")
        for s in dir_path:
            print (s)


        # for dir_path_epo in dir_path:
        #     for image_path in os.listdir(dir_path_epo):
        #         image_vec.append(image_path)
        # print ("图片总数目为: ", len(image_vec))

        for dir_path_epo in dir_path:
            for image_path in os.listdir(dir_path_epo):
                
                save_path_list = image_path.split('.')
                save_path_num = save_path_list[0]
                save_txt_name = save_path_num + ".txt"

                image_path = dir_path_epo +"/" + image_path
                image = cv.imread(image_path, 1)
                h = image.shape[0]
                w = image.shape[1]
                if len(image.shape) == 2:
                    im = np.zeros((h,w,3))
                    im[:,:,0]=image
                    im[:,:,1]=image
                    im[:,:,2]=image
                    image = im
                mask = np.zeros((h,w))
                print(mask.shape)
                # if image2 is not None:
                # 	args+=[image2]
                #Run detection
                print ("开始检测")
                results = self.model.detect([image], verbose=0)
                print ("检测成功")
                # Visualize results
                r = results[0]
                i = 0
                num_mask = 1
                for roi in r['rois']:
                    if self.class_names[r['class_ids'][i]] == 'person':
                        image_m = r['masks'][:,:,i]
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    if self.class_names[r['class_ids'][i]] == 'bicycle':
                        image_m = r['masks'][:,:,i]
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    if self.class_names[r['class_ids'][i]] == 'car':
                        image_m = r['masks'][:,:,i]
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    if self.class_names[r['class_ids'][i]] == 'motorcycle':
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    # if self.class_names[r['class_ids'][i]] == 'airplane':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    if self.class_names[r['class_ids'][i]] == 'bus':
                        image_m = r['masks'][:,:,i]
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    # if self.class_names[r['class_ids'][i]] == 'train':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    if self.class_names[r['class_ids'][i]] == 'truck':
                        image_m = r['masks'][:,:,i]
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    if self.class_names[r['class_ids'][i]] == 'boat':
                        image_m = r['masks'][:,:,i]
                        mask[image_m == 1] = num_mask
                        num_mask += 1
                    # if self.class_names[r['class_ids'][i]] == 'bird':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'cat':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'dog':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'horse':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'sheep':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'cow':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'elephant':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'bear':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'zebra':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.
                    # if self.class_names[r['class_ids'][i]] == 'giraffe':
                    #     image_m = r['masks'][:,:,i]
                    #     mask[image_m == 1] = 1.		
                    i+=1
                #print('GetSeg mask shape:',mask.shape)
                # mask = (mask*255).astype(np.uint8)
                # im_res = np.zeros((h,w,3))
                # im_res[:,:,0]=mask
                # im_res[:,:,1]=mask
                # im_res[:,:,2]=mask
                # print ("显示Mask");
                # plt.figure("Mask_result")
                # plt.imshow(im_res)
                # plt.axis('on')
                # plt.title('image')
                # plt.show()
                print ("Save mask")
                
                save_path = dir_path_epo + "_mask/" + save_txt_name
                print ("save mask in ", save_path)
                np.savetxt(save_path, mask, fmt = "%d")


        # return im_res.astype(np.uint8)

if __name__ == '__main__':

    net = Mask()
    net.GetDynSeg()
