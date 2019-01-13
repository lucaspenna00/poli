#include "Ponto.h"
#include <iostream>
using namespace std;
Ponto::Ponto(double x, double y){
    this->x = x;
    this->y = y;
}
Ponto::~Ponto(){}

double Ponto::getX(){
    return x;
}
double Ponto::getY(){
    return y;
}
void Ponto::imprimir(){
    cout << "(" << x << ", " << y << ")" << endl;
}
bool Ponto::eIgual(Ponto* outro){
    double difx;
    double dify;
    difx = outro->getX() - x;
    dify = outro->getY() - y;
    if (difx < 0)
        difx = -difx;
    if (dify < 0)
        dify = -dify;
    if (difx < 0.00001 && dify < 0.00001)
        return true;
    else return false;
}
