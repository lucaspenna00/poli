'''
Item 2-B P1 Professor Doutor Emílio Del Moral Hernandez
Autor: Lucas Penna Saraiva
Data: 03/05/2020

Instalar: Anaconda
Após instalar anaconda, rode os comandos no prompt anaconda

pip install keras
pip install tensorflow

para rodar, rode no prompt

python item2B.property
'''

'''
Nessa etapa preparamos o código para que os dados recebidos pelo Professor
possam ser utilizados nos métodos da biblioteca Keras.
'''
import numpy as np

treino = np.loadtxt("A-treino.txt", skiprows=1)
teste = np.loadtxt("B-teste.txt", skiprows=1)

Y_treino = treino[:,5]
X_treino = treino[:, :5]

Y_alvo= teste[:, 5]
X_teste = teste[:, :5]

NUSP = [9, 7, 7, 0, 5, 6, 6]

'''
Lembrando que para não ter problema de exploding gradient, é necessário normalizar
os dados antes de passá-los como input da Rede Neural Artficial.
Se não normalizar, então provavelmente haverá erro na hora do backpropagation

Nas linhas abaixo, normalizaremos utilizando o método MinMaxScaler
https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
'''

from sklearn.preprocessing import MinMaxScaler

scaler = MinMaxScaler()

X_treino = scaler.fit_transform(X_treino)

Y_treino = ((Y_treino - Y_treino.min())/(Y_treino.max() - Y_treino.min()))

X_teste = scaler.fit_transform(X_teste)

Y_alvo = ((Y_alvo - Y_alvo.min())/(Y_alvo.max() - Y_alvo.min()))

'''
I) Apresente o código e/ou chamada/s para a definição da arquitetura da rede acima. Sempre que usar chamadas
a rotinas ou funções neste e nos itens que seguem, explicite claramente a origem (como você chegou no seu valor,
por exemplo) e o significado de cada parâmetro usado por você na chamada usada na sua resposta.
'''

from keras.models import Sequential

model = Sequential()

from keras.layers import Dense

model.add(Dense(units=sum(NUSP), activation='sigmoid', input_dim=X_treino.shape[1]))

model.add(Dense(units=4, activation='sigmoid'))

model.add(Dense(units=1, activation='linear'))

model.compile(optimizer='adam', loss='mean_squared_error')

'''
II) Idem como acima (código e/ou chamada/s), para o Treino da rede MLP; considere como exemplares de treino
aqueles mesmos do *.txt fornecido a você para a questão de ensaio computacional no MBP.
'''

# x_train and y_train are Numpy arrays --just like in the Scikit-Learn API.
model.fit(X_treino, Y_treino, epochs=500, batch_size=1)

'''
III) Idem como acima (código e/ou chamada/s), para o Teste da rede MLP, com o arquivo de teste pertinente.
'''

Y_rede_neural = model.predict(X_teste)

'''
IV) Idem (código e/ou chamada/s), para a Geração de arquivos com conjuntos de treino e de teste para emprego
da técnica k-fold cross validation, com k=3; Considere como o universo total de dados empíricos de partida para esse
3-fold, a união dos conjuntos dois conjuntos, de treino e de teste, considerados nos itens II e III acima)
'''

#from sklearn.model_selection import cross_val_score

#scores = cross_val_score(model, X, y, cv=3)

'''
V) Idem (código e/ou chamada/s), para o Cálculo de alguma das medidas de qualidade de regressores ou de
reconhecedores que seja DIFERENTE do RMS e do Eqm consideradas no nosso curso.
'''

print("\n----Metricas Calculadas da Rede Neural Conjunto de Teste ------")

from sklearn.metrics import r2_score
print("R2 score:", r2_score(Y_alvo, Y_rede_neural))

from sklearn.metrics import mean_squared_error
print("RMSE: test:", np.sqrt(mean_squared_error(Y_alvo, Y_rede_neural)))

print("Autor: Lucas Penna Saraiva | NUSP: 9770566")
#from scipy.stats import pearsonr
#print("Coef. Corr. Pearson:", pearsonr(Y_alvo, Y_rede_neural))

# Plotar o gráfico Alvo vs Obtido
import matplotlib.pyplot as plt

plt.figure(1)
plt.plot(Y_rede_neural, label="Y_rede_neural")
plt.plot(Y_alvo, label="Y_alvo")
plt.legend()
plt.title("Valor Y_alvo e Y_rede_neural normalizados comparados obtidos com Keras | P1 Emilio Item 2B")
plt.show()
