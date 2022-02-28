'''
Author: your name
Date: 2022-01-19 23:28:31
LastEditTime: 2022-01-19 23:33:32
LastEditors: Please set LastEditors
Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
FilePath: /Mask_RCNN/samples/make_mask_for_kitti.py
'''
import Mask_class

net = Mask_class.Mask()
kitti_path = "/home/liubo/data_sets/04"

net.GetAndSaveMask(kitti_path)
