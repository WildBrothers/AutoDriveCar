
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np


# extract white and yellow from image
def filter_colors(image):
    white_threshold = 200  # 130
    lower_white = np.array([white_threshold, white_threshold, white_threshold])
    upper_white = np.array([255, 255, 255])
    white_mask = cv2.inRange(image, lower_white, upper_white)
    white_image = cv2.bitwise_and(image, image, mask=white_mask)

    # Filter yellow pixels
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    lower_yellow = np.array([90, 100, 100])
    upper_yellow = np.array([110, 255, 255])
    yellow_mask = cv2.inRange(hsv, lower_yellow, upper_yellow)
    yellow_image = cv2.bitwise_and(image, image, mask=yellow_mask)

    # Combine the two above images
    image2 = cv2.addWeighted(white_image, 1., yellow_image, 1., 0.)

    return image2


if __name__ == '__main__':
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.framerate = 32
    rawCapture = PiRGBArray(camera, size=(640, 480))

    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        # grab the raw NumPy array representing the image, then initialize the timestamp
        # and occupied/unoccupied text
        image = frame.array

        filtered_img = filter_colors(image)

        # show the frame
        cv2.imshow("Frame", filtered_img)
        # setting fps and wait user keyboard input
        # after that, masking result by dec 255
        key = cv2.waitKey(1) & 0xFF

        # http://picamera.readthedocs.io/en/release-1.10/api_array.html?highlight=truncate
        # this doc say that truncate is deprecated now,
        rawCapture.truncate(0)

        if key == ord("q"):
            break

