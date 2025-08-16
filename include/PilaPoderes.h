#ifndef PILA_PODERES_H
#define PILA_PODERES_H

#include "TipoPoder.h"

class NodoPila{
    public:
        TipoPoder poder;
        NodoPila* abajo;


        NodoPila(TipoPoder p);
};


class PilaPoderes{
    private:
        NodoPila* cima;

    public:
        PilaPoderes();
        ~PilaPoderes();


        void agregar(TipoPoder p);
        TipoPoder quitar();

        TipoPoder verCima() const;
        bool estaVacia() const;

        void imprimirPila()const;
};

#endif