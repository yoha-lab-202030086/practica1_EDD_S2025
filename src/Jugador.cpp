#include "Jugador.h"
#include "PilaPoderes.h"

Jugador::Jugador(){
    this->nombre="N/A";
    this->inicial='?';
    this->puntaje=0;

    //this->poderes=new PilaPoderes();
}

Jugador::~Jugador(){

}


void Jugador::iniciarJugador(string nombre, char inicial){
    this->nombre=nombre;
    this->inicial=inicial;
    this->puntaje=0;
}


string Jugador::getNombre()const{
    return this->nombre;
}


char Jugador::getInicial()const{
    return this->inicial;
}

int Jugador::getPuntaje()const {
    return this->puntaje;
}

void Jugador::incrementarPuntaje(){
    this->puntaje++;
}