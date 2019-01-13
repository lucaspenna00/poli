#ifndef GRAFICO_H
#define GRAFICO_H
#include "SerieTemporal.h"
#include "Tela.h"
#include "Eixo.h"
#include "EixoDinamico.h"
#include "stdexcept"
#include "SerieNormal.h"

using namespace std;

class Grafico
{
    public:

        Grafico(Eixo* x, Eixo* y, vector<Serie*>* series);

        virtual ~Grafico();

        Eixo* getEixoX();

        Eixo* getEixoY();

        vector<Serie*>* getSeries();

        void desenhar();

    protected:

    Eixo* x;
    Eixo* y;
    vector<Serie*>* series;
};

#endif // GRAFICO_H
