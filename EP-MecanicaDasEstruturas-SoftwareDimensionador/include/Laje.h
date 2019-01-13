#ifndef LAJE_H
#define LAJE_H


class Laje
{
    public:
        Laje(float x, float y, int identificacao );
        virtual ~Laje();
        float obterAltura();
        float x;
        float y;
        int identificacao;

    protected:
    private:
};

#endif // LAJE_H
