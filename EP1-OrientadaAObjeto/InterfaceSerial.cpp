#include "InterfaceSerial.h"

// Baseado em http://playground.arduino.cc/Interfacing/CPPWindows

// Parametros da placa
#define BAUD_RATE CBR_9600
#define BYTE_SIZE 8
#define STOP_BITS ONESTOPBIT
#define PARITY NOPARITY

#define WAIT_TIME 500

#define TAMANHO_BUFFER 256
#define HEADER_TITULO 'T'
#define HEADER_DADO 'A'

#include <stdio.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cctype>

using namespace std;



void InterfaceSerial::inicializar(string porta) {
    nomes[0] = "T1";
    nomes[1] = "T2";
    nomes[2] = "T3";
    nomes[3] = "T4";
    nomes[4] = "T5";
}



double InterfaceSerial::getValor (string canal) {
  int valoresT1[] = {100, 20, 30, 40, 50, 60};
  int valoresT2[] = {9, 25, 35, 45, 55, 65};
  int valoresT3[] = {16, 26, 36, 46, 56, 66};
  int valoresT4[] = {17, 27, 37, 47, 57, 67};
  int valoresT5[] = {18, 28, 38, 48, 58, 68};
  if ( canal == "T1") return valoresT1[numerodechamadas];
  if ( canal == "T2") return valoresT2[numerodechamadas];
  if ( canal == "T3") return valoresT3[numerodechamadas];
  if ( canal == "T4") return valoresT4[numerodechamadas];
  if ( canal == "T4") return valoresT5[numerodechamadas];
}

bool InterfaceSerial::atualizar() {
  numerodechamadas++;
  return true;

}


string* InterfaceSerial::getNomeDosCanais() {
  return nomes;
}

int InterfaceSerial::getQuantidadeDeCanais() {
  return 5;
}
