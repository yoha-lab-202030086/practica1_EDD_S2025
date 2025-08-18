#include <iostream>
#include <limits>
#include <string> // Necesario para 'string' y 'getline'
using namespace std; // Para no tener que escribir std::

// Las cabeceras de tus clases
#include "../include/Jugador.h"
#include "../include/TipoPoder.h"

// ============================================================
// PEGA LA FUNCIÓN 'probarEstructurasJuego' COMPLETA AQUÍ
// (El bloque de código del Paso 1)
// ============================================================
#include "../include/ColaTurnos.h"
#include "../include/Tablero.h"

void probarEstructurasJuego(Jugador* jugadores, int numJugadores, int ancho, int alto) {
    std::cout << "\n\n--- INICIANDO PRUEBAS DE ESTRUCTURAS DE JUEGO ---" << std::endl;
    std::cout << "\n[PRUEBA] Creando y llenando la Cola de Turnos..." << std::endl;
    ColaTurnos colaDeTurnos;
    for (int i = 0; i < numJugadores; i++) {
        colaDeTurnos.encolar(&jugadores[i]);
    }
    std::cout << "Estado inicial de la cola:" << std::endl;
    colaDeTurnos.imprimirCola();
    std::cout << "\n[PRUEBA] Simulando una rotacion de turno..." << std::endl;
    Jugador* jugadorActual = colaDeTurnos.verFrente();
    std::cout << "Le toca a: " << jugadorActual->getNombre() << std::endl;
    Jugador* jugadorQueTermino = colaDeTurnos.desencolar();
    colaDeTurnos.encolar(jugadorQueTermino);
    std::cout << "Estado de la cola despues de una rotacion:" << std::endl;
    colaDeTurnos.imprimirCola();
    jugadorActual = colaDeTurnos.verFrente();
    std::cout << "Ahora le toca a: " << jugadorActual->getNombre() << std::endl;
    std::cout << ">> ¡Prueba de Cola de Turnos exitosa!" << std::endl;
    std::cout << "\n[PRUEBA] Creando el Tablero de Juego..." << std::endl;
    Tablero* tableroDeJuego = new Tablero(ancho, alto);
    std::cout << "Tablero inicial de " << ancho << "x" << alto << ":" << std::endl;
    tableroDeJuego->imprimirTablero();
    std::cout << "\n[PRUEBA] Dibujando una linea de (0,0) a (0,1)..." << std::endl;
    tableroDeJuego->dibujarLinea(0, 0, 0, 1, jugadorActual, TipoPoder::NINGUNO);
    std::cout << "Tablero despues de dibujar la linea:" << std::endl;
    tableroDeJuego->imprimirTablero();
    std::cout << ">> ¡Prueba del Tablero exitosa!" << std::endl;
    delete tableroDeJuego;
    std::cout << "\n--- FIN DE LAS PRUEBAS ---" << std::endl;
}



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
    } while (ancho < 3);

    do{
        cout << "Ingrece el alto del tablero (min 3): ";
        cin >> alto;
    } while(alto < 3);

    do{
        cout << "Ingrece el numero de jugadores (min 2): ";
        cin >> numJugadores;
    } while(numJugadores < 2);

     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

     Jugador* listaJugadores = new Jugador[numJugadores];

     for (int i = 0; i < numJugadores; i++){
        string nombre;
        char inicial;
        cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
        getline(cin, nombre);
        cout << "Ingrese su inicial: ";
        cin >> inicial;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Nota: Asegúrate que tus métodos se llamen así.
        // En mis ejemplos eran 'inicializar' y 'agregarPoder'.
        listaJugadores[i].iniciarJugador(nombre, inicial);
        listaJugadores[i].agregarPoder(TipoPoder::DOBLE_LINEA);
     }

     cout << "\nRESUMEN" << endl;
     cout << "Ancho del tablero: " << ancho << endl;
     cout << "Alto del tablero: " << alto << endl;
     cout << "Jugadores" << endl;
     
     for (int i = 0; i < numJugadores; i++){
        cout << "Jugador: " << listaJugadores[i].getNombre() << " Inicial: " << listaJugadores[i].getInicial() << endl;
        listaJugadores[i].verPoderes();
     }

     cout << "\nQUE COMIENCE EL JUEGO!!!!!!!!! " << endl;
     
     // ===================================
     // LLAMADA A LA FUNCIÓN DE PRUEBA
     // ===================================
     probarEstructurasJuego(listaJugadores, numJugadores, ancho, alto);


     // Liberamos la memoria del arreglo de jugadores al final
     delete[] listaJugadores;

     return 0;
}