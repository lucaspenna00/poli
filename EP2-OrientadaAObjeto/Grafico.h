#ifndef GRAFICO_H
#define GRAFICO_H
#include "SerieTemporal.h"
#include "Tela.h"


using namespace std;

class Grafico
{
    public:

        Grafico(Eixo* x, Eixo* y, Serie* serie);

        virtual ~Grafico();

        Eixo* getEixoX();

        Eixo* getEixoY();

        Serie* getSerie();

        void desenhar();

    protected:

    Eixo *x;
    Eixo *y;
    Serie *serie;
};

#endif // GRAFICO_H
