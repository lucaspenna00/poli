#ifndef SERIE_H
#define SERIE_H

#include <string>
#include "Ponto.h"
#include "vector"
#include "stdexcept"

using namespace std;

class Serie
{

     ///////////////////////MUDAR PARA PROTECTED!!!////////////////
    protected:
    string nome;

    string nomeDoCanalX;

    string nomeDoCanalY;

    vector<Ponto*>* pontos;
    public:

    Serie(string nome, string nomeDoCanalX, string nomeDoCanalY);

    virtual ~Serie() = 0;

    virtual string getNome();/**OK**/
    virtual string getNomeDoCanalX();/**OK**/
    virtual string getNomeDoCanalY();/**OK**/

    virtual int getQuantidade(); /**OK**/

    virtual bool estaVazia();/**OK**/

    virtual vector<Ponto*>* getPontos();

    virtual Ponto* getLimiteSuperior();/**OK**/

    virtual Ponto* getLimiteInferior();/**OK**/

    virtual Ponto* getPosicao(int posicao);

    virtual void imprimir();

};

#endif // SERIE_H
