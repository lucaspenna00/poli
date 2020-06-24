import cv2
import numpy as np


'''

Corrigir perspectiva
Pegamos os pontos "na mão" da imagem original e definimos os pontos de início e os pontos de destino "onde queremos levar os pontos iniciais". Após isso utilizamos a função warpPerspective passando
os pontos de correção
'''


# Lendo imagem de entrada
entrada = cv2.imread("quadrado2a.png")

# Definição dos pontos correspondentes a imagem de origem e de saída
pontos_inicio = np.array([(235, 156), (640, 203), (0, 260), (447, 321)], dtype = "float32")
pontos_destino = np.array([(1, 0), (620, 0), (1, 450), (620, 450)], dtype = "float32")

# Fazendo a conversão das imagens
pontos_de_correcao = cv2.getPerspectiveTransform(pontos_inicio, pontos_destino)

tamanho_imagem = (620, 450)

saida = cv2.warpPerspective(entrada, pontos_de_correcao, tamanho_imagem)

# Salvando imagem de saída
cv2.imshow("quadrado2b.png", saida)
k=cv2.waitKey(0)
