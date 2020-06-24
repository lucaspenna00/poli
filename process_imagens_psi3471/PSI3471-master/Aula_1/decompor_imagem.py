'''
Reduzir ruído de imagem preto e branca
Utilizando média aritmética dos pixels ao redor
'''

import cv2

img = cv2.imread("flor_ori.jpg")

# B G R

'''
mantenho canal 0 com os valores de azul e passo os outros como 0
o msm pras outras cores
'''
# get blue image
img_blue = img.copy()

img_blue[:,:,1] = 0
img_blue[:,:,2] = 0

# get green image
img_green = img.copy()

img_green[:,:,0] = 0
img_green[:,:,2] = 0

# get red image
img_red = img.copy()

img_red[:,:,0] = 0
img_red[:,:,1] = 0

cv2.imshow("Flor azul", img_blue)
k = cv2.waitKey(0)

cv2.imshow("Flor verde", img_green)
k = cv2.waitKey(0)

cv2.imshow("Flor vermelho", img_red)
k = cv2.waitKey(0)

cv.imwrite("flor_blue.png", img_blue)
cv.imwrite("flor_green.png", img_green)
cv.imwrite("flor_red.png", img_red)
