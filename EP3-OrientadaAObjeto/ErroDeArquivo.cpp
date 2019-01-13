#include "ErroDeArquivo.h"

ErroDeArquivo::ErroDeArquivo(const string &mensagem) : logic_error(mensagem)
{

}

ErroDeArquivo::~ErroDeArquivo()
{
    //dtor
}
