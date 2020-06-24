'''
Lição de casa 2: Altere o programa 7 para calcular gradiente usando núcleo de Sobel. Rode o

Calcular vetor gradiente (em relação a x e y da imagem). Então teremos duas imagens componentes.
Derivada de sinal discreto é aproximada por:
x'(n)=0.5*[x(n+1)−x(n−1)]

0.5* [0 −1 0
      0 0 0
      0 1 0]

0.5* [0 0 0
     −1 0 1
      0 0 0]

(a) Filtros simples para calcular gradiente.

Ou seja, o gradiente é composto por dois filtros lineares aplicados em direções opostas.
Filtro linear é um produto pixel a pixel (kernel como ponderador)

Nesse exercicio utilizaremos Kernel de Sobel no filtro:

−1 −2 −1
0 0 0
1 2 1

−1 0 1
−2 0 2
−1 0 1

'''

import cv2
import numpy as np

def gradiente_imagem(img):

    # Usando Sobel

    img = img/255

    mx = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
    mx = np.array(mx)

    mx = mx / 4

    my = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
    my = np.array(my)

    my = my / 4

    img_x = cv2.filter2D(img, -1, kernel=mx)
    img_y = cv2.filter2D(img, -1, kernel=my)

    return img_x, img_y

img = cv2.imread("fantom.pgm")

cv2.imshow("Circulo", img)
k=cv2.waitKey(0)

img_x = gradiente_imagem(img)[0]*255
img_y = gradiente_imagem(img)[1]*255

modgrad = np.sqrt(np.power(img_x, 2) + np.power(img_y, 2))

modgrad = np.uint64(modgrad)

cv2.imshow("Circulo - Componente X", img_x)
k=cv2.waitKey(0)

cv2.imshow("Circulo - Componente Y", img_y)
k=cv2.waitKey(0)

cv2.imshow("Módulo do Gradiente", 0.5+modgrad)
k=cv2.waitKey(0)
