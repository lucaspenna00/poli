'''
Reduzir ruído de imagem preto e branca
Utilizando média aritmética dos pixels ao redor
'''

import cv2

img = cv2.imread("noisy_image.jpg")

#cv2.imshow("Mickey sem Ruido", img)
#k = cv2.waitKey(0)

for n in range(0, 30):

    for banda in range(0, img.shape[2]):

        for row in range(1, img.shape[0]-1):

            for col in range(1, img.shape[1]-1):

                img[row][col][banda] = (0.25*img[row][col-1][banda] + 0.25*img[row][col+1][banda] + 0.25*img[row-1][col][banda] + 0.25*img[row+1][col][banda])

cv2.imshow("Mickey sem Ruido", img)
k = cv2.waitKey(0)

cv2.imwrite("obamadenoisy.png", img)
