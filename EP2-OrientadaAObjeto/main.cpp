#include <iostream>

#include "Serie.h"
#include "Ponto.h"
#include <iostream>

#include "Serie.h"
#include "Ponto.h"
#include "InterfaceSerial.h"

#define COMM "\\\\.\\COM3"

using namespace std;

int main()
{
    InterfaceSerial* is = new InterfaceSerial();
    Serie* s1 = new Serie;
    string nomeserie;

    is->inicializar(COMM);
    string canalx;
    string canaly;
    cout << "aperte o botao reset da placa" << endl;

// Obtem o nome da Serie e os canais escolhidos
    cout << "informe o nome da serie: " << endl;
    cin >> nomeserie;
    cout << endl;
    string* canais;
    canais = is->getNomeDosCanais();

    int canX = 0;
    cout << "escolha o canal X:" << endl;
    for (int i = 0; i < is->getQuantidadeDeCanais(); i++)
        cout << i << ") " << canais[i] << endl;
    cin >> canX;
    int canY = 0;
    cout << "escolha o canal Y:" << endl;
    for (int i = 0; i < is->getQuantidadeDeCanais(); i++)
        cout << i << ") " << canais[i] << endl;
    cin >> canY;
    cout << endl;

    // Obtem o numero de Pontos a adicionar
    int quantidade;
    cout << "obter quantos pontos? ";
    cin >> quantidade;
    cout << endl;

    // Cria a Serie
    cout << "Obtendo os pontos" << endl;
    for (int i = 0; i < quantidade; i++)
    {
        is->atualizar();
        s1->adicionar(is->getValor(is->getNomeDosCanais()[canX]), is->getValor(is->getNomeDosCanais()[canY]));
        // adiciona os valores a Serie
    }

    cout << "Imprimindo os pontos obtidos" << endl;

    s1->imprimir();

    cout << "Limite Superior: ";
    s1->getLimiteSuperior()->imprimir();
    cout << endl;

    cout << "Limite Inferior: ";
    s1->getLimiteInferior()->imprimir();
    cout << endl;

    return 0;
}
