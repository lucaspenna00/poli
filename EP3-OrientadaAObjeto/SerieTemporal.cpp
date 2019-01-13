#include "SerieTemporal.h"

using namespace std;

int SerieTemporal::instante = 0;
SerieTemporal::SerieTemporal(string nome, string nomeDoCanalY) : Serie(nome, "Tempo", nomeDoCanalY)
{

}

SerieTemporal::~SerieTemporal()
{}


void SerieTemporal::adicionar(double valor){

    /**VERIFICAR SE HÁ PONTO IGUAL **/
    //IF(ponto igual, adicionar ali//
    //else
    instante++;
    Ponto *p = new Ponto(instante, valor);
    pontos->push_back (p);

}


