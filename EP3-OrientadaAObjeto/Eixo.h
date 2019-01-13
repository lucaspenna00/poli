#ifndef EIXO_H
#define EIXO_H
#include <iostream>
#include <string>

using namespace std;

class Eixo
{
    public:
        Eixo(string titulo, double minimo, double maximo, bool orientacaoHorizontal);
        virtual ~Eixo();
        virtual string getTitulo ();
        virtual double getMinimo ()= 0;
        virtual double getMaximo () = 0;
        virtual bool temOrientacaoHorizontal();

    protected:
        double minimo;
        double maximo;
        string titulo;
        bool orientacaoHorizontal;
};

#endif // EIXO_H
