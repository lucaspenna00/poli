import cv2
import numpy as np
from sklearn.neighbors import KNeighborsRegressor

def definir_tabela_funcao_filtro(img_treino_x, img_treino_y, ker_size=3):

    '''
    Transforma as imagens de treino X e Y em um dataframe de treino, com (3*3) features e uma coluna de label, correspondente
    ao pixel da imagem.
    Ou seja, definição da função

    W(x1,x2,x3,...,x9)---->img(pixel_do_meio)

    faltou somente generalizar a janela

    '''

    img_treino_x = img_treino_x/255.0
    img_treino_y = img_treino_y/255.0

    n_linhas = (img_treino_x.shape[0]-2)*(img_treino_x.shape[1]-2)

    tabela_de_x = np.empty((n_linhas, ker_size*ker_size))
    tabela_de_y = np.empty(n_linhas)

    l = 0;

    for i in range(1, img_treino_x.shape[0]-1):

        for j in range(1, img_treino_x.shape[1]-1):

            tabela_de_x[l][0] = img_treino_x[i-1][j-1]
            tabela_de_x[l][1] = img_treino_x[i-1][j]
            tabela_de_x[l][2] = img_treino_x[i-1][j+1]

            tabela_de_x[l][3] = img_treino_x[i][j-1]
            tabela_de_x[l][4] = img_treino_x[i][j]
            tabela_de_x[l][5] = img_treino_x[i][j+1]

            tabela_de_x[l][6] = img_treino_x[i+1][j-1]
            tabela_de_x[l][7] = img_treino_x[i+1][j]
            tabela_de_x[l][8] = img_treino_x[i+1][j+1]

            tabela_de_y[l]  = img_treino_y[i][j]

            l=l+1

    return tabela_de_x, tabela_de_y

def reconstruir_imagem(Y_pred, dim_x, dim_y):

    '''

    dada as dimensões da imagem original e o Y_pred, reconstroi a imagem

    '''

    img = np.empty((dim_x-2, dim_y-2))

    l=0

    for i in range(0, dim_x-2):

        for j in range(0, dim_y-2):

            img[i][j] = Y_pred[l]*255

            l=l+1

    return np.uint8(img)

def AUX_transformar_cinza_em_preto(img):

    '''

    função auxiliar para pintar de preto os "cinzinhas" obtidos na regressão do kNN

    '''

    for i in range(0, img.shape[0]):

        for j in range(0, img.shape[1]):

            if img[i][j] != 255:

                img[i][j] = 0

    return img

img_treino_x = cv2.imread("img_treino_x.bmp", cv2.IMREAD_GRAYSCALE)
img_treino_y = cv2.imread("img_treino_y.bmp", cv2.IMREAD_GRAYSCALE)
img_teste_x = cv2.imread("img_teste_x.bmp", cv2.IMREAD_GRAYSCALE)
img_teste_y = cv2.imread("img_teste_y.bmp", cv2.IMREAD_GRAYSCALE)

print("1 definir tabela")
X_treino, Y_treino = definir_tabela_funcao_filtro(img_treino_x, img_treino_y, ker_size=3)

print("2 definir tabela")
X_teste, Y_teste = definir_tabela_funcao_filtro(img_teste_x, img_teste_y, ker_size=3)

# KNN versão regressão importado da biblioteca de Machine Learning sklearn
# Acho mais fácil que usar o ML do OpenCV
kNN = KNeighborsRegressor(n_neighbors=15)

print("3 treinar kNN")
kNN.fit(X_treino, Y_treino)

Y_pred = kNN.predict(X_teste)

print("4 reconstruir imagem")
img_pred = reconstruir_imagem(Y_pred, dim_x=img_teste_y.shape[0], dim_y=img_teste_y.shape[1])

cv2.imshow("ponta de reta predicted", AUX_transformar_cinza_em_preto(img_pred))
k=cv2.waitKey(0)

cv2.imshow("ponta de reta real", img_teste_y)
k=cv2.waitKey(0)

cv2.imwrite("img_pred.png", AUX_transformar_cinza_em_preto(img_pred))
cv2.imwrite("img_true.png", img_teste_y)
