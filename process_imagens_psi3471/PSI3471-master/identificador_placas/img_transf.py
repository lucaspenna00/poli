import cv2
import numpy as np

RED = [0,0,255]
BLACK = [0,0,0]
WHITE = [255,255,255]
GREEN = [0,255,0]

def transformarEmCinza(img):

    '''
    Recebe uma imagem e retorna a mesma em níveis de cinza. A cor desejada será transformada em Branco
    e as demais serão transformadas em preto.

    Inputs

    img: imagem que se deseja transformar em níveis de cinza.

    Output

    img: imagem transformada em preto e branco.
    '''

    '''
    Jeito antigo por método RGB, demorava muito para executar!

    for linha in range(0, img.shape[0]):

        for coluna in range(0, img.shape[1]):

            if np.linalg.norm(img[linha][coluna] - color) < threshold:

                img[linha][coluna] = WHITE

            else:

                img[linha][coluna] = BLACK

    return img
    '''

    # https://stackoverflow.com/questions/30331944/finding-red-color-in-image-using-python-opencv
    # COM A PARTE COMENTADA, O PROGRAMA DEMORAVA 40s pra rodar!!!!!!!!!!
    # com a otimização caiu para entre 5s a 10s, top demais!

    img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # lower mask (0-10)
    lower_red = np.array([0,50,50])
    upper_red = np.array([20,255,255])
    mask0 = cv2.inRange(img_hsv, lower_red, upper_red)

    # upper mask (170-180)
    lower_red = np.array([160,50,50])
    upper_red = np.array([180,255,255])
    mask1 = cv2.inRange(img_hsv, lower_red, upper_red)

    mask = mask0+mask1

    # set my output img to zero everywhere except my mask
    output_img = img.copy()
    output_img[np.where(mask==0)] = 0

    return output_img


def get_list_img_resizes(template_img, MAX_SIZE=100, q=0.9, save_temp=False, N=16):

    '''
    Recebe um template e retorna uma lista de imagens templates redimensionadas,

    Inputs

    template_img: imagem do template que se quer redimensionar.
    MAX_SIZE: (default 100) o tamanho da maior imagem a ser gerada.
    q: (default 0.9) a razão da progressão geométrica de  redimensionamento do template.
    save: (default False) se True, salva as imagens redimensionadas no diretório data.
    N: (default 16) número de imagens redimensionadas que se quer gerar.

    Output

    list_images: lista de imagens redimensionadas.
    '''

    list_images_temp = []

    for n in range(0, N):

        dim = (q**n)*MAX_SIZE

        #print("[ DEBUG] Dimensao da imagem "+str(n)+":", dim)

        list_images_temp.append(cv2.resize(template_img, (int(dim), int(dim))))

        if save_temp == True:

            cv2.imwrite("data_EP/image_resized_"+str(n)+".png", list_images[n])

    return list_images_temp


def get_placa_proibido(img, template, color=GREEN, threshold_placa=0.8, MAX_SIZE=150, q=0.95, save_temp=False, N=60):

    '''
    Recebe uma imagem e um template de placa e retorna a placa identificada na imagem, se houver parecida.
    Faz o casamento da imagem com N templates utilizando templateMatching. Escolhe o casamento em que há maior correlação.
    Desenha o círculo na placa.

    Inputs:

    img: imagem que se quer identificar a placa
    template: template da placa que se quer identificar
    color: cor do círculo que se deseja desenhar ao redor da placa (default GREEN)
    threshold_placa: limiar que indica a partir de quanto considerará a placa (default 0.8)
    MAX_SIZE: tamanho máximo de templates a serem gerados. Deve ser alterado considerando o tamanho do diâmetro máximo
    das placas que se quer identificar (default 150)
    q: fator geométrico de redução das imagens (default 150)
    save_temp: se True, salva as imagens de template geradas (default False)
    N: número de templates comparativos gerados (default 60)

    output:

    img: imagem com a placa detectada com o círculo desenhado.
    '''


    img_copy = img.copy()

    print("[ INFO] Transformando imagem em preto e branco ")

    img = transformarEmCinza(img)

    #cv2.imshow("DEBUG: Imagem preto e branco", img)
    #k=cv2.waitKey(0)

    every_max_corr = np.array([])

    print("[ INFO] Redimensionando os templates ")

    list_images_temp = get_list_img_resizes(template, MAX_SIZE, q, save_temp, N)

    print("[ INFO] Calculando correlacoes de cada casamento ")

    for template in list_images_temp:

        img_corr = cv2.matchTemplate(img, template, cv2.TM_CCOEFF_NORMED)

        #print("[ DEBUG] Corr. Max: ", img_corr.max())

        every_max_corr = np.append(every_max_corr, img_corr.max())

        if img_corr.max() >= threshold_placa:

            break

    n = np.argmax(every_max_corr)

    #print("[ DEBUG] Image selected:", n)

    img_corr = cv2.matchTemplate(img, list_images_temp[n], cv2.TM_CCOEFF_NORMED)

    #loc = np.where( img_corr >= threshold_placa) #PEGAR VÁRIAS PLACAS
    loc = np.where( img_corr == img_corr.max()) #ENTREGAR AO PROF. HAE COM APENAS UMA PLACA

    radius = ((list_images_temp[n].shape[0])/2)

    for pt in zip(*loc[::-1]):

        x = pt[0] + int(list_images_temp[n].shape[0]/2)
        y = pt[1] + int(list_images_temp[n].shape[0]/2)

        cv2.circle(img_copy, (x,y), int(radius), color, thickness=5, lineType=8, shift=0)

    return img_copy
