#include "mbed.h"
#include "nRF24L01P.h"
#include "stdio.h"
#include "string"
#include <iterator>
#include <stdlib.h>
#include <string.h>

#define RECEIVER_SIZE 4
#define CONST_CALIBRACAO 1.40

// Sensor Infravermelho
InterruptIn  ENCOD1(PTD4);
InterruptIn  ENCOD2(PTA12);

// Ponte H
DigitalOut IN1(PTC7);
DigitalOut IN2(PTC0);
DigitalOut IN3(PTC3);
DigitalOut IN4(PTC4);

Serial pc(USBTX, USBRX); // tx, rx

// NRF24
nRF24L01P rx_nrf24l01p(PTD2, PTD3, PTC5, PTD0, PTD5, PTA13);    // mosi, miso, sck, csn, ce, irq

// LED DEBUG
DigitalOut led_stop(LED1);
DigitalOut led_go(LED2);

char rxData[RECEIVER_SIZE];

int pulses1 = 0, pulses2 = 0;

void brake(){

	printf("[DEBUG brake] STOP \r\n");

     led_go = 1;
     led_stop = 0;

     IN1 = 1;
     IN2 = 1;

     IN3 = 1;
     IN4 = 1;

}


void go_forward(int dist){

	 int start_pulsos, number_pulsos_dist;

	 float number_pulsos_dist_aux;

	 start_pulsos = pulses1;

	 number_pulsos_dist_aux = CONST_CALIBRACAO*dist;

	 printf("[DEBUG go_forward] PULSO start: %d \r \n", pulses1);

	 number_pulsos_dist = int(number_pulsos_dist_aux);

	 while(pulses1 - start_pulsos <= number_pulsos_dist){

		 printf("[DEBUG go_forward] Indo para a frente. Numero de puslsos: %d \r \n", pulses1-start_pulsos);

	     led_go = 0;
	     led_stop = 1;

	     IN3 = 0;
	     IN4 = 1;

	     // PWM no MOTOR A, PARA CORRIGIR VELOCIDADE

	     IN1 = 1;
	     IN2 = 1;

	     wait(0.0098);

	     IN1 = 0;
	     IN2 = 1;

	     wait(0.0002);

    }

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

	     IN1 = 1;
	     IN2 = 1;

	     wait(0.0098);

	     IN1 = 1;
	     IN2 = 0;

	     wait(0.0002);


    }

    brake();
}

void turn_left(){

	 int start_pulsos;

     start_pulsos = pulses1;

     while(pulses1 - start_pulsos <= 26){

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

     while(pulses2 - start_pulsos <= 23){

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

    rx_nrf24l01p.powerUp();

    // Display the (default) setup of the nRF24L01+ chip
    pc.printf( "FIRMWARE CARRINHO \r\n" );

    pc.printf( "nRF24L01+ Frequency    : %d MHz\r\n",  rx_nrf24l01p.getRfFrequency() );
    pc.printf( "nRF24L01+ Output power : %d dBm\r\n",  rx_nrf24l01p.getRfOutputPower() );
    pc.printf( "nRF24L01+ Data Rate    : %d kbps\r\n", rx_nrf24l01p.getAirDataRate() );
    pc.printf( "nRF24L01+ TX Address   : 0x%010llX\r\n", rx_nrf24l01p.getTxAddress() );
    pc.printf( "nRF24L01+ RX Address   : 0x%010llX\r\n", rx_nrf24l01p.getRxAddress() );

    rx_nrf24l01p.setTransferSize( RECEIVER_SIZE );

    rx_nrf24l01p.setReceiveMode();
    rx_nrf24l01p.enable();

    led_go = 1;
    led_stop = 1;

    ENCOD1.rise(&count1);

    ENCOD2.rise(&count2);


    while (1) {

        // If we've received anything in the nRF24L01+...
        if ( rx_nrf24l01p.readable() ) {

            // ...read the data into the receive buffer
            rxDataCnt = rx_nrf24l01p.read( NRF24L01P_PIPE_P0, rxData, sizeof( rxData ) );

            // Display the receive buffer contents via the host serial link

            for ( int i = 0; rxDataCnt > 0; rxDataCnt--, i++ ) {

                pc.putc( rxData[i] );
            }

            int dist;

            char dist_char[3];

            dist_char[0] = rxData[1];
            dist_char[1] = rxData[2];
            dist_char[2] = rxData[3];

            sscanf(dist_char, "%d", &dist);


            if (rxData[0] == 'w'){

              go_forward(dist);


            }

            if (rxData[0] == 'b'){

              brake();


            }

            if (rxData[0] == 's'){

              go_backward(dist);


            }

            if (rxData[0] == 'a'){

               turn_left();	

            }

            if (rxData[0] == 'd'){

            	turn_right();

            }




        }

       

    }

}
