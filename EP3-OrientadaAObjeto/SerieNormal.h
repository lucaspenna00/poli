#ifndef SERIENORMAL_H
#define SERIENORMAL_H
#include "Serie.h"

class SerieNormal : public Serie
{
    public:
        SerieNormal(string nome, string nomeDoCanalX, string nomeDoCanalY);
        virtual ~SerieNormal();
        virtual void adicionar(double x, double y);

    protected:

    private:
};

#endif // SERIENORMAL_H
