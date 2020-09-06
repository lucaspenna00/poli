### Escola Politécnica da USP
## Laboratório de Sistemas Eletrônicos
## Aula 3 - Controle do Carrinho por distância e adição de curvas 90º

# 1. Controle do Carrinho por Distância

Para se controlar o carrinho por distância, utilizou-se a calibração feita na última aula. 
Conta-se os pulsos do sensor infrared equivalentes a uma distância conhecida e estabelece-se uma relação linear.

Para que o carrinho obedeça o usuário,  necessário fornecer o comando no transmissor da seguinte forma:

**CHAR_COMANDO + DIST_CM.**

Por exemplo:

```bash
w100

# Fará o carrinho andar 100 cm para a frente
```

```bash
s050

# Fará o carrinho andar 50 cm para trás
```

> Dividir a tela cdigo + readme

No código _controle_remoto.cpp_ (equivalente ao firmware do carrinho), encontra-se um parâmetro definido como CONST_CALIBRACAO,
que nada mais é do que o número de pulsos equivalente a 1 metro de distância dividido por 100.

A mudança em relação a aula 2 ficou na adição de um parâmetro distância nas funções de controle. As funçes _go_forward()_ e _go_backward()_
ganharam um novo parâmetro: dist. Esse parâmetro é um número inteiro convertido a partir dos três chars fornecidos no comando do transmissor.

Assim, essa distância e convertida em número de pulsos utilizando a CONST_CALIBRACAO e um loop é estabelecido, mandando o carrinho para frente.
Nesse loop, controla-se o motor na condição proposta at que o número de pulsos seja maior que o equivalente à distância fornecida.

Além disso, nas funçes go_forward() e go_backward(), adicionou-se um controle PWM no motor A. Adicionou-se esse PWM de forma a corrigir a velocidade do motor A que estava mais rápida que o motor B, levando o carrinho a executar 
trajetórias tortas. Esse PWM foi feito da seguinte maneira:

<img src=pwm.png>

Após o loop acabar, o freio é acionado e o carrinho então para.

No gif abaixo, uma trajetória foi fornecida ao carrinho: primeiro, andar 100cm para a frente. Após isso, fazer uma curva de 90º para a direita.
Após a curva de 90º para a direita, caminhar 50cm para frente. Por fim, ré de 50cm.

> ADD GIF

# 2. Curvas 

Para realizar a curva a estratégia utilizada foi a seguinte: travou-se uma das rodas e a outra girando, de forma a gerar um torque que provocaria a rotação do carrinho.
Para estimar o número de pulsos necessários para o giro do carrinho, formulei o problema da seguinte maneira:

<img src=curva.png>

Assim, fizemos a função _turn_right()_ que vai para a direita e _turn_left()_ que vai para a esquerda.

### Carrinho fazendo curva para a direita:

> ADD GIF

### Carrinho fazendo curva para a esquerda:

> ADD GIF

Nessa aula atingimos o objetivo. Obrigado e até a próxima!
