#include "Grafico.h"
#include "stdexcept"
#include <iostream>
using namespace std;
Grafico::Grafico(Eixo* x, Eixo* y, vector<Serie*>* series)
{
    if (x->temOrientacaoHorizontal() == false || y->temOrientacaoHorizontal() == true)
        throw new logic_error("orientacao do eixo errada");
    if (series == NULL)
        throw new logic_error("vetor series nulo");
    this->x = x;
    this->y = y;
    this->series = series;

}

Grafico::~Grafico(){}

Eixo* Grafico::getEixoX(){

return x;
}

Eixo* Grafico::getEixoY(){

return y;
}

vector<Serie*>* Grafico::getSeries(){
    return series;
}

void Grafico::desenhar(){

    Tela* t = new Tela;

    t->setEixoX(x->getTitulo(), x->getMinimo(), x->getMaximo());

    t->setEixoY(y->getTitulo(), y->getMinimo(), y->getMaximo());


    for (int i = 0; i < series->size(); i++){
            string nomeserie = series->at(i)->getNome();
            for (int j = 0; j < series->at(i)->getQuantidade(); j++){
                t->plotar(nomeserie, series->at(i)->getPosicao(j)->getX(),series->at(i)->getPosicao(j)->getY());
            }

            }

    t->mostrar();
    t->~Tela();
}
