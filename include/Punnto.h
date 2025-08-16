#ifndef PUNTO_H
#define PUNTO_H

class Punto{

public:
int x,y;

    Punto* arriba;
    Punto* abajo;
    Punto* izquierda;
    Punto* derecha;

    bool lineaHaciaDerecha;
    bool lineaHaciaIzquierda;

    Punto(int x, int y){
        this->x=x;
        this->y=y;

        //al inicio no hay ninguna conexion
        this->arriba=nullptr;
        this->abajo=nullptr;
        this->derecha=nullptr;
        this->izquierda=nullptr;

        this->lineaHaciaDerecha=false;
        this->lineaHaciaIzquierda=false;


    }
 
 
};



#endif