#include <iostream>
#include "InterfaceSerial.h"
#include "Ponto.h"
#include "EixoEstatico.h"
#include "EixoDinamico.h"
#include "SerieNormal.h"
#include "SerieTemporal.h"
#include "Tela.h"
#include "Grafico.h"
#include "PersistenciaDeSerie.h"
#include <stdexcept>
#define COMM "\\\\.\\COM3"


using namespace std;

int main() {
    InterfaceSerial* is = new InterfaceSerial(COMM);
    Eixo *eixoY;
    Eixo *eixoX;
    string arquivo;
    string nomeserie;
    string tipoEixoX;
    string tipoEixoY;
    string tituloX;
    string tituloY;
    string canalx;
    string canaly;
    char serieloop = 's';
    double valorMinimoX;
    double valorMaximoX;
    double valorMinimoY;
    double valorMaximoY;
    PersistenciaDeSerie *persistencia;
    vector<Serie*>* series = new vector<Serie*>();
    vector<Serie*>* guardaSeries = new vector<Serie*>();
    try{
    is->inicializar();
    }
    catch (runtime_error *e){
        cout << "Erro: " << e->what() << endl;
        delete e;
        return 0;
    }
// Obtem o nome da Serie e os canais escolhidos
    cout << "informe o nome do arquivo de dados: ";
    cin >> arquivo;
    while (serieloop == 's'){
        cout << "informe o nome da serie: ";
        cin >> nomeserie;
        string* canais;
        canais = is->getNomeDosCanais();
        int canX = 0;
        cout << "escolha o canal X:" << endl;
        cout << 0 << ") Tempo" << endl;
        for (int i = 0; i < is->getQuantidadeDeCanais(); i++)
            cout << i + 1 << ") " << canais[i] << endl;
        cin >> canX;
        int canY = 0;
        cout << "escolha o canal Y:" << endl;
        for (int i = 0; i < is->getQuantidadeDeCanais(); i++)
        cout << i + 1 << ") " << canais[i] << endl;
        cin >> canY;
        cout << "adicionar uma nova serie (s/n): ";
        cin >> serieloop;
        if (canX == 0){
            SerieTemporal *st = new SerieTemporal(nomeserie, is->getNomeDosCanais()[canY]);
            series->push_back(st);
        }
        else {
            Serie *sn = new SerieNormal(nomeserie, is->getNomeDosCanais()[canX], is->getNomeDosCanais()[canY]);
            series->push_back(sn);
        }
    }
    // Obtem o numero de Pontos a adicionar
    int quantidade;
    cout << "obter quantos pontos? ";
    cin >> quantidade;

    // Cria a Serie
    cout << "Obtendo os pontos" << endl;
    while (series->size() > 0){
        Serie *serie = series->back();
        series->pop_back();
        guardaSeries->push_back(serie);
    }
    while (guardaSeries->size() > 0){
            Serie *serie = guardaSeries->back();
            guardaSeries->pop_back();
            for (int i = 0; i < quantidade; i++) {
                is->atualizar();
                    if (SerieTemporal *st = dynamic_cast<SerieTemporal*>(serie)) {
                    st->adicionar(is->getValor(st->getNomeDoCanalY()));
                    }
                    else if (SerieNormal *sn = dynamic_cast<SerieNormal*>(serie)){
                            string nome = sn->getNomeDoCanalY();
                            sn->adicionar(is->getValor(sn->getNomeDoCanalX()), is->getValor(nome));
                    }
        // adiciona os valores a Serie
            }
            series->push_back(serie);
    }
    char carregaserie;

    cout << "Deseja carregar alguma serie? (s/n) ";
    cin >> carregaserie;
    try{
    persistencia = new PersistenciaDeSerie(arquivo);
    }
     catch (ErroDeArquivo *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
    vector<string>* nomesArquivo = persistencia->getNomes();
    while (carregaserie == 's' && nomesArquivo->size() > 0){
            for (int i = 0; i < nomesArquivo->size(); i ++){
                    string nomeDaSerie = nomesArquivo->at(i);
                cout << i + 1 << ") " << nomeDaSerie << endl;
            }
            cout << "Escolha a serie para carregar: ";
            int serieEscolhida;
            cin >> serieEscolhida;
            nomeserie = nomesArquivo->at(serieEscolhida - 1);
            series->push_back(persistencia->obter(nomeserie));
            cout << "Deseja obter outra serie? (s/n) ";
            cin >> carregaserie;
        }
    cout << "o eixo X e' estatico ou dinamico (e/d): ";
    cin >> tipoEixoX;
    if (tipoEixoX == "e"){
        cout << "Informe o titulo: ";
        cin >> tituloX;
        cout <<"Valor minimo: ";
        cin >> valorMinimoX;
        cout <<"Valor maximo: ";
        cin >> valorMaximoX;
        try {
        eixoX = new EixoEstatico(tituloX,valorMinimoX, valorMaximoX, true);
        }
        catch (runtime_error *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
    }
    if (tipoEixoX == "d"){
        cout << "Informe o titulo: ";
        cin >> tituloX;
        cout <<"Valor minimo padrao: ";
        cin >> valorMinimoX;
        cout <<"Valor maximo padrao: ";
        cin >> valorMaximoX;
        list<Serie*>* listaSerie = new list<Serie*>();
        for (int i = 0; i < series->size(); i ++){
            listaSerie->push_back(series->at(i));
        }
        try{
        eixoX = new EixoDinamico(tituloX, valorMinimoX, valorMaximoX, listaSerie, true);
        }
        catch (runtime_error *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
    }
    cout << "O eixo Y e' estatico ou dinamico (e/d): ";
    cin >> tipoEixoY;
    if (tipoEixoY == "e"){
        cout << "Informe o titulo: ";
        cin >> tituloY;
        cout <<"Valor minimo: ";
        cin >> valorMinimoY;
        cout <<"Valor maximo: ";
        cin >> valorMaximoY;
        try {
        eixoY = new EixoEstatico(tituloY, valorMinimoY, valorMaximoY, false);
        }
        catch (runtime_error *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
    }
    if (tipoEixoY == "d"){
        cout << "Informe o titulo: ";
        cin >> tituloY;
        cout <<"Valor minimo padrao: ";
        cin >> valorMinimoY;
        cout <<"Valor maximo padrao: ";
        cin >> valorMaximoY;
        list<Serie*>* listaSerie = new list<Serie*>();
        for (int i = 0; i < series->size(); i ++){
            listaSerie->push_back(series->at(i));
        }
        try{
        eixoY = new EixoDinamico(tituloY ,valorMinimoY, valorMaximoY, listaSerie, false);
        }
        catch (runtime_error *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
    }
    Grafico *g;
    try{
    g = new Grafico(eixoX, eixoY, series);
    }
    catch (logic_error *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }

    try {
    g->desenhar();
    }
    catch (out_of_range *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
    cout << "Deseja salvar alguma serie? (s/n) ";
    cin >> carregaserie;
    while (carregaserie == 's'){
            for (int i = 0; i < series->size(); i++){
                Serie *serie = series->at(i);
                string serieCarregada = serie->getNome();
                cout << i + 1 << ") " << serie->getNome() << endl;
            }
            cout << "Escolha a serie para salvar: ";
            int serieEscolhida;
            cin >> serieEscolhida;
            cout <<"Salvar a serie com qual nome: ";
            string nomeSalva;
            cin >> nomeSalva;
            Serie *serie = series->at(serieEscolhida - 1);
            try {
            persistencia->inserir(nomeSalva, serie);
            }
            catch (out_of_range *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
             catch (ErroDeArquivo *e){
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
            }
            cout <<"Deseja salvar outra serie? (s/n) ";
            cin >> carregaserie;
    }
    return 0;
}
