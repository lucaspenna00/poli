#ifndef PERSISTENCIADESERIE_H
#define PERSISTENCIADESERIE_H
#include <fstream>
#include <vector>
#include "Serie.h"
#include "SerieNormal.h"
#include "SerieTemporal.h"
#include "ErroDeArquivo.h"

using namespace std;

class PersistenciaDeSerie
{
    public:

        PersistenciaDeSerie(string arquivo);

        virtual ~PersistenciaDeSerie();

        Serie* obter (string nome);

        vector<string>* getNomes();

        void inserir(string nome, Serie* s);

    protected:

        string arquivo;
        vector<Serie*>* series;

};

#endif // PERSISTENCIADESERIE_H
