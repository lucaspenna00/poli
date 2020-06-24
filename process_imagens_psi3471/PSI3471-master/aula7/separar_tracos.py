import cv2

'''
Lição 7.1 separar traços verticais e horizontais
Conceito de Erosão e Diltação

Erosão adequada na imagem fará com que o branco seja comprimido
Diltação adequada na imagem fará com que o branco seja expandido.


'''

WHITE=[255,255,255]
BLACK=[0,0,0]

img = cv2.imread("horver.png")

ver = cv2.erode(src=img, kernel=(3,3))

## --- PINTAR DE PRETO TUDO QUE É TRAÇO VERTICAL ---""

for linha in range(ver.shape[0]):

    for coluna in range(ver.shape[1]):

        if all(ver[linha][coluna] == WHITE):

            img[linha][coluna] = BLACK

hor = img

hor = cv2.dilate(src=hor, kernel=(3,3))

hor = cv2.medianBlur(hor,3)

cv2.imshow("vertical", ver)
k=cv2.waitKey(0) & 0xFF

cv2.imshow("horizontal", hor)
k=cv2.waitKey(0) & 0xFF
