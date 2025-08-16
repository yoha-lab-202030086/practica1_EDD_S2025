#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>

using namespace std;

class Jugador{
private:
    string nombre;
    char inicial;
    int puntaje;
    //PilaPoderes* poderes;

public:
    //Constructor y destructor
    Jugador();
    ~Jugador();

    void iniciarJugador(string nombre, char inicial);

    string getNombre()const;

    char getInicial()const;

    int getPuntaje() const;

    void incrementarPuntaje();
};


#endif