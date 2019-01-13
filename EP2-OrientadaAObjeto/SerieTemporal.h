#ifndef SERIETEMPORAL_H
#define SERIETEMPORAL_H
#include "Serie.h"

class SerieTemporal: public Serie
{

    public:

        SerieTemporal(string nome, string NomeDoCanalY);

        virtual ~SerieTemporal(); //destrutor

        virtual int existePontoIgual();

        virtual void adicionar(double valor);

        virtual void adicionar(double x, double y);

    protected:

        double instante;

};

#endif
