#include "Serie.h"
#include <iostream>

Serie::Serie(){
    for(int i=0;i<NUMERO_MAXIMO_VALORES; i++){
        Armazena_X[i] = NULL;
        Armazena_Y[i] = NULL;
    }
}

void Serie::setNome(string Nome)
{
    this->NomeDaSerie = Nome;
}

void Serie::setNomeDoCanalX(string nomeDoCanalX)
{
    this->NomeDoCanalX = nomeDoCanalX;
}

void Serie::setNomeDoCanalY(string nomeDoCanalY)
{
    this->NomeDoCanalY = nomeDoCanalY;
}

string Serie::getNome()
{
    return NomeDaSerie;
}

string Serie::getNomeDoCanalX()
{
    return NomeDoCanalX;
}

string Serie::getNomeDoCanalY()
{
    return NomeDoCanalY;
}

bool Serie::estaVazia()
{

    if (getQuantidade() != 0)

        return false;

    else

        return true;
}

int Serie::getQuantidade()
{

    int ContadorDePontos = 0;

    for(int i= 0; i<NUMERO_MAXIMO_VALORES; i++)
    {

        if(Armazena_X[i] != NULL && Armazena_Y[i] != NULL)

            ContadorDePontos++;
    }

    return ContadorDePontos;

}

void Serie::adicionar(double x, double y)
{
    if(getQuantidade() != NUMERO_MAXIMO_VALORES)
    {

        for(int i = 0; i<NUMERO_MAXIMO_VALORES; i++)
        {

            if((Armazena_X[i] == NULL) && (Armazena_Y[i] == NULL))
            {

                Armazena_X[i] = x;

                Armazena_Y[i] = y;

                break;
            }
        }
    }
}

Ponto* Serie::getLimiteSuperior(){

    double Maximo_X = Armazena_X[0];
    double Maximo_Y = Armazena_Y[0];

    for(int i=0; i<NUMERO_MAXIMO_VALORES; i++){

        if(Armazena_X[i] > Maximo_X)
            Maximo_X = Armazena_X[i];
        if(Armazena_Y[i] > Maximo_Y)
            Maximo_Y = Armazena_Y[i];
    }

    p->setX(Maximo_X);
    p->setY(Maximo_Y);

    return p;
}

Ponto* Serie::getLimiteInferior(){

    double Minimo_X = Armazena_X[0];

    double Minimo_Y = Armazena_Y[0];

    for(int i=0; i<NUMERO_MAXIMO_VALORES ; i++){

        if(Armazena_X[i] < Minimo_X && Armazena_X[i] != NULL)

            Minimo_X = Armazena_X[i];

        if(Armazena_Y[i] < Minimo_Y && Armazena_Y[i] != NULL)

            Minimo_Y = Armazena_Y[i];
    }

    p->setX(Minimo_X);
    p->setY(Minimo_Y);

    return p;
}

Ponto* Serie::getPosicao(int posicao){

    if(posicao >= NUMERO_MAXIMO_VALORES)
        return NULL;
    else{

        for(int i = 0; i<NUMERO_MAXIMO_VALORES; i++){

            if(i == posicao){
            p->setX(Armazena_X[i]);
            p->setY(Armazena_Y[i]);
            }
        }
    }

return p;
}

void Serie::imprimir(){

    cout<< "Serie " << NomeDaSerie <<endl;

    for(int i = 0; i<NUMERO_MAXIMO_VALORES && (Armazena_X[i] != NULL && Armazena_Y != NULL) ; i++)

    cout<< "(" << Armazena_X[i] << ", " << Armazena_Y[i] << ")" <<endl;

}
