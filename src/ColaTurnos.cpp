#include "ColaTurnos.h"
#include <iostream>


NodoCola::NodoCola(Jugador*j){
    this->jugador=j;
    this->siguiente=nullptr;
}


ColaTurnos::ColaTurnos(){
    this->frente=nullptr;
    this->final=nullptr;
}

ColaTurnos::~ColaTurnos(){
    cout << "Destructor de ColaTurnos llamado. Vaciando la cola..." <<endl;
    while (!estaVacia()){
        desencolar();
    }
    
}

void ColaTurnos::encolar(Jugador* j){
    NodoCola* nuevoNodo=new NodoCola(j);
    if(estaVacia()){
        this->frente=nuevoNodo;
        this->final=nuevoNodo;
    }else{
        this->final->siguiente=nuevoNodo;

        this->final=nuevoNodo;
    }

}

Jugador* ColaTurnos::desencolar(){
    if(estaVacia()){
        cout<<"Esta desencolando una cola vacia XD"<<endl;
        return nullptr;
    }

    //Guardamos el nodo de frente para liberarlo
    NodoCola* nodoAEliminar=this->frente;

    Jugador* jugadorARetornar=nodoAEliminar->jugador;
    //Mover el puntero del frente al siguiente elemento

    this->frente=this->frente->siguiente;

    //Si al quitar el elemento la cola queda vacia, tambien actualizaos el puntero final
    if(this->frente==nullptr){
        this->final=nullptr;
    }

    //Liberamos la memoria del nodo pero no del jugador al que apunta
    //El jugador sigue existiendo en el nodo principal

    delete nodoAEliminar;
    return jugadorARetornar;
}

Jugador* ColaTurnos::verFrente() const {
    if (estaVacia()) {
        return nullptr;
    }
    return this->frente->jugador;
}

bool ColaTurnos::estaVacia() const {
    return this->frente == nullptr;
}

void ColaTurnos::imprimirCola() const {
    cout << "Estado de la Cola: Frente -> ";
    if (estaVacia()) {
        cout << "(vacia)" << endl;
        return;
    }

    NodoCola* actual = this->frente;
    while(actual != nullptr) {
       cout << "[" << actual->jugador->getNombre() << "] -> ";
        actual = actual->siguiente;
    }
    cout << "Final" <<endl;
}

