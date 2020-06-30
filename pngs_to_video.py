#! /usr/bin/env python3
#! /usr/bin/python3

import cv2
import os

image_folder = 'images'
video_name = 'fast_slam.avi'

images = os.listdir(image_folder)
images = sorted(images)

frame = cv2.imread(os.path.join(image_folder, images[0]))
height, width, layers = frame.shape

video = cv2.VideoWriter(video_name, 0, 10, (width,height))

for image in images:
    video.write(cv2.imread(os.path.join(image_folder, image)))

cv2.destroyAllWindows()
video.release()