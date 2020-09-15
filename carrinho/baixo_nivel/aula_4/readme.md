# Aula 4 - Implementação do Sensor HCSR04

Queremos utilizar o HCSR04 como um sensor auxiliar para medir distâncias e evitar colisões.

O princípio de funcionamento do HC-SR04 consiste na emissão de sinais ultrassônicos pelo sensor e na leitura do sinal de retorno (reflexo/eco) desse mesmo sinal. A distância entre o sensor e o objeto que refletiu o sinal é calculada com base no tempo entre o envio e leitura de retorno.

Distância  = (Tempo de duração do sinal de saída * velocidade do som) / 2

<img src=hcsr04.png width=50%>

No nosso circuito, a conexão do HCSR04 foi feita da seguinte forma na KL25Z.

<img src=SENSOR_ULTRASSONICO_CIRCUITO.png width=50%>
