import cv2
import numpy as np
from img_transf import get_placa_proibido
import time
import os.path
from os import path
import argparse

def main(IMAGE_PATH):

    start_time = time.time()

    if path.exists(str(IMAGE_PATH)):

        img = cv2.imread(IMAGE_PATH)

    else:

        print("[ ERROR] Imagem não existe. Tente outro diretório.")
        return 0

    template = cv2.imread("template.png")

    img = get_placa_proibido(img, template, threshold_placa=0.4, MAX_SIZE=300, q=0.98, save_temp=False, N=130)

    print("[ INFO] O programa demorou %s segundos para rodar!" % (time.time() - start_time))

    cv2.imshow("Placa detectada", img)

    k=cv2.waitKey(0)

parser = argparse.ArgumentParser()
parser.add_argument("input", help="diretorio relativo da imagem ou absoluto")
args = parser.parse_args()
IMAGE_PATH = args.input

main(IMAGE_PATH)
