#ifndef PILAR_H
#define PILAR_H
#include "math.h"

class Pilar
{
    public:

        Pilar(int numeroPilaresX, int numeroPilaresY, char tipo, int identificacao, float DimX, float DimY, int numeroAndaresAcima);
        virtual ~Pilar();

        float obterareaInfluencia();
        /*getters and setters*/
        int identificacao;
        float numeroAndaresAcima;
        float obterDimensao();
        float numeroPilaresX;
        float numeroPilaresY;
        float DimX;
        float DimY;
        char tipo;

         //α = 1,3 → pilares internos ou de extremidade, na direção da maior dimensão;
         //α = 1,5 → pilares de extremidade, na direção da menor dimensão;
         //α = 1,8 → pilares de canto.

};

#endif // PILAR_H
