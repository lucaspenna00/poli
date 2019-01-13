#ifndef SERIETEMPORAL_H
#define SERIETEMPORAL_H
#include "Serie.h"

class SerieTemporal: public Serie
{

    public:

        SerieTemporal(string nome, string nomeDoCanalY);

        virtual ~SerieTemporal(); //destrutor


        virtual void adicionar(double valor);

    protected:

        static int instante;
};

#endif
