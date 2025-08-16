#include <iostream>
#include <limits> //para limpiar el buffer de entrada
#include "../include/Jugador.h"

void mostrarBienvenida(){
    cout << "=====================================" << std::endl;
    cout << "=== BIENVENIDO A TIMBIRICHE / TOTITO CHINO ===" << std::endl;
    cout << "=====================================" << std::endl << std::endl;

}

int main (){
    mostrarBienvenida();
    int ancho, alto, numJugadores;
    do{
   
    cout << "Introduce el ancho del tablero (min 3): ";
    cin >> ancho;
    }while (ancho<3);

    do{
        cout<<"Ingrece el alto del tablero (min 3): ";
        cin>>alto;
    }while(alto<3);

    do{
        cout<<"Ingrece el numero de jugadores (min 2: ";
        cin>>numJugadores;
    }while(numJugadores<2);

     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

     Jugador* listaJugadores = new Jugador[numJugadores];


     for (int i = 0; i < numJugadores; i++){
        string nombre;
        char inicial;
        cout<<"Ingrese el nombre del jugador: "<<i+1<<": ";
        getline(cin,nombre);
        cout<<"Ingrese su inicial: ";
        cin>>inicial;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

        listaJugadores[i].iniciarJugador(nombre,inicial);

        
     }


     cout<<"RESUMEN"<<endl;

     cout<<"Ancho del tablero: "<<ancho<<endl;
     cout<<"Alto del tablero: "<<alto<<endl;

     cout<<"Jugadores"<<endl;
     
     for (int i = 0; i < numJugadores; i++){
        
        cout<<"Jugaor: "<<listaJugadores[i].getNombre()<<" Inicial: "<<listaJugadores[i].getInicial()<<endl;
     }


     cout<<"QUE COMIENCE EL JUEGO!!!!!!!!! "<<endl;
     
     return 0;
    
}