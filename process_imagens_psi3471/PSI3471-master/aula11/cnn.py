#cnn1.py - grad2020
import tensorflow.keras as keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dropout, Conv2D, MaxPooling2D, Dense, Flatten
from keras import optimizers
import numpy as np
import sys
import os; os.environ['TF_CPP_MIN_LOG_LEVEL']='3'

'''
CONSEGUI ACURÁCIA DE 0.993
E TAXA DE ERRO 0.7% !! UHUU
'''


(AX, AY), (QX, QY) = mnist.load_data()
AX=255-AX; QX=255-QX
nclasses = 10
AY2 = keras.utils.to_categorical(AY, nclasses)
QY2 = keras.utils.to_categorical(QY, nclasses)
nl, nc = AX.shape[1], AX.shape[2] #28, 28

AX = AX.astype('float32') / 255.0 # 0 a 1
QX = QX.astype('float32') / 255.0 # 0 a 1
AX = np.expand_dims(AX,axis=3)
QX = np.expand_dims(QX,axis=3)

model = Sequential()

model.add(Conv2D(32, kernel_size=(3,3), activation='relu', input_shape=(nl, nc, 1) ))
model.add(MaxPooling2D(pool_size=(2,2)))
model.add(Conv2D(32, kernel_size=(3,3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2,2)))

model.add(Flatten())
model.add(Dense(128, activation='relu'))
model.add(Dropout(0.3))
model.add(Dense(nclasses, activation='softmax'))

from keras.utils import plot_model
plot_model(model, to_file='cnn1.png', show_shapes=True)
from keras.utils import print_summary
print_summary(model)

opt=optimizers.Adam()
model.compile(optimizer=opt, loss='categorical_crossentropy', metrics=['accuracy'])
model.fit(AX, AY2, batch_size=300, epochs=50, verbose=True)
score = model.evaluate(QX, QY2, verbose=False)
print('Test loss:', score[0])
print('Taxa de erro:', (1-score[1])*100)
print('Acurácia:', score[1])
model.save('cnn1.h5')
