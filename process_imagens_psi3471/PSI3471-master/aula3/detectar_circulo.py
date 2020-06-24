'''
Usar a ideia de gradiente da imagem!

'''

import cv2
import numpy as np

def gradiente_imagem(img):

    # Usando Sobel

    mx = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
    mx = np.array(mx)

    mx = mx / 3

    my = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
    my = np.array(my)

    my = my / 3

    img_1 = cv2.filter2D(img, -1, kernel=mx)
    img_2 = cv2.filter2D(img, -1, kernel=my)
    img_3 = cv2.filter2D(img, -1, kernel=-mx)
    img_4 = cv2.filter2D(img, -1, kernel=-my)

    return img_1, img_2, img_3, img_4

img = cv2.imread("placa_transito_2.png")

cv2.imshow("Circulo", img)
k=cv2.waitKey(0)

img_1 = gradiente_imagem(img)[0]
img_2 = gradiente_imagem(img)[1]
img_3 = gradiente_imagem(img)[2]
img_4 = gradiente_imagem(img)[3]

cv2.imshow("Circulo - Componente X", img_1)
k=cv2.waitKey(0)

cv2.imshow("Circulo - Componente Y", img_2)
k=cv2.waitKey(0)

cv2.imshow("Circulo - Componente Y", img_3)
k=cv2.waitKey(0)

cv2.imshow("Circulo - Componente Y", img_4)
k=cv2.waitKey(0)
