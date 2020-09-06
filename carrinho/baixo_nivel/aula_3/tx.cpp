#include "mbed.h"
#include "nRF24L01P.h"
#include <iterator>
#define TRANSFER_SIZE 4
#define RECEIVER_SIZE 1
#include "string"
#include "iostream"
#include "vector"

int main() {

    Serial pc(USBTX, USBRX); // tx, rx

    nRF24L01P tx_nrf24l01p(PTD2, PTD3, PTC5, PTD0, PTD5, PTA13);    // mosi, miso, sck, csn, ce, irq

    // The nRF24L01+ supports transfers from 1 to 32 bytes, but Sparkfun's
    //  "Nordic Serial Interface Board" (http://www.sparkfun.com/products/9019)
    //  only handles 4 byte transfers in the ATMega code.

    char txData[TRANSFER_SIZE];
    int txDataCnt = 0;
    char rxData[5];
    int rxDataCnt = 0;

    tx_nrf24l01p.powerUp();

    // Display the (default) setup of the nRF24L01+ chip

    pc.printf( "Sou o Transmissor \r\n" );

    pc.printf( "nRF24L01+ Frequency    : %d MHz\r\n",  tx_nrf24l01p.getRfFrequency() );
    pc.printf( "nRF24L01+ Output power : %d dBm\r\n",  tx_nrf24l01p.getRfOutputPower() );
    pc.printf( "nRF24L01+ Data Rate    : %d kbps\r\n", tx_nrf24l01p.getAirDataRate() );
    pc.printf( "nRF24L01+ TX Address   : 0x%010llX\r\n", tx_nrf24l01p.getTxAddress() );
    pc.printf( "nRF24L01+ RX Address   : 0x%010llX\r\n", tx_nrf24l01p.getRxAddress() );

    pc.printf( "Type keys to test transfers:\r\n  (transfers are grouped into %d characters)\r\n", TRANSFER_SIZE );

    tx_nrf24l01p.setTransferSize( 5 );

    tx_nrf24l01p.setReceiveMode();
    tx_nrf24l01p.enable();

    printf(" PRESSIONE P para inicializar uma contagem de pulsos \n\r");

    while (1) {

        // If we've received anything over the host serial link...
        if ( pc.readable() ) 

            // ...add  it to the transmit buffer
            txData[txDataCnt++] = pc.getc();

            // If the transmit buffer is full
            if ( txDataCnt >= sizeof( txData ) ) {

                printf(" Buffer is full \n\r");

                // Send the transmitbuffer via the nRF24L01+
                tx_nrf24l01p.write( NRF24L01P_PIPE_P0, txData, txDataCnt );

                txDataCnt = 0;

                wait(2);
            }

          }


}
