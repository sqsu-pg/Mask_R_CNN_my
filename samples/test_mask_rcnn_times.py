import Mask_class as MC 

import os
import time 
import glob 
import cv2 as cv 
import argparse
import numpy as np 

# start = time.clock()

# time.sleep(5)

# end = time.clock()

# print ("times used is : " , end - start)

if __name__ == "__main__":

    net = MC.Mask()

    parser = argparse.ArgumentParser()
    parser.add_argument('--path', help="dataset for evaluation")

    arg = parser.parse_args()
    
    kitti_path = arg.path

    image_paths = glob.glob(os.path.join(kitti_path + '/image_0/', '*.png'))
    print ("image_path.size is : ", len(image_paths))

    image_paths = sorted(image_paths)

    sum_of_mask_time = 0.
    sum_of_mask_img = len(image_paths)

    for image_path in image_paths:
        start = time.time()
        image = cv.imread(image_path)

        if len(image.shape) == 2:
            im1 = np.zeros((image.shape[0], image.shape[1], 3))

            im1[:, :, 0] = image
            im1[:, :, 1] = image
            im1[:, :, 2] = image

            image = im1

        mask = np.zeros((image.shape[0], image.shape[1]))

        results = net.model.detect([image], verbose = 0)   

        # Visualize results
        r = results[0]
        i = 0
        num_mask = 1
        for roi in r['rois']:
            if net.class_names[r['class_ids'][i]] == 'person':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = num_mask
                num_mask += 1
            if net.class_names[r['class_ids'][i]] == 'bicycle':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = num_mask
                num_mask += 1
            if net.class_names[r['class_ids'][i]] == 'car':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = num_mask
                num_mask += 1
            if net.class_names[r['class_ids'][i]] == 'motorcycle':
                mask[image_m == 1] = num_mask
                num_mask += 1
            # if self.class_names[r['class_ids'][i]] == 'airplane':
            #     image_m = r['masks'][:,:,i]
            #     mask[image_m == 1] = 1.
            if net.class_names[r['class_ids'][i]] == 'bus':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = num_mask
                num_mask += 1
            # if self.class_names[r['class_ids'][i]] == 'train':
            #     image_m = r['masks'][:,:,i]
            #     mask[image_m == 1] = 1.
            if net.class_names[r['class_ids'][i]] == 'truck':
                image_m = r['masks'][:,:,i]
                mask[image_m == 1] = num_mask
                num_mask += 1
            if net.class_names[r['class_ids'][i]] == 'boat':
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
        end = time.time()
        print("each time : ", end - start)

        sum_of_mask_time = sum_of_mask_time + end - start
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
        # print ("Save mask")
        
        # save_path = dir_path_epo + "_mask/" + save_txt_name
        # print ("save mask in ", save_path)
        # np.savetxt(save_path, mask, fmt = "%d")

        # return mask

    mean_of_mask_time = sum_of_mask_time / sum_of_mask_img

    Hz_of_mask = 1 / mean_of_mask_time

    print ("mean_of_mask_time is : ", mean_of_mask_time)
    print ("Hz_of_mask is : ", Hz_of_mask)