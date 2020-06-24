import numpy as np
import cv2
import queue

RED = [0, 0, 255]

def pintaRegiaoDeCor(a, li, ci, color):

    threshold = 100
    b=a.copy()

    color_seed = a[li, ci]

    q=queue.Queue()

    q.put(li) #1

    q.put(ci) #1

    l=0
    c=0

    while not q.empty(): #2

        print(q.qsize())

        l=q.get() #3

        c=q.get() #3

        #print(np.linalg.norm(b[l][c]-color_seed))

        if np.linalg.norm(b[l][c] - color_seed) <= threshold: #4

            b[l,c]=color #5

            #print("Coordenadas pintadas: "+str(l)+","+str(c))

            q.put(l-1); q.put(c) #6-acima

            q.put(l+1); q.put(c) #6-abaixo

            q.put(l); q.put(c+1) #6-direita

            q.put(l); q.put(c-1) #6-esquerda

    return b

img = cv2.imread("elefante.jpg")

img = pintaRegiaoDeCor(img, 140, 120, RED)

cv2.imshow("Pintar regiao aproximada", img)
k = cv2.waitKey(0)
