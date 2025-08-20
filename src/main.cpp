#include <iostream>
#include <limits>
#include <string> // string y getline
using namespace std;
#include "../include/Jugador.h"
#include "../include/TipoPoder.h"

#include "../include/ColaTurnos.h"
#include "../include/Tablero.h"

void jugar(Jugador *jugadores, int nJugadores, int ancho, int alto);
bool verificarCaja(int f1, int col1, int f2, int col2, Jugador* jugador, Tablero* tablero);
void mostrarBienvenida(){
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
    // El nombre del parámetro en Tablero es (ancho, alto), pero tu creación es (alto, ancho).
    // Para evitar confusión, vamos a crearlo en el orden correcto.
    Tablero *tablero = new Tablero(ancho, alto);
    
    ColaTurnos turnos;
    for (int i = 0; i < nJugadores; i++) {
        turnos.encolar(&jugadores[i]);
    }

    int lineasDibujadas = 0;
    int maxLineas = (ancho - 1) * alto + ancho * (alto - 1);

    // Bucle principal del juego
    while (lineasDibujadas < maxLineas) {
        system("clear || cls"); // Limpia la consola
        bool turnoExtra = false; // Reiniciamos la bandera en cada turno
        
        Jugador *turnoActual = turnos.verFrente();
        cout << "\t\033[92mTurno de: [" << turnoActual->getNombre() << "] Inicial: [" << turnoActual->getInicial() << "] Puntos: [" << turnoActual->getPuntaje() << "] ";
        turnoActual->verPoderes();
        cout<<"\033[00m"<<endl;
        cout << "\n";
        tablero->imprimirTablero(false);

        cout << "\n1---Dibujar Linea" << endl;
        cout << "2---Usar Poder" << endl;
        cout << "3---Activar/Desactivar Clarividente" << endl;
        cout << "Elija la accion a realizar: ";
        
        int accion;
        cin >> accion;
        int f1_usuario, c1_usuario, f2_usuario, c2_usuario;
        if (accion == 1) {
            
            bool lineaDibujadaConExito;

            do {
                cout << "\n\t\tFILAS Y COLUMNAS INCIAN EN CERO 0 \n" << endl;
                cout << "\tIngresando las coordenadas primer punto:   (FILA, COLUMNA)\n" << endl;
                cout << "Ingrese el numero de fila "; cin >> f1_usuario;
                cout << "Ingrese el numero de columna "; cin >> c1_usuario;
                cout << "\tIngresando las coordenadas Segundo punto: (FILA, COLUMNA)\n" << endl;
                cout << "Ingrese el numero de la fila "; cin >> f2_usuario;
                cout << "Ingrese el numero de columna "; cin >> c2_usuario;

                int r1 = f1_usuario; 
                int c1 = c1_usuario;
                int r2 = f2_usuario;
                int c2 = c2_usuario;
                
                // Ahora llamamos a los métodos del tablero con las coordenadas INTERNAS (r, c)
                lineaDibujadaConExito = tablero->dibujarLinea(r1, c1, r2, c2, turnoActual, TipoPoder::NINGUNO);

            } while (!lineaDibujadaConExito);

            // Obtenemos las coordenadas internas de la línea recién dibujada para la verificación
            int r1_traducido = f1_usuario;
            int c1_traducido = c1_usuario;
            int r2_traducido = f2_usuario;
            int c2_traducido = c2_usuario;

            // Llamamos a la función auxiliar con las coordenadas ya traducidas
            turnoExtra = verificarCaja(r1_traducido, c1_traducido, r2_traducido, c2_traducido, turnoActual, tablero);
            lineasDibujadas++;

        } else if (accion == 2) {
             int valor = 2;
        turnoActual->verPoderes();
        TipoPoder poder = turnoActual->usarPoder();
        cout << "\nPoder a Usar: " << poderAString(poder) << "\n"
             << endl;
             cout << "Presiona Enter para continuar...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        if (poder == TipoPoder::DOBLE_LINEA)
        {
            while (valor > 0)
            {
                do{
                cout << "\n\t\tFILAS Y COLUMNAS INCIAN EN CERO 0 \n"<< endl;
                cout << "\tIngresando las coordenadas primer punto:   (FILA, COLUMNA)\n"<< endl;

                cout << "Ingrese el numero de fila ";
                cin >> f1_usuario;
                cout << "Ingrese el numero de columna ";
                cin >> c1_usuario;
                cout << "\tIngresando las coordenadas Segundo punto: (FILA, COLUMNA)\n"<< endl;
                cout << "Ingrese el numero de la fila ";
                cin >> f2_usuario;
                cout << "Ingrese el numero de columna ";
                cin >> c2_usuario;                   
            }while(!tablero->dibujarLinea(f1_usuario, c1_usuario, f2_usuario, c2_usuario, turnoActual, TipoPoder::NINGUNO));
                if(valor>1){
                        tablero->imprimirTablero();
                    }
                valor--;
            }
        }
        }

        // Esta lógica de rotación de turno es la correcta
        if (!turnoExtra) {
            Jugador *jugadorRecienTermino = turnos.desencolar();
            turnos.encolar(jugadorRecienTermino);
        }
    }

    // Limpieza final
    delete tablero;
}

bool verificarCaja(int fila1, int col1, int fila2, int col2, Jugador* jugador, Tablero* tablero){
    bool esHorizontal = (fila1 == fila2);
    int f_origen = min(fila1, fila2);
    int col_origen = min(col1, col2);

    int cajasCerradas = tablero->verificarYAsignarCaja(f_origen, col_origen, esHorizontal, jugador);

    if(cajasCerradas > 0){
        for (int i = 0; i < cajasCerradas; i++) {
            jugador->incrementarPuntaje();
        }
        cout << "\n\033[32m¡Punto y turno extra para " << jugador->getNombre() << "!\033[0m" << endl;
    
        cout << "Presiona Enter para continuar...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return true;
    } else {
        // No es necesario un mensaje aquí, ya que es el resultado normal.
        return false;
    }
}