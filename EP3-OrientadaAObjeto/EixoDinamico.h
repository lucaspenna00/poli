#ifndef EIXODINAMICO_H
#define EIXODINAMICO_H
#include "Eixo.h"
#include "Serie.h"
#include "SerieTemporal.h"
#include "list"
#include "SerieNormal.h"

using namespace std;
class EixoDinamico : public Eixo{
    public:
        EixoDinamico(string titulo, double minimoPadrao, double maximoPadrao, list<Serie*>* series, bool orientacaoHorizontal);
        virtual ~EixoDinamico();
        double getMinimo();
        double getMaximo();
    private:
        double serieMinimo;
        double serieMaximo;
        double padraoMinimo;
        double padraoMaximo;

};

#endif // EIXODINAMICO_H
