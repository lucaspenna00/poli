#include "mbed.h"
#include "nRF24L01P.h"
#include "stdio.h"
#include "string"
#include <iterator>
#include <stdlib.h>
#include <string.h>

#define RECEIVER_SIZE 1

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

int pulses1 = 0, pulses2 = 0;

void go_backward(){

     led_go = 0;
     led_stop = 1;

     IN1 = 1;
     IN2 = 0;

     IN3 = 1;
     IN4 = 0;
}

void go_forward(){

     led_go = 0;
     led_stop = 1;

     IN1 = 0;
     IN2 = 1;

     IN3 = 0;
     IN4 = 1;
}

void go_forward_right(){

     led_go = 0;
     led_stop = 1;

     IN1 = 1;
     IN2 = 0;

     IN3 = 1;
     IN4 = 1;
}

void go_backward_right(){

     led_go = 0;
     led_stop = 1;

     IN1 = 0;
     IN2 = 1;

     IN3 = 1;
     IN4 = 1;
}


void go_forward_left(){

     led_go = 0;
     led_stop = 1;

     IN1 = 1;
     IN2 = 1;

     IN3 = 1;
     IN4 = 0;

}

void go_backward_left(){

     led_go = 0;
     led_stop = 1;

     IN1 = 1;
     IN2 = 1;

     IN3 = 0;
     IN4 = 1;

}

void brake(){

     led_go = 1;
     led_stop = 0;

     IN1 = 1;
     IN2 = 1;

     IN3 = 1;
     IN4 = 1;

}

void count1(){
    pulses1++;
    wait(0.005);
}


void count2(){
    pulses2++;
    wait(0.005);
}

int count_numbers ( int num) {
   int count =0;
   while (num !=0) {
      count++;
      num/=10;
   }
   return count;
}


int main() {

    // The nRF24L01+ supports transfers from 1 to 32 bytes, but Sparkfun's
    //  "Nordic Serial Interface Board" (http://www.sparkfun.com/products/9019)
    //  only handles 4 byte transfers in the ATMega code.


    char rxData[RECEIVER_SIZE];
    int rxDataCnt = 0;
    int numero_pulsos_transmitidos;
    int pulse_start;
    int pulse_end;
    int number_pulses;
    int char_anterior;

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

    bool flag = 0;

    while (1) {

        // If we've received anything in the nRF24L01+...
        if ( rx_nrf24l01p.readable() ) {

            // ...read the data into the receive buffer
            rxDataCnt = rx_nrf24l01p.read( NRF24L01P_PIPE_P0, rxData, sizeof( rxData ) );

            // Display the receive buffer contents via the host serial link

            for ( int i = 0; rxDataCnt > 0; rxDataCnt--, i++ ) {

                pc.putc( rxData[i] );
            }


            if (rxData[0] == 'w'){


              go_forward();
              flag = 0;


            }

            if (rxData[0] == 'b'){

              brake();
              flag = 0;


            }

            if (rxData[0] == 's'){

              go_backward();
              flag = 0;


            }

            if (rxData[0] == 'p'){

              pulse_start = pulses1;
              flag = 0;


            }

            if (rxData[0] == 'e'){

              pulse_end = pulses1;
              flag = 1;

            }

        }

        // if comando mudar

        if (flag == 1){

          numero_pulsos_transmitidos = pulse_end - pulse_start;

          printf("[debug1] numero pulsos int: %d \n\r", numero_pulsos_transmitidos);

          char txData[5];

          sprintf(txData, "%d", numero_pulsos_transmitidos);

          int len = count_numbers(numero_pulsos_transmitidos);

          printf("[debug3] len: %d \n\r", len);

          printf("[debu2] Numero de Pulsos char: %s \n\r", txData);

          rx_nrf24l01p.write( NRF24L01P_PIPE_P0, txData, sizeof(txData));

        }

    }

}
