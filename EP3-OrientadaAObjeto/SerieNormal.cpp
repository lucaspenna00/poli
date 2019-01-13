#include "SerieNormal.h"
#include "Serie.h"
#include "vector"

using namespace std;
SerieNormal::SerieNormal(string nome, string nomeDoCanalX, string nomeDoCanalY) : Serie(nome, nomeDoCanalX, nomeDoCanalY)
{
}

SerieNormal::~SerieNormal()
{
    //dtor
}
void SerieNormal::adicionar(double x, double y){
    Ponto *p = new Ponto(x, y);
    pontos->push_back (p);
}
