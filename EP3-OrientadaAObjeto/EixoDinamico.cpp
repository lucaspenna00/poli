#include "EixoDinamico.h"
#include "Serie.h"
#include "SerieNormal.h"
#include "SerieTemporal.h"
#include <stdexcept>

using namespace std;

EixoDinamico::EixoDinamico(string titulo, double minimoPadrao, double maximoPadrao, list<Serie*>* series, bool orientacaoHorizontal) : Eixo(titulo, minimoPadrao, maximoPadrao ,orientacaoHorizontal) {
    if (series == NULL)
        throw new logic_error("Lista nula");
    if (minimoPadrao >= maximoPadrao)
        throw new runtime_error("minimo maior que maximo");

    if (series->size() == 0){
        serieMinimo = minimoPadrao;
        serieMaximo = maximoPadrao;
    }
    padraoMaximo = maximoPadrao;
    padraoMinimo = minimoPadrao;
    if (series->size() > 0){
        if (orientacaoHorizontal){

            Serie *serie = series->back();
            series->pop_back();
            serieMinimo = serie->getLimiteInferior()->getX();
            serieMaximo = serie->getLimiteSuperior()->getX() ;
            while (series->size() != 0){
                serie = series->back();
                series->pop_back();
                if (serie->getLimiteInferior()->getX() < serieMinimo)
                    serieMinimo = serie->getLimiteInferior()->getX();
                if (serie->getLimiteSuperior()->getX() > serieMaximo)
                    serieMaximo = serie->getLimiteSuperior()->getX();
            }
        }
        else {
            Serie *serie = series->back();
            series->pop_back();
            serieMinimo = serie->getLimiteInferior()->getY();
            serieMaximo = serie->getLimiteSuperior()->getY() ;
            while (series->size() != 0){
                serie = series->back();
                series->pop_back();
                if (serie->getLimiteInferior()->getY() < serieMinimo)
                    serieMinimo = serie->getLimiteInferior()->getY();
                if (serie->getLimiteSuperior()->getY() > serieMaximo)
                    serieMaximo = serie->getLimiteSuperior()->getY();
        }
    }
}
}
EixoDinamico::~EixoDinamico()
{
    //dtor
}
double EixoDinamico::getMinimo(){
    Ponto *pMinimo = new Ponto(1, serieMinimo);
    Ponto *pMaximo = new Ponto(1, serieMaximo);
    if (pMinimo->eIgual(pMaximo)){
        pMinimo->~Ponto();
        pMaximo->~Ponto();
        return padraoMinimo;
    }
    pMinimo->~Ponto();
    pMaximo->~Ponto();
    return serieMinimo;
}
double EixoDinamico::getMaximo(){
    Ponto *pMinimo = new Ponto(1, serieMinimo);
    Ponto *pMaximo = new Ponto(1, serieMaximo);
    if (pMinimo->eIgual(pMaximo)){
        pMinimo->~Ponto();
        pMaximo->~Ponto();
        return padraoMaximo;
    }
    pMinimo->~Ponto();
    pMaximo->~Ponto();
    return serieMaximo;
}
