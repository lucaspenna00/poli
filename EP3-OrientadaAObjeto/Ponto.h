#ifndef PONTO_H
#define PONTO_H

class Ponto {
private:
    double x=0.0;
   double y=0.0;
public:

    Ponto (double x, double y);

    virtual ~Ponto ();
  /**
   * Obtem o valor do Ponto na coordenada horizontal (x).
   */
  double getX();

  /**
   * Obtem o valor do Ponto na coordenada vertical (y).
   */
  double getY();

  /**
   * Define o valor do Ponto na coordenada horizontal (x).
   */

  /**
   * Define o valor do Ponto na coordenada vertical (y).
   */

  /**
   * Imprime na saida padrao (cout) o Ponto no formato (x, y).
   * Pule uma linha apos imprimir o Ponto.
   */
  void imprimir();

  /**
   * Informa se este Ponto eh igual a outro.
   * Um Ponto eh igual se os valores x e y dos Pontos sao
   * suficientemente proximos.
   */
  bool eIgual(Ponto* outro);

  // ADICIONE OS ATRIBUTOS NECESSARIOS
};

#endif // PONTO_H
