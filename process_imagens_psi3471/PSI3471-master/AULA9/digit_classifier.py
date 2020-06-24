import tensorflow as tf
import numpy as np
from sklearn import svm, metrics
from sklearn.neighbors import KNeighborsClassifier
import cv2

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

## pre-processing the images

'''
Sem pré-processamento, a acurácia da SVM foi de 0.9417. Vamos ver com
os filtros como é que fica. Com mediana e gaussiano, a acurácia caiu para 0.9237.
Vamos tirar o filtro gaussian blur e ver se melhora...
Só filtro mediana a acurácia caiu para 0.9327. Support Vector Machine não funciona tão bem.
Com os dois filtros + um kNN de 10 vizinhos obtive uma acurácia de [FINAL] Acurácia é:  0.968
Sem os dois filtros, essa acurácia cai para 0.9665
Com os dois filtros e numero de vizinhos = 5, acurácia foi de 0.9691!
'''


print("[INFO] Passando filtro mediana nas imagens")

for i in range(0, x_train.shape[0]):

    x_train[i] = cv2.medianBlur(x_train[i], 3)

for i in range(0, x_test.shape[0]):

    x_test[i] = cv2.medianBlur(x_test[i], 3)


print("[INFO] Passando filtro gaussiano nas imagens")
for i in range(0, x_train.shape[0]):

    x_train[i] = cv2.GaussianBlur(x_train[i],(5,5), 0)

for i in range(0, x_test.shape[0]):

    x_test[i] = cv2.GaussianBlur(x_test[i], (5,5), 0)


print("[INFO] Reshapando as imagens")

x_train = x_train.reshape((x_train.shape[0], -1))
x_test = x_test.reshape((x_test.shape[0], -1))

print("[INFO] Normalizando as imagens")

x_train = np.float64(x_train/255.0)
x_test = np.float64(x_test/255.0)

# Create a classifier: a support vector classifier
#model = svm.SVC(gamma=0.001, C=1.0)
model = KNeighborsClassifier(n_neighbors=3, n_jobs=-1)

print("[INFO] Treinando o Classificador")

model.fit(x_train, y_train)

predicted = model.predict(x_test)

print("[FINAL] Acurácia é: ", metrics.accuracy_score(y_test, predicted))
