#ifndef SERIE_H
#define SERIE_H

#define NUMERO_MAXIMO_VALORES 10

#include <string>
#include "Ponto.h"

using namespace std;

class Serie {
public:

    Serie();

  string NomeDaSerie;

  string NomeDoCanalX;

  string NomeDoCanalY;

  double Armazena_X[NUMERO_MAXIMO_VALORES];

  double Armazena_Y[NUMERO_MAXIMO_VALORES];

  double X;

  double Y;

  Ponto *p = new Ponto;

  // Permite definir o nome, o nomeDoCanalX e o nomeDoCanalY.
  void setNome(string nome);/**OK**/
  void setNomeDoCanalX(string nomeDoCanalX);/**OK**/
  void setNomeDoCanalY(string nomeDoCanalY);/**OK**/

  // Permite obter o nome, o nomeDoCanalX e o nomeDoCanalY.

  string getNome();/**OK**/
  string getNomeDoCanalX();/**OK**/
  string getNomeDoCanalY();/**OK**/

  int getQuantidade(); /**OK**/

  bool estaVazia();/**OK**/

  void adicionar(double x, double y);/**OK**/

  Ponto* getLimiteSuperior();/**OK**/

  Ponto* getLimiteInferior();/**OK**/

  Ponto* getPosicao(int posicao);

  void imprimir();

  // ADICIONE OS ATRIBUTOS NECESSARIOS
};


#endif // SERIE_H
