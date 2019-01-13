#include "Pilar.h"
#include "math.h"

Pilar::Pilar(int numeroPilaresX, int numeroPilaresY, char tipo, int identificacao, float DimX, float DimY, int numeroAndaresAcima)
{
  this->tipo = tipo;
  this->numeroPilaresX = numeroPilaresX;
  this->numeroPilaresY = numeroPilaresY;
  this->identificacao = identificacao;
  this->DimX = DimX;
  this->DimY = DimY;

}

Pilar::~Pilar()
{
    //dtor
}


float Pilar::obterDimensao(){


//α = 1,3 → pilares internos ou de extremidade, na direção da maior dimensão;
                    //α = 1,5 → pilares de extremidade, na direção da menor dimensão;
                //α = 1,8 → pilares de canto.

/* Se for pilar de EXTREMIDADE e CANTO (c), Ai = A*/
/* Se for pilar de EXTREMIDADE (e), Ai = 2A*/
/* Se for pilar de MEIO (m) , Ai = 4A
2.5
*/

float areaSecao;


if (this->tipo == 'c' )

    areaSecao = (30*1,8*Pilar::obterareaInfluencia()*(Pilar::numeroAndaresAcima + 0.7) ) / (2.5+ (0.01*(69,2-2.5)));

if (this->tipo == 'e' )

    areaSecao = (30*1,5*2*Pilar::obterareaInfluencia()*(Pilar::numeroAndaresAcima + 0.7) ) / (2.5+ (0.01*(69,2-2.5)));

if (this->tipo == 'm' )

    areaSecao = (30*1,3*2*4*Pilar::obterareaInfluencia()*(Pilar::numeroAndaresAcima + 0.7) ) / (2.5+ (0.01*(69,2-2.5)));

return sqrt(areaSecao)/100;

}

float Pilar::obterareaInfluencia(){

    return 0.25 * (Pilar::DimX/Pilar::numeroPilaresX) * (Pilar::DimY/Pilar::numeroPilaresY);

}


