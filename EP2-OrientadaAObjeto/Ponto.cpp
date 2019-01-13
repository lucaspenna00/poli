#include "Ponto.h"
#include <iostream>
using namespace std;

double Ponto::getX(){
    return x;
}
double Ponto::getY(){
    return y;
}
void Ponto::setX(double x){
    this->x = x;
}
void Ponto::setY(double y){
    this->y = y;
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
