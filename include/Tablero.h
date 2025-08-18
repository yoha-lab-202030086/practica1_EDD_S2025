#ifndef TABLERO_H
#define TABLERO_H

#include "Jugador.h"
#include "TipoPoder.h"

struct Caja
{
    Jugador* propietario=nullptr;
    TipoPoder poderDisponible=TipoPoder::NINGUNO;
};

class NodoPunto{
    public:
        NodoPunto*arriba=nullptr, *abajo=nullptr, *izquierda=nullptr, *derecha=nullptr;
     // Banderas para saber si una línea ha sido dibujada
        bool lineaHaciaDerecha=false;
        bool lineaHaciaAbajo=false;

        //CUando se use un poder 
        TipoPoder efectoLineaDerecha = TipoPoder::NINGUNO;
        TipoPoder efectoLineaAbajo = TipoPoder::NINGUNO;
};

class Tablero{

    private:
        int ancho, alto;
        NodoPunto* esquinaSuperiorIzquierda;
        Caja** matrizCajas;

        NodoPunto*getNodo(int r, int c)const;

    public:
        Tablero(int ancho, int alto);
        ~Tablero();

        // dibujarLinea ahora necesita saber qué poder se está usando 
        bool dibujarLinea(int r1, int c1, int r2, int c2, Jugador*jugador, TipoPoder poderAplicado=TipoPoder::NINGUNO);

        // Esta función ahora se encargará de todo el proceso de cierre y asignación
        int verificarYAsignarCaja(int r_linea, int c_linea, bool esHorizontal, Jugador*jugadorActua);

        void imprimirTablero(bool modoClarividente=false)const;
};



#endif