#include "EixoEstatico.h"
#include <stdexcept>

using namespace std;
EixoEstatico::EixoEstatico(string titulo, double minimo, double maximo, bool orientacaoHorizontal) : Eixo(titulo, minimo, maximo, orientacaoHorizontal)
{
    if (minimo >= maximo)
        throw new runtime_error("Minimo maior que maximo");
}

EixoEstatico::~EixoEstatico()
{
    //dtor
}
double EixoEstatico::getMinimo(){
    return minimo;
}

double EixoEstatico::getMaximo(){
    return maximo;
}
