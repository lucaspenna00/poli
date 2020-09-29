#include "mbed.h"
#include "nRF24L01P.h"
#include "stdio.h"
#include <algorithm>
#include <cmath>
#include "hcsr04.h"

#define RECEIVER_SIZE 8
#define CONST_CALIBRACAO 1.5
#define SECURITY_LEVEL 8 // 8cm para o carrinho não bater
#define NUM_LEITURAS 9 //  Número de aquisições sensor ultrassonico

// Sensor Infravermelho
InterruptIn  ENCOD1(PTD4);
InterruptIn  ENCOD2(PTA12);

// Ponte H
PwmOut IN1(PTC8);
PwmOut IN2(PTC9);

DigitalOut IN3(PTC3);
DigitalOut IN4(PTC4);

Serial pc(USBTX, USBRX); // tx, rx

// NRF24
nRF24L01P rx_nrf24l01p(PTD2, PTD3, PTC5, PTD0, PTD5, PTA13);    // mosi, miso, sck, csn, ce, irq

// LED DEBUG
DigitalOut led_stop(LED1);
DigitalOut led_go(LED2);

// HCSR04 Ultrassonic
HCSR04 ultrassonic(PTD7, PTD6); //"trigger" and "echo"

char rxData[RECEIVER_SIZE];

int pulses1 = 0, pulses2 = 0;


int read_ultrassonic(){

    // Retorna a mediana de NUM_LEITURAS do sensor ultrassonico
    // Filtro Mediana para pegar ruido

    int leituras[ NUM_LEITURAS ];

    for(int i = 0; i < NUM_LEITURAS; i++){

        ultrassonic.start();
        leituras[i] = ultrassonic.get_dist_cm();
        //printf(" INFO] distance lida: %d \r\n", leituras[i]);

    }

    std::sort(leituras, leituras + NUM_LEITURAS);

    int index = ceil(NUM_LEITURAS / 2.0);

    if ((leituras[index] < 1000) && (leituras[index] > 0)){

        return leituras[index];

    }

    else{

        return read_ultrassonic();

    }
}

void brake(){

    printf("[DEBUG brake] STOP \r\n");

     led_go = 1;
     led_stop = 0;

     IN1.write(1.0f);
     IN2.write(1.0f);

     IN3 = 1;
     IN4 = 1;
}


void go_forward(int dist){

     int start_distance = 0;

     // esperar a distância ser realística para aceitar a leitura

     while(start_distance == 0) start_distance = read_ultrassonic();

     int lida;

     printf("[DEBUG go_forwardward] dist start: %d \r \n", start_distance);

     int start_pulsos, number_pulsos_dist;

     float number_pulsos_dist_aux;

     start_pulsos = pulses1;

     // calcular número de puslsos necessários para atingir a distância desejada

     number_pulsos_dist_aux = CONST_CALIBRACAO*dist;

     printf("[DEBUG go_forwardward] PULSO start: %d \r \n", pulses1);

     number_pulsos_dist = int(number_pulsos_dist_aux);
     
     printf("NUMERO DE PULSOS FORNECIDOS: %d \r \n", number_pulsos_dist);

     int dist_percorrida = 0;

     while(1){

         printf("[ INFO] Distancia lida: %d \r\n", lida);

         printf("[ INFO] Distancia percorida: %d \r\n", dist_percorrida);
         printf("[DEBUG go_forward] Indo para tras. Numero de puslsos: %d \r \n", pulses1-start_pulsos);
         //printf(" INFO] distance lida: %d \r\n", lida);

         led_go = 0;
         led_stop = 1;

         IN3 = 0;
         IN4 = 1;

         // PWM no MOTOR A, PARA CORRIGIR VELOCIDADE
         IN1 = 0;
         IN2.write(0.92f); 

         lida = read_ultrassonic();

         if (lida > 0){

            dist_percorrida = abs(start_distance - lida);

        }

         if ((lida <= SECURITY_LEVEL) && (lida > 0)){

            // CASO HOUVER UM OBSTÁCULO, QUEBRAR O LOOP E PARAR O CARRINHO

            printf("[ INFO] SAIU POR CAUSA DO SECURITY . Lida: %d \r\n", lida);
            break;

        }
        
        if (pulses1 - start_pulsos > number_pulsos_dist) break;
        if (dist_percorrida > dist) break;

        }

        //printf("SAIU DO LOOP\r\n");

        brake();
    }


void go_backward(int dist){

     int start_pulsos, number_pulsos_dist;

     float number_pulsos_dist_aux;

     start_pulsos = pulses1;

     number_pulsos_dist_aux = CONST_CALIBRACAO*dist;

     printf("[DEBUG go_backward] PULSO start: %d \r \n", pulses1);

     number_pulsos_dist = int(number_pulsos_dist_aux);


     while(pulses1 - start_pulsos <= number_pulsos_dist){

         printf("[DEBUG go_backward] Indo para tras. Numero de puslsos: %d \r \n", pulses1-start_pulsos);

         led_go = 0;
         led_stop = 1;

         IN3 = 1;
         IN4 = 0;

         // PWM no MOTOR A, PARA CORRIGIR VELOCIDADE
         IN1 = 0;
         IN2.write(0.9f); 


    }

    brake();
}

