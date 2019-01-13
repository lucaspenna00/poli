#include "SerieTemporal.h"
#include "math.h"

SerieTemporal::SerieTemporal(string Nome, string NomeDoCanalX, string NomeDoCanalY) : Serie(Nome, "Tempo", NomeDoCanalY)
{ this->instante = 0;}

SerieTemporal::~SerieTemporal()
{}

int SerieTemporal::existePontoIgual(double instante){

    for(i = 0; i<NUMERO_MAXIMO_VALORES; i++){
        if(fabs(Armazena_X[i] - instante) < 0.00001)
            return i;
    }
return -1;
}

void SerieTemporal::adicionar(double valor){

 if(Serie::getQuantidade() != NUMERO_MAXIMO_VALORES){

    if(existePontoIgual(instante) == -1){
        this->instante = this->instante + 1;
        Serie::adicionar(instante, valor);
    }
    else{

        Armazena_X[existePontoIgual()] = instante;
        Armazena_Y[existePontoIgual()] = valor;
    }
  }
}

void SerieTemporal::adicionar(double instante, double y){

if(instante >= 1){
 if(Serie::getQuantidade() != NUMERO_MAXIMO_VALORES)

    if(existePontoIgual(instante) == -1)

        Serie::adicionar(instante, y);

    else
    {
        Armazena_X[existePontoIgual()] = instante;
        Armazena_Y[existePontoIgual()] = y;
    }
}
}
