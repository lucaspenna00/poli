#include "mbed.h"
#include "nRF24L01P.h"
#include <iterator>
#define TRANSFER_SIZE 8
#include "string"
#include "iostream"
#include "vector"

int main() {

    Serial pc(USBTX, USBRX); // tx, rx

    nRF24L01P tx_nrf24l01p(PTD2, PTD3, PTC5, PTD0, PTD5, PTA13);    // mosi, miso, sck, csn, ce, irq

    // resetar placa a cada comando para limpar o buffer
    DigitalOut reset_board(PTC16);

    // led 
    DigitalOut led_go(LED2);

    DigitalOut led_stop(LED1);

    reset_board = 1;
    led_stop = 0;

    // The nRF24L01+ supports transfers from 1 to 32 bytes, but Sparkfun's
    //  "Nordic Serial Interface Board" (http://www.sparkfun.com/products/9019)
    //  only handles 4 byte transfers in the ATMega code.

    char txData[TRANSFER_SIZE];
    int txDataCnt = 0;
    char rxData[5];
    int rxDataCnt = 0;

    tx_nrf24l01p.powerUp();

    // Display the (default) setup of the nRF24L01+ chip

    pc.printf( "\r\n[ INFO] Controle Remoto do Carrinho\r\n" );

    pc.printf( "[ INFO] nRF24L01+ Frequency    : %d MHz\r\n",  tx_nrf24l01p.getRfFrequency() );
    pc.printf( "[ INFO] nRF24L01+ Output power : %d dBm\r\n",  tx_nrf24l01p.getRfOutputPower() );
    pc.printf( "[ INFO] nRF24L01+ Data Rate    : %d kbps\r\n", tx_nrf24l01p.getAirDataRate() );
    pc.printf( "[ INFO] nRF24L01+ TX Address   : 0x%010llX\r\n", tx_nrf24l01p.getTxAddress() );
    pc.printf( "[ INFO] nRF24L01+ RX Address   : 0x%010llX\r\n", tx_nrf24l01p.getRxAddress() );

    pc.printf( "[ INFO] Type keys to test transfers:\r\n  (transfers are grouped into %d characters)\r\n", TRANSFER_SIZE );

    pc.printf(" [ USER INFO] Fornecer input na seguinte forma | Ex: +010+010 para que o carrinho vá pra frente 10cm e vire a direita 10cm \r\n");

    tx_nrf24l01p.setTransferSize( TRANSFER_SIZE );

    tx_nrf24l01p.setReceiveMode();
    tx_nrf24l01p.enable();

    while (1) {

        // If we've received anything over the host serial link...
        if ( pc.readable() ) 

            // ...add  it to the transmit buffer
            txData[txDataCnt++] = pc.getc();

            // If the transmit buffer is full
            if ( txDataCnt >= sizeof( txData ) ) {

                printf("[ INFO] Buffer is full \r \n");

                led_go = 0;
                led_stop = 1;

                // Send the transmitbuffer via the nRF24L01+
                tx_nrf24l01p.write( NRF24L01P_PIPE_P0, txData, txDataCnt );

                txDataCnt = 0;

                wait(1);

                reset_board=0;

            }

          }


}
