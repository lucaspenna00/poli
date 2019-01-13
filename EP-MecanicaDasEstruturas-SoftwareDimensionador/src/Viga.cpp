#include "Viga.h"
#include "math.h"


Viga::Viga(float Xo, float Yo, float Xf, float Yf, char tipo)
{
  this->Xo = Xo;
  this->Yo = Yo;
  this->Xf = Xf;
  this->Yf = Yf;
  this->tipo = tipo;
}

Viga::~Viga()
{
    //dtor
}

float Viga::obterComprimento(){

    float L;

    L = sqrt( (Xf - Xo)*(Xf - Xo) + (Yf - Yo)*(Yf - Yo) );

    return L;

}

float Viga::obterEspessura(){


    if( this->tipo == 'b')
        /*balanço*/

        return 0.5*(Viga::obterComprimento());

    if( this->tipo == 'i')
        /*tramo interno*/

        return 0.1*(Viga::obterComprimento());

    if( this->tipo == 'e')
        /*tramo externo*/

        return 0.12*(Viga::obterComprimento());
}
