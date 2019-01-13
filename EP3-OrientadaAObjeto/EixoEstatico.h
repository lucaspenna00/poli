#ifndef EIXOESTATICO_H
#define EIXOESTATICO_H
#include "Eixo.h"

class EixoEstatico : public Eixo
{
    public:
        EixoEstatico(string titulo, double minimo, double maximo, bool orientacaoHorizontal);
        virtual ~EixoEstatico();
        double getMinimo();
        double getMaximo();
    protected:

    private:
};

#endif // EIXOESTATICO_H
