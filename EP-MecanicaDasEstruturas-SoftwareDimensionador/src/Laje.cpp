#include "Laje.h"

Laje::Laje(float x, float y, int identificacao)
{
    this-> x = x;
    this-> y = y;
    this->identificacao = identificacao;
}

Laje::~Laje()
{
    //dtor
}

float Laje::obterAltura(){


    if( x < y ){

                return (2,5) * x / 100;

    }

    else{

                return (2,5) * 0.7 * y / 100;

    }

}


/*
Para lajes com bordas apoiadas ou engastadas, a altura útil pode ser
estimada por meio da seguinte expressão:
d est = (2,5 – 0,1 x n) . l * /100

n → número de bordas engastadas
l x → menor vão
l y → maior vão
Para lajes com bordas livres, como as lajes em balanço, deve ser utilizado
outro processo.
*/
