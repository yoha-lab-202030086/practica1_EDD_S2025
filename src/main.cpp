#include <iostream>
#include <limits>
#include <string> // string y getline
using namespace std;
#include "../include/Jugador.h"
#include "../include/TipoPoder.h"

#include "../include/ColaTurnos.h"
#include "../include/Tablero.h"

void jugar(Jugador *jugadores, int nJugadores, int ancho, int alto);
void probarEstructurasJuego(Jugador *jugadores, int numJugadores, int ancho, int alto)
{
    std::cout << "\n\n--- INICIANDO PRUEBAS DE ESTRUCTURAS DE JUEGO ---" << std::endl;
    std::cout << "\n[PRUEBA] Creando y llenando la Cola de Turnos..." << std::endl;
    ColaTurnos colaDeTurnos;
    for (int i = 0; i < numJugadores; i++)
    {
        colaDeTurnos.encolar(&jugadores[i]);
    }
    std::cout << "Estado inicial de la cola:" << std::endl;
    colaDeTurnos.imprimirCola();
    std::cout << "\n[PRUEBA] Simulando una rotacion de turno..." << std::endl;
    Jugador *jugadorActual = colaDeTurnos.verFrente();
    std::cout << "Le toca a: " << jugadorActual->getNombre() << std::endl;
    Jugador *jugadorQueTermino = colaDeTurnos.desencolar();
    colaDeTurnos.encolar(jugadorQueTermino);
    std::cout << "Estado de la cola despues de una rotacion:" << std::endl;
    colaDeTurnos.imprimirCola();
    jugadorActual = colaDeTurnos.verFrente();
    std::cout << "Ahora le toca a: " << jugadorActual->getNombre() << std::endl;
    std::cout << ">> ¡Prueba de Cola de Turnos exitosa!" << std::endl;
    std::cout << "\n[PRUEBA] Creando el Tablero de Juego..." << std::endl;
    Tablero *tableroDeJuego = new Tablero(ancho, alto);
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

void mostrarBienvenida()
{
    cout << "=====================================" << std::endl;
    cout << "=== BIENVENIDO A TIMBIRICHE / TOTITO CHINO POR YOHANA ===" << std::endl;
    cout << "=====================================" << std::endl
         << std::endl;
}

int main()
{
    mostrarBienvenida();
    int ancho, alto, numJugadores;
    do
    {
        cout << "Introduce el ancho del tablero (min 3): ";
        cin >> ancho;
    } while (ancho < 3);

    do
    {
        cout << "Ingrece el alto del tablero (min 3): ";
        cin >> alto;
    } while (alto < 3);

    do
    {
        cout << "Ingrece el numero de jugadores (min 2): ";
        cin >> numJugadores;
    } while (numJugadores < 2);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Arreglo de jugadores
    Jugador *listaJugadores = new Jugador[numJugadores];

    for (int i = 0; i < numJugadores; i++)
    {
        string nombre;
        char inicial;
        cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
        getline(cin, nombre);
        cout << "Ingrese su inicial: ";
        cin >> inicial;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        listaJugadores[i].iniciarJugador(nombre, inicial);
    }

    cout << "\nQUE COMIENCE EL JUEGO!!!!!!!!! " << endl;

    jugar(listaJugadores, numJugadores, alto, ancho);

    // probarEstructurasJuego(listaJugadores, numJugadores, ancho, alto);

    // Liberamos la memoria del arreglo de jugadores al final
    delete[] listaJugadores;

    return 0;
}

void jugar(Jugador *jugadores, int nJugadores, int ancho, int alto)
{
    int fin = 5, accion;
    int x1, y1, x2, y2;
    ColaTurnos turnos;

    for (int i = 0; i < nJugadores; i++)
    {
        turnos.encolar(&jugadores[i]);
    }
    Tablero *tablero = new Tablero(alto, ancho);
    while (fin > 0)
    {

        Jugador *turnoActual = turnos.verFrente();
        cout << "\tTurno de: [" << turnoActual->getNombre() << "] Inicial: [" << turnoActual->getInicial() << "] ";
        turnoActual->verPoderes();
       cout<<"\n";
        tablero->imprimirTablero(false);

        cout << "\n1---Dibujar Linea" << endl;
        cout << "2---Usar Poder" << endl;
        cout << "3---Activar/Desactivar Clarividente" << endl;
        cout << "Elija la accion a realizar: ";
        cin >> accion;
        if (accion == 1)
        {
            cout<<"\n\t\tFILAS Y COLUMNAS INCIAN EN CERO 0 \n"<<endl;
            cout << "\tIngresando las coordenadas primer punto:   (FILA, COLUMNA)\n" << endl;
            
            cout << "Ingrese el numero de fila ";
            cin >> x1;
            cout << "Ingrese el numero de columna ";
            cin >> y1;
            cout << "\tIngresando las coordenadas Segundo punto: (FILA, COLUMNA)\n" << endl;
            cout << "Ingrese el numero de la fila ";
            cin >> x2;
            cout << "Ingrese el numero de columna ";
            cin >> y2;
            tablero->dibujarLinea(x1,y1,x2,y2, turnoActual, TipoPoder::NINGUNO);
            

        }
        Jugador*jugadorRecienTermino= turnos.desencolar();
        turnos.encolar(jugadorRecienTermino);
        fin--;
    }
}