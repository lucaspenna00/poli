#ifndef SERIE_H
#define SERIE_H

#define NUMERO_MAXIMO_VALORES 10

#include <string>
#include "Ponto.h"

using namespace std;

class Serie
{

public:

    string NomeDaSerie;

    string NomeDoCanalX;

    string NomeDoCanalY;

    double Armazena_X[NUMERO_MAXIMO_VALORES];

    double Armazena_Y[NUMERO_MAXIMO_VALORES];

    Ponto *p = new Ponto;

    Serie(string NomeDaSerie, string NomeDoCanalX, string NomeDoCanalY);

    virtual ~Serie();

    virtual string getNome();/**OK**/
    virtual string getNomeDoCanalX();/**OK**/
    virtual string getNomeDoCanalY();/**OK**/

    virtual int getQuantidade(); /**OK**/

    virtual bool estaVazia();/**OK**/

    virtual void adicionar(double x, double y);/**OK**/

    virtual Ponto* getLimiteSuperior();/**OK**/

    virtual Ponto* getLimiteInferior();/**OK**/

    virtual Ponto* getPosicao(int posicao);

    virtual void imprimir();

};

#endif // SERIE_H
