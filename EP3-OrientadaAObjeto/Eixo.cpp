#include "Eixo.h"
#include <stdexcept>

using namespace std;

Eixo::Eixo(string titulo, double minimo, double maximo, bool orientacaoHorizontal) {
    if (minimo >= maximo)
        throw new runtime_error("Minimo maior que maximo");
    this->titulo = titulo;
    this->minimo = minimo;
    this->maximo = maximo;
    this->orientacaoHorizontal = orientacaoHorizontal;
    //ctor
}

Eixo::~Eixo() {
    //dtor
}
string Eixo::getTitulo() {
    return titulo;
}

bool Eixo::temOrientacaoHorizontal(){
    return orientacaoHorizontal;
}
