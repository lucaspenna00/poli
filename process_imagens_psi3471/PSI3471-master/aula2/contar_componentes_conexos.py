'''
-----------------------------------------
Contar componentes conexos - PSI 3471
Lucas Penna Saraiva
Aula 2
----------------------------------------
'''
import cv2
import queue

AZUL = [255, 0, 0]
WHITE = [255, 255, 255]

'''
1) Coloque o pixel-semente no conjunto V
dos pixels a serem visitados.
2) Se o conjunto V for vazio, termine o
programa.
3) Retire um pixel p de V.
4) Se p for preto ou azul, vá para (2).
5) Aqui, p é branco. Pinte-o de azul.
6) Coloque no conjunto V dos pixels a serem
visitados os pixels à direita, acima, à esquerda e abaixo de p.

'''
AZUL=(255,0,0)
BRANCO=(255,0,0)

def pintaRegiaoDeCor(a, li, ci, color):

    b=a.copy()

    color_seed = a[li, ci]

    q=queue.Queue()

    q.put(li) #1

    q.put(ci) #1

    while not q.empty(): #2

        l=q.get() #3

        c=q.get() #3

        if all(b[l,c,:]==color_seed): #4

            b[l,c]=color #5

            q.put(l-1); q.put(c) #6-acima

            q.put(l+1); q.put(c) #6-abaixo

            q.put(l); q.put(c+1) #6-direita

            q.put(l); q.put(c-1) #6-esquerda

    return b

img = cv2.imread("c2.bmp")

#img = pintaRegiaoDeCor(img, 0,0, AZUL)
#cv2.imshow("letras", img)
#k = cv2.waitKey(0)

BACKGROUND_COLOR = img[0, 0]

count = 0

img_copy = img.copy()

for linha in range(1, img.shape[0]-1):

    for coluna in range(1, img.shape[1]-1):

        if all(img[linha][coluna] != BACKGROUND_COLOR):

            count = count + 1

            img = pintaRegiaoDeCor(img, linha, coluna, BACKGROUND_COLOR)

            img_copy = pintaRegiaoDeCor(img_copy, linha, coluna, AZUL)

print("O numero de componentes conexos é: ", count)

cv2.imshow("Componentes Conexos", img_copy)
k = cv2.waitKey(0)
