#include "Jugador.h"
#include <iostream>

Jugador::Jugador(){
    this->nombre="N/A";
    this->inicial='?';
    this->puntaje=0;
    this->poderes=new PilaPoderes();
}

Jugador::~Jugador(){

    delete this->poderes;
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


void Jugador::agregarPoder(TipoPoder p){
    cout<< this->nombre << " ha obtenido el poder: " << poderAString(p) << std::endl;

    this->poderes->agregar(p);

}
TipoPoder Jugador::usarPoder(){
    if(this->poderes->estaVacia()){
        cerr<<" Error: "<<this->nombre<<" No tiene poderes "<<endl;

    }
    TipoPoder poderUsado=this->poderes->quitar();
    cout<<this->nombre<<" Ha usado el poder: "<< poderAString(poderUsado)<<endl;

    return poderUsado;
}

void Jugador::verPoderes()const{
    this->poderes->imprimirPila();
}


bool Jugador::tienePoderes()const{
    
    return this->poderes->estaVacia();
    
}
