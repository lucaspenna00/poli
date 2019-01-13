#ifndef VIGA_H
#define VIGA_H
/*

tramos internos: h = L/12

tramos externos ou viga biapoiadas: h = L/10

balanços: h = L/5

Usualmente, adotam-se, no máximo, duas alturas diferentes. Tal
procedimento pode, eventualmente, gerar a necessidade de armadura dupla em
alguns trechos das vigas.
*/

class Viga
{
    public:

        Viga(float Xo, float Yo, float Xf, float Yf, char tipo);
        virtual ~Viga();
        float obterEspessura();
        float obterComprimento();

    protected:

        float Xo;
        float Yo;
        float Yf;
        float Xf;
        char tipo; //balanço ou tramos internos ou tramos externos

    private:
};

#endif // VIGA_H
