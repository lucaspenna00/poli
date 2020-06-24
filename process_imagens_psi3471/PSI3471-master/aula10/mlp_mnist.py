# mlp2.py
import tensorflow.keras as keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Flatten
from keras import optimizers
import numpy as np
import tensorflow as tf

'''
Com as mudanças executadas, obteve-se:
[INFO] Loss: 0.26763527915125485
[INFO] Accuracy: 0.9818999767303467
'''


(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

x_train = x_train.astype('float32') / 255.0 # 0 a 1
x_test = x_test.astype('float32') / 255.0 # 0 a 1

nclasses = 10
y_train = keras.utils.to_categorical(y_train, nclasses)
y_test  = keras.utils.to_categorical(y_test, nclasses)

model = Sequential()
model.add(Flatten(input_shape=(x_train.shape[1], x_train.shape[2]))) # 28x28
model.add(Dense(256, activation='relu'))
model.add(Dense(256, activation='relu'))
model.add(Dense(256, activation='relu'))
model.add(Dense(256, activation='relu'))
model.add(Dense(nclasses, activation='softmax'))

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

model.fit(x_train, y_train, batch_size=50, epochs=100, verbose=True);

score = model.evaluate(x_test, y_test, verbose=False)

print('[INFO] Loss:', score[0])
print('[INFO] Accuracy:', score[1])
