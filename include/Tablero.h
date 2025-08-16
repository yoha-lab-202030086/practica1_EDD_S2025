#ifndef TABLERO_H
#define TABLERO_H

#include "Punnto.h"

class Tablero
{
private:
   Punto* esquinaSuperiorIzquierda; //el primer puntero o punto para construir toda la malla
   int anch;
   int alto;

public:

    Tablero(int alto, int ancho);
    ~Tablero();

    void imprimirTablero()const;
};



#endif