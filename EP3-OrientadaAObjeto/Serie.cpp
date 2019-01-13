#include "Serie.h"
#include <iostream>

using namespace std;

Serie::Serie(string nome, string nomeDoCanalX, string nomeDoCanalY){

    this->nome = nome;
    this->nomeDoCanalX = nomeDoCanalX;
    this->nomeDoCanalY = nomeDoCanalY;
    pontos = new vector<Ponto*>();

}

Serie::~Serie(){}

string Serie::getNome()
{
    return nome;
}

string Serie::getNomeDoCanalX()
{
    return nomeDoCanalX;
}

string Serie::getNomeDoCanalY()
{
    return nomeDoCanalY;
}

bool Serie::estaVazia()
{

    if (getQuantidade() != 0)

        return false;

    else

        return true;
}

int Serie::getQuantidade(){

    return pontos->size();

}


Ponto* Serie::getLimiteSuperior(){
    double Maximo_X;
    double Maximo_Y;

if(estaVazia() == true) throw runtime_error("A serie esta vazia!");
else{
    Ponto* p = pontos->at(0);
    Maximo_X = p->getX();

    Maximo_Y = p->getY();

    for(int i=0; i< pontos->size(); i++){
        p = pontos->at(i);
        if(p->getX() > Maximo_X)
            Maximo_X = p->getX();
        if(p->getY() > Maximo_Y)
            Maximo_Y = p->getY();
    }

    Ponto *pmax = new Ponto(Maximo_X, Maximo_Y);

    return pmax;}
}

Ponto* Serie::getLimiteInferior(){

if(estaVazia() == true) throw runtime_error("A serie esta vazia!");
else{
    Ponto* p = pontos->at(0);
    double Minimo_X = p->getX();

    double Minimo_Y = p->getY();

    for(int i=0; i< pontos->size(); i++){
        p = pontos->at(i);
        if(p->getX() < Minimo_X)
            Minimo_X = p->getX();
        if(p->getY() < Minimo_Y)
            Minimo_Y = p->getY();
    }

    Ponto *pmax = new Ponto(Minimo_X, Minimo_Y);

    return pmax;}
}

Ponto* Serie::getPosicao(int posicao){

    if(posicao > pontos->size() || posicao < 0) throw new out_of_range("Posicao invalida");
    else{

        for(int i = 0; i<pontos->size(); i++){

            if(i == posicao){

                Ponto *p = pontos->at(i);
                return p;
            }
        }
    }
}

vector<Ponto*>* Serie::getPontos(){

    return pontos;
}

void Serie::imprimir(){

    cout<< "Serie " << nome <<endl;

    for(int i = 0; i<pontos->size(); i++){
        Ponto *p = pontos->at(i);
        cout<< "(" << p->getX() << ", " << p->getY() << ")" <<endl;

}
}
