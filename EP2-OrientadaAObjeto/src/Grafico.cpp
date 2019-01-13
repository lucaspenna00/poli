#include "Grafico.h"

Grafico::Grafico(Eixo* x, Eixo* y, Serie* serie)
{
    this->x = x;
    this->y = y
    this->serie = serie}

Grafico::~Grafico()
{}

Eixo* getEixoX(){

return x;
}

Eixo* getEixoY(){

return y;
}

Serie* getSerie(){

return serie;

}

void desenhar(){

    Tela* t = new Tela;

    t->setEixoX(x->getTitulo(), x->getMinimo(), x->getMaximo());

    t->setEixoY(y->getTitulo(), y->getMinimo(), y->getMaximo());


    for(i = 0; i < serie->getQuantidade(); i++)

    t->plotar( serie->getNome(), serie  )


}
