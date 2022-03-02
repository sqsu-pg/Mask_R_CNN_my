import argparse

import cv2 as cv
import numpy as np


Color = {0:[255, 0, 0],
         1:[0, 255, 0],
         2:[0, 0, 255],
         3:[255, 255, 0],
         4:[255, 0, 255],
         5:[0, 255, 255],
         6:[153, 50, 204],
         7:[255, 185, 15],
         8:[0, 139, 69],
         9:[175, 238, 238]
         }



def vis_mask_save_png(args):
    mask = np.loadtxt(args.mask_path, dtype=np.int32)
    source_img = cv.imread(args.img_path)
    
    if len(source_img.shape) == 2:
        tmp_img = np.zeros((source_img.shape[0], source_img.shape[1], 3))
        tmp_img[:, :, 0] = source_img
        tmp_img[:, :, 1] = source_img
        tmp_img[:, :, 2] = source_img
        source_img = tmp_img

    if mask.shape[0] != source_img.shape[0] or mask.shape[1] != source_img.shape[1]:
        print("error because the size of mask and source img are not same...")
        return 
    
    for i in range(mask.shape[0]):
        for j in range(mask.shape[1]):
            if mask[i][j] == 0:
                continue
            elif mask[i, j] != 0:
                index = mask[i, j] % 9
                source_img[i, j, 0] = Color[index][0]
                source_img[i, j, 1] = Color[index][1]
                source_img[i, j, 2] = Color[index][2]
    
    cv.imshow("mask_vis", source_img)
    cv.waitKey()
    cv.imwrite(args.save_vismask_path, source_img)
                




if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--save_vismask_path', help="restore checkpoint")
    parser.add_argument('--mask_path', help="dataset for evaluation")
    parser.add_argument('--img_path', help="dataset for evaluation")
    args = parser.parse_args()

    vis_mask_save_png(args)
