#include "PilaPoderes.h"

#include <iostream>
using namespace std;

NodoPila::NodoPila(TipoPoder p){
    this->poder=p;
    this->abajo=nullptr;
}

PilaPoderes::PilaPoderes(){
    this->cima=nullptr;    
}

PilaPoderes::~PilaPoderes(){
    std::cout << "[DEBUG] Destructor de PilaPoderes llamado. Limpiando pila..." << std::endl;
    while (!estaVacia()) {
        quitar(); // El método pop ya se encarga de eliminar un nodo en cada llamada
    }

}

void PilaPoderes::agregar(TipoPoder p){
    NodoPila* nuevoNodo=new NodoPila(p);
    nuevoNodo->abajo=this->cima;
    this->cima=nuevoNodo;

}

TipoPoder PilaPoderes::quitar(){

    if(estaVacia()){
       throw out_of_range("Error: Intentando hacer pop en una pila vacia.");
    }

    NodoPila* nodoEliminar=this->cima;
    TipoPoder poderRetornado=nodoEliminar->poder;
    this->cima=this->cima->abajo;

    delete nodoEliminar;
    return poderRetornado;
}

TipoPoder PilaPoderes::verCima()const{
    if(estaVacia()){
        throw out_of_range("Error: Intentando hacer pop en una pila vacia.");
    }

    return this->cima->poder;
}

bool PilaPoderes::estaVacia()const{
    return this->cima==nullptr;
}


void PilaPoderes::imprimirPila()const{
    if(estaVacia()){
        cout<<"[No hay poderes]"<<endl;
        return;
    }
    cout<<"Poderes: ";
    NodoPila* actual=this->cima;
    while (actual!=nullptr)
    {
        cout << "[" << poderAString(actual->poder) << "] -> ";
        actual=actual->abajo;
    }
    


}

