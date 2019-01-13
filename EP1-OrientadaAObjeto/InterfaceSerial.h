#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#define ESPERA 500

#include <string>
#include <windows.h>

using namespace std;


class InterfaceSerial {
public:

  void inicializar(string porta);

  double getValor (string canal);


  bool atualizar();

  string* getNomeDosCanais();

  int getQuantidadeDeCanais();

private:
  // Metodos internos, de apoio

  string nomes [5];
int numerodechamadas = -1;
};

#endif // INTERFACESERIAL_H
