
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np


# Canny Edge Detector
low_threshold = 50
high_threshold = 150


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


def gaussian_blur(img, kernel_size):
    """Applies a Gaussian Noise kernel"""
    return cv2.GaussianBlur(img, (kernel_size, kernel_size), 0)


def grayscale(img):
    """Applies the Grayscale transform
	This will return an image with only one color channel
	but NOTE: to see the returned image as grayscale
	you should call plt.imshow(gray, cmap='gray')"""
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def canny(img, low_threshold, high_threshold):
    """Applies the Canny transform"""
    return cv2.Canny(img, low_threshold, high_threshold)


if __name__ == '__main__':
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.framerate = 32
    rawCapture = PiRGBArray(camera, size=(640, 480))

    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        # grab the raw NumPy array representing the image, then initialize the timestamp
        # and occupied/unoccupied text
        image = frame.array

        # TEST
        filtered_img = filter_colors(image)
        gray_img = grayscale(filtered_img)
        blur_img = gaussian_blur(gray_img, kernel_size=3)
        canny_img = canny(blur_img, low_threshold, high_threshold)
        # TEST

        # show the frame
        cv2.imshow("Canny", canny_img)
        # setting fps and wait user keyboard input
        # after that, masking result by dec 255
        key = cv2.waitKey(1) & 0xFF

        # http://picamera.readthedocs.io/en/release-1.10/api_array.html?highlight=truncate
        # this doc say that truncate is deprecated now,
        rawCapture.truncate(0)

        if key == ord("q"):
            break

