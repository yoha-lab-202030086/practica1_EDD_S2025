#ifndef COLA_TURNOS_H
#define COLA_TURNOS_H

#include "Jugador.h" //Llamamos el archivo que tiene la declaracion de jugador ya que esta declaracion de cola turnos debe incluir a los jugadores

//Esta clase se usara como nodo para la cola
class NodoCola{
    public:
        Jugador* jugador;
        NodoCola* siguiente;

        NodoCola(Jugador* j);
};


class ColaTurnos{
    private:
        NodoCola* frente; //puntero al inciio
        NodoCola* final;  //puntero al final 

    public:
        ColaTurnos();
        ~ColaTurnos();

        //AAgregar a un jugador a la cola
        void encolar(Jugador* j);

        //Quita a un jugador de la cola
        Jugador* desencolar();

        //Ver al primer elemento de la cola
        Jugador* verFrente()const;

        // Verifica si la cola no tiene elementos
        bool estaVacia() const;

          // Método extra para visualizar el estado de la cola
        void imprimirCola() const;

};


#endif