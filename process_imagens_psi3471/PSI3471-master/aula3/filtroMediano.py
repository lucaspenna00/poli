import cv2

img = cv2.imread("noisy_image.jpg")

cv2.imshow("noisy", img)
k = cv2.waitKey(0)

''''

1 2 3      1 2 3
4   5  --> 4 4 5
6 7 8      6 7 8

'''

for i in range(10):

    img = cv2.medianBlur(img, 3)

cv2.imshow("bye bye noisy", img)
k = cv2.waitKey(0)