void turn_left(){

     int start_pulsos;

     start_pulsos = pulses1;

     while(pulses1 - start_pulsos <= 34){

         printf("[DEBUG turn_left] Turning Left. Numero de puslsos: %d \r \n", pulses1-start_pulsos);

         led_go = 0;
         led_stop = 1;

         IN1 = 0;
         IN2 = 1;

         IN3 = 1;
         IN4 = 1;

    }

    brake();

}


void turn_right(){

     int start_pulsos;

     start_pulsos = pulses2;

     while(pulses2 - start_pulsos <= 31){

         printf("[DEBUG turn_left] Turning Right. Numero de puslsos: %d \r \n", pulses2-start_pulsos);

         led_go = 0;
         led_stop = 1;

         IN1 = 1;
         IN2 = 1;

         IN3 = 0;
         IN4 = 1;

    }

    brake();

}


void count1(){
    pulses1++;
    wait(0.005);
}


void count2(){
    pulses2++;
    wait(0.005);
}


int main() {

    // The nRF24L01+ supports transfers from 1 to 32 bytes, but Sparkfun's
    //  "Nordic Serial Interface Board" (http://www.sparkfun.com/products/9019)
    //  only handles 4 byte transfers in the ATMega code.
    int rxDataCnt = 0;

    IN1.period(0.001f);      
    IN2.period(0.001f);  

    rx_nrf24l01p.powerUp();

    // Display the (default) setup of the nRF24L01+ chip
    pc.printf( "[ INFO] FIRMWARE CARRINHO \r\n" );

    pc.printf( "[ INFO] nRF24L01+ Frequency    : %d MHz\r\n",  rx_nrf24l01p.getRfFrequency() );
    pc.printf( "[ INFO] nRF24L01+ Output power : %d dBm\r\n",  rx_nrf24l01p.getRfOutputPower() );
    pc.printf( "[ INFO] nRF24L01+ Data Rate    : %d kbps\r\n", rx_nrf24l01p.getAirDataRate() );
    pc.printf( "[ INFO] nRF24L01+ TX Address   : 0x%010llX\r\n", rx_nrf24l01p.getTxAddress() );
    pc.printf( "[ INFO] nRF24L01+ RX Address   : 0x%010llX\r\n", rx_nrf24l01p.getRxAddress() );

    rx_nrf24l01p.setTransferSize( RECEIVER_SIZE );

    rx_nrf24l01p.setReceiveMode();
    rx_nrf24l01p.enable();

    led_go = 1;
    led_stop = 1;

    ENCOD1.rise(&count1);

    ENCOD2.rise(&count2);

    int dist_x, dist_y;

    while (1) {

        //printf("\r\n[ main INFO] distance lida: %d", read_ultrassonic());

        // If we've received anything in the nRF24L01+...
        if ( rx_nrf24l01p.readable() ) {

            // ...read the data into the receive buffer
            rxDataCnt = rx_nrf24l01p.read( NRF24L01P_PIPE_P0, rxData, sizeof( rxData ) );

            // Display the receive buffer contents via the host serial link

            for ( int i = 0; rxDataCnt > 0; rxDataCnt--, i++ ) {

                pc.putc( rxData[i] );
            }


            char dist_char_x[3], dist_char_y[3];

            dist_char_x[0] = rxData[1];
            dist_char_x[1] = rxData[2];
            dist_char_x[2] = rxData[3];

            dist_char_y[0] = rxData[5];
            dist_char_y[1] = rxData[6];
            dist_char_y[2] = rxData[7];

            sscanf(dist_char_x, "%d", &dist_x);
            sscanf(dist_char_y, "%d", &dist_y);

            // + Vai pra frente | + Vai pra direita

            if ( (rxData[0] == '+') && (rxData[4] == '+') ){

              if (dist_x > 0){

                go_forward(dist_x);

              }

              if (dist_y > 0){

                turn_right();

                go_forward(dist_y);
              }

            }

            // + Vai pra frente | - Vai pra esquerda

            if ( (rxData[0] == '+') && (rxData[4] == '-') ){

              if (dist_x > 0){

                go_forward(dist_x);

              }

              if (dist_y > 0){

                turn_left();
                  
                go_forward(dist_y);
              }

            }

            // - Vai pra trás | + Vai pra direita

            if ((rxData[0] == '-') && (rxData[4] == '+')){

              if (dist_x > 0){

                go_backward(dist_x);

              }

              if (dist_y > 0){

                turn_right();
                  
                go_forward(dist_y);
              }


            }

            // - Vai pra trás | - Vai pra esquerda

            if ((rxData[0] == '-') && (rxData[4] == '-')){


              if (dist_x > 0){

                go_backward(dist_x);

              }

              if (dist_y > 0){

                turn_left();
                  
                go_forward(dist_y);
              }

            }

        }

    }

}

