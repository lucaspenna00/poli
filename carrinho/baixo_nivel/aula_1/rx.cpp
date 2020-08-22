#include "mbed.h"
#include "nRF24L01P.h"
#define TRANSFER_SIZE 1

int main() {

    // The nRF24L01+ supports transfers from 1 to 32 bytes, but Sparkfun's
    //  "Nordic Serial Interface Board" (http://www.sparkfun.com/products/9019)
    //  only handles 4 byte transfers in the ATMega code.

    Serial pc(USBTX, USBRX); // tx, rx

    nRF24L01P rx_nrf24l01p(PTD2, PTD3, PTC5, PTD0, PTD5, PTA13);    // mosi, miso, sck, csn, ce, irq

    DigitalOut led_receiver(LED1);

    char rxData[TRANSFER_SIZE];
    int rxDataCnt = 0;

    rx_nrf24l01p.powerUp();

    // Display the (default) setup of the nRF24L01+ chip
    pc.printf( "Sou o Receptor \r\n" );

    pc.printf( "nRF24L01+ Frequency    : %d MHz\r\n",  rx_nrf24l01p.getRfFrequency() );
    pc.printf( "nRF24L01+ Output power : %d dBm\r\n",  rx_nrf24l01p.getRfOutputPower() );
    pc.printf( "nRF24L01+ Data Rate    : %d kbps\r\n", rx_nrf24l01p.getAirDataRate() );
    pc.printf( "nRF24L01+ TX Address   : 0x%010llX\r\n", rx_nrf24l01p.getTxAddress() );
    pc.printf( "nRF24L01+ RX Address   : 0x%010llX\r\n", rx_nrf24l01p.getRxAddress() );

    rx_nrf24l01p.setTransferSize( TRANSFER_SIZE );

    rx_nrf24l01p.setReceiveMode();
    rx_nrf24l01p.enable();

    led_receiver = 1;

    while (1) {

        // If we've received anything in the nRF24L01+...
        if ( rx_nrf24l01p.readable() ) {

            // ...read the data into the receive buffer
            rxDataCnt = rx_nrf24l01p.read( NRF24L01P_PIPE_P0, rxData, sizeof( rxData ) );

            // Display the receive buffer contents via the host serial link
            for ( int i = 0; rxDataCnt > 0; rxDataCnt--, i++ ) {

                pc.putc( rxData[i] );
            }

            if (rxData[0] == '1'){

                led_receiver = 0;

            }

            if (rxData[0] == '0'){

                led_receiver = 1;

            }

        }

    }

}
