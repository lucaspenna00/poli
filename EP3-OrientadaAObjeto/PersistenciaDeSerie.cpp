#include "PersistenciaDeSerie.h"
#include <string>
#include <iostream>
using namespace std;

PersistenciaDeSerie::PersistenciaDeSerie(string arquivo){
    series = new vector<Serie*> ();
    this->arquivo = arquivo;
    ifstream input;
    input.open(arquivo);
    while (input.good()){
        string nome;
        int tipo;
        int quantidade;
        string nomeDoCanalX;
        string nomeDoCanalY;
        input >> nome;
        input >> tipo;
        input >> quantidade;
        if (tipo == 1){
            input >> nomeDoCanalX;
            input >> nomeDoCanalY;
            double valorX;
            double valorY;
            SerieNormal *s = new SerieNormal(nome, nomeDoCanalX, nomeDoCanalY);
            for (int i = 0; i < quantidade; i++){
                input >> valorX;
                input >> valorY;
                s->adicionar(valorX, valorY);
            }
            series->push_back(s);
            s->~SerieNormal();
        }
        else if (tipo == 0){
            input >> nomeDoCanalY;
            double valor;
            SerieTemporal *st = new SerieTemporal(nome, nomeDoCanalY);
            for (int i = 0; i < quantidade; i++){
                input >> valor;
                st->adicionar(valor);
            }
            series->push_back(st);
            st->~SerieTemporal();
        }
        if (!input && !input.eof()){
            throw new ErroDeArquivo("Formato invalido");
        }
    }
    input.close();
}

PersistenciaDeSerie::~PersistenciaDeSerie(){

}

Serie* PersistenciaDeSerie::obter(string nome){
    bool achou = false;
    Serie *serie;
    for (int i = 0; i < series->size() && achou == false; i++){
        serie = series->at(i);
        if (serie->getNome() == nome)
            achou = true;
    }
    if (achou)
        return serie;
    return NULL;




}

vector<string>* PersistenciaDeSerie::getNomes(){
    vector<string>* nomes = new vector<string>();
    for (int i = 0; i < series->size(); i ++){
        Serie *serie = series->at(i);
        nomes->push_back(serie->getNome());
    }
    return nomes;
}

void PersistenciaDeSerie::inserir(string nome, Serie* s){
    for (int i = 0; i < series->size(); i++){
        Serie *serieAtual = series->at(i);
        if (serieAtual->getNome() == s->getNome())
            throw new ErroDeArquivo("Ja existe uma serie com esse nome");
    }
    series->push_back(s);

    ofstream output;
    output.open(arquivo,ios_base::app);
    if (output.fail())
        throw new ErroDeArquivo("Falha ao escrever");
    if (s->getNomeDoCanalX() == "Tempo"){
        output << nome << "\n";
        output << 0 << "\n";
        output << s->getQuantidade() << "\n";
        output << s->getNomeDoCanalY() << "\n";
        for (int i = 0; i < s->getQuantidade(); i++){
            output << s->getPosicao(i)->getY() << "\n";
        }
    }
    else{
        output<< "\n" << nome << "\n";
        output << 1 << "\n";
        output << s->getQuantidade() << "\n";
        output << s->getNomeDoCanalX() << "\n";
        output << s->getNomeDoCanalY();
        for (int i = 0; i < s->getQuantidade(); i++){
            output<< "\n" << s->getPosicao(i)->getX() << "\n";
            output << s->getPosicao(i)->getY();
        }
    }
}
