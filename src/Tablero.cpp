#include "../include/Tablero.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Para setw

Tablero::Tablero(int ancho, int alto) {
    this->ancho = ancho;
    this->alto = alto;
    // ... (la creación y enlazado de nodos es igual que antes) ...
    std::vector<std::vector<NodoPunto*>> nodos(alto, std::vector<NodoPunto*>(ancho));
    for (int i = 0; i < alto; ++i) { for (int j = 0; j < ancho; ++j) { nodos[i][j] = new NodoPunto(); }}
    this->esquinaSuperiorIzquierda = nodos[0][0];
    for (int i = 0; i < alto; ++i) { for (int j = 0; j < ancho; ++j) {
        if (i > 0) nodos[i][j]->arriba = nodos[i - 1][j]; if (i < alto - 1) nodos[i][j]->abajo = nodos[i + 1][j];
        if (j > 0) nodos[i][j]->izquierda = nodos[i][j - 1]; if (j < ancho - 1) nodos[i][j]->derecha = nodos[i][j + 1];
    }}

    // Creación de la matriz de Cajas y asignación de Power-Ups VISIBLES
  srand(time(0));
    int altoCajas = alto - 1;
    int anchoCajas = ancho - 1;
    this->matrizCajas = new Caja*[altoCajas];
    
    for(int i = 0; i < altoCajas; ++i) {
        this->matrizCajas[i] = new Caja[anchoCajas];
        for(int j = 0; j < anchoCajas; ++j) {
            // IMPORTANTE: Inicializar explícitamente sin poder
            this->matrizCajas[i][j].poderDisponible = TipoPoder::NINGUNO;
            this->matrizCajas[i][j].propietario = nullptr;
            
            // 25% de probabilidad de tener un poder
            if (rand() % 4 == 0) { 
                // Genera números del 1 al 5 para los poderes disponibles
                int poderIdx = rand() % 10 + 1;
                this->matrizCajas[i][j].poderDisponible = static_cast<TipoPoder>(poderIdx);
                
                // DEBUG: Imprime qué poder se asigna (opcional, puedes quitarlo después)
                cout << "DEBUG: Asignando poder " << poderIdx 
                         << " en caja (" << i << "," << j << ")" << std::endl;
            }
        }
    }
}

Tablero::~Tablero() {
    // ... (la lógica de borrado de nodos y cajas es igual que antes) ...
    NodoPunto* filaActual = this->esquinaSuperiorIzquierda;
    while (filaActual != nullptr) {
        NodoPunto* nodoActual = filaActual;
        NodoPunto* proximaFila = filaActual->abajo;
        while (nodoActual != nullptr) {
            NodoPunto* proximoNodo = nodoActual->derecha;
            delete nodoActual;
            nodoActual = proximoNodo;
        }
        filaActual = proximaFila;
    }
    int altoCajas = this->alto - 1;
    for(int i = 0; i < altoCajas; ++i) { delete[] this->matrizCajas[i]; }
    delete[] this->matrizCajas;
}

// Función auxiliar para navegar la malla
NodoPunto* Tablero::getNodo(int r, int c) const {
    if (r < 0 || r >= alto || c < 0 || c >= ancho) return nullptr;
    NodoPunto* actual = esquinaSuperiorIzquierda;
    for (int i = 0; i < r; ++i) actual = actual->abajo;
    for (int j = 0; j < c; ++j) actual = actual->derecha;
    return actual;
}

bool Tablero::dibujarLinea(int fila1, int columna1, int fial2, int columna2, Jugador* jugador, TipoPoder poderAplicado) {
    // Validaciones básicas
    if (fila1 < 0 || fila1 >= alto || columna1 < 0 || columna1 >= ancho || fial2 < 0 || fial2 >= alto || columna2 < 0 || columna2 >= ancho) {
        cout << "\n\033[31m[ERROR] Coordenadas fuera de los límites, intente de nuevo.\033[0m" << endl;
        return false;
    }
    if ((abs(fila1 - fial2) + abs(columna1 - columna2)) != 1) {
        cout << "\n\033[31m[ERROR] Los puntos no son adyacentes, intente de nuevo.\033[0m" << endl;
        return false;
    }

    // Aseguramos que (fila1, columna) sea el punto de origen (arriba o a la izquierda)
    if (fial2 < fila1 || columna2 < columna1) { std::swap(fila1, fial2); std::swap(columna1, columna2); }
    
    NodoPunto* origen = getNodo(fila1, columna1);

    // Dibujar línea horizontal
    if (fila1 == fial2) {
        if (origen->lineaHaciaDerecha) {
            std::cout << "[ERROR] La linea ya existe." << std::endl;
            return false;
        }
        origen->lineaHaciaDerecha = true;
        origen->efectoLineaDerecha = poderAplicado; // Aplicamos el efecto del poder
    } 
    // Dibujar línea vertical
    else {
        if (origen->lineaHaciaAbajo) {
            std::cout << "[ERROR] La linea ya existe." << std::endl;
            return false;
        }
        origen->lineaHaciaAbajo = true;
        origen->efectoLineaAbajo = poderAplicado; // Aplicamos el efecto del poder
    }

    return true;
}


// implementacion de la verificación
int Tablero::verificarYAsignarCaja(int r_linea, int c_linea, bool esHorizontal, Jugador* jugadorActual) {
    int cajasCerradas = 0;

    // --- Lógica para una LÍNEA HORIZONTAL ---
    if (esHorizontal) {
        // 1. Comprobar la caja de ARRIBA de la línea
        if (r_linea > 0) {
            int caja_r = r_linea - 1; // La fila de la caja de arriba
            int caja_c = c_linea;     // La columna de la caja
            
            // Si esta caja aún no tiene dueño, la analizamos
            if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
                // Comprobación directa de los 4 bordes de ESTA caja
                bool bordeSuperior = getNodo(caja_r, caja_c)->lineaHaciaDerecha;
                bool bordeInferior = getNodo(caja_r + 1, caja_c)->lineaHaciaDerecha; // Esta es la línea que se acaba de dibujar
                bool bordeIzquierdo = getNodo(caja_r, caja_c)->lineaHaciaAbajo;
                bool bordeDerecho = getNodo(caja_r, caja_c + 1)->lineaHaciaAbajo;

                // Si los 4 bordes existen, ¡la caja está cerrada!
                if (bordeSuperior && bordeInferior && bordeIzquierdo && bordeDerecho) {
                    matrizCajas[caja_r][caja_c].propietario = jugadorActual;
                    // Recogemos el poder de ESTA MISMA caja, garantizando que es el correcto
                    if (matrizCajas[caja_r][caja_c].poderDisponible != TipoPoder::NINGUNO) {
                        jugadorActual->agregarPoder(matrizCajas[caja_r][caja_c].poderDisponible);
                        matrizCajas[caja_r][caja_c].poderDisponible = TipoPoder::NINGUNO; // El poder se consume
                    }
                    cajasCerradas++;
                }
            }
        }
        // 2. Comprobar la caja de ABAJO de la línea
        if (r_linea < alto - 1) {
            int caja_r = r_linea; // La fila de la caja de abajo es la misma que la de la línea
            int caja_c = c_linea;

            if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
                // Comprobación directa de los 4 bordes de la caja de abajo
                bool bordeSuperior = getNodo(caja_r, caja_c)->lineaHaciaDerecha; // Esta es la línea recién dibujada
                bool bordeInferior = getNodo(caja_r + 1, caja_c)->lineaHaciaDerecha;
                bool bordeIzquierdo = getNodo(caja_r, caja_c)->lineaHaciaAbajo;
                bool bordeDerecho = getNodo(caja_r, caja_c + 1)->lineaHaciaAbajo;

                if (bordeSuperior && bordeInferior && bordeIzquierdo && bordeDerecho) {
                    matrizCajas[caja_r][caja_c].propietario = jugadorActual;
                    if (matrizCajas[caja_r][caja_c].poderDisponible != TipoPoder::NINGUNO) {
                        jugadorActual->agregarPoder(matrizCajas[caja_r][caja_c].poderDisponible);
                        matrizCajas[caja_r][caja_c].poderDisponible = TipoPoder::NINGUNO;
                    }
                    cajasCerradas++;
                }
            }
        }
    }
    // --- Lógica para una LÍNEA VERTICAL ---
    else {
        // 1. Comprobar la caja de la IZQUIERDA de la línea
        if (c_linea > 0) {
            int caja_r = r_linea;
            int caja_c = c_linea - 1; // La columna de la caja izquierda

            if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
                // Comprobación directa de los 4 bordes
                bool bordeSuperior = getNodo(caja_r, caja_c)->lineaHaciaDerecha;
                bool bordeInferior = getNodo(caja_r + 1, caja_c)->lineaHaciaDerecha;
                bool bordeIzquierdo = getNodo(caja_r, caja_c)->lineaHaciaAbajo;
                bool bordeDerecho = getNodo(caja_r, caja_c + 1)->lineaHaciaAbajo; // Línea recién dibujada

                if (bordeSuperior && bordeInferior && bordeIzquierdo && bordeDerecho) {
                    matrizCajas[caja_r][caja_c].propietario = jugadorActual;
                    if (matrizCajas[caja_r][caja_c].poderDisponible != TipoPoder::NINGUNO) {
                        jugadorActual->agregarPoder(matrizCajas[caja_r][caja_c].poderDisponible);
                        matrizCajas[caja_r][caja_c].poderDisponible = TipoPoder::NINGUNO;
                    }
                    cajasCerradas++;
                }
            }
        }
        // 2. Comprobar la caja de la DERECHA de la línea
        if (c_linea < ancho - 1) {
            int caja_r = r_linea;
            int caja_c = c_linea; // La columna de la caja derecha es la misma que la de la línea

            if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
                // Comprobación directa de los 4 bordes
                bool bordeSuperior = getNodo(caja_r, caja_c)->lineaHaciaDerecha;
                bool bordeInferior = getNodo(caja_r + 1, caja_c)->lineaHaciaDerecha;
                bool bordeIzquierdo = getNodo(caja_r, caja_c)->lineaHaciaAbajo; // Línea recién dibujada
                bool bordeDerecho = getNodo(caja_r, caja_c + 1)->lineaHaciaAbajo;

                if (bordeSuperior && bordeInferior && bordeIzquierdo && bordeDerecho) {
                    matrizCajas[caja_r][caja_c].propietario = jugadorActual;
                    if (matrizCajas[caja_r][caja_c].poderDisponible != TipoPoder::NINGUNO) {
                        jugadorActual->agregarPoder(matrizCajas[caja_r][caja_c].poderDisponible);
                        matrizCajas[caja_r][caja_c].poderDisponible = TipoPoder::NINGUNO;
                    }
                    cajasCerradas++;
                }
            }
        }
    }
    
    return cajasCerradas;
}

void Tablero::imprimirTablero(bool modoClarividente) const {
    //El arreglo debe coincidir con el numero asignado del enum de tipo poder
    const std::string simbolosPoder[] = {"", "DL", "TS", "BL", "PS", "LS","ES","UF","AC","NT","EX"};
    
    // Para efectos de línea en modo clarividente
    const std::string simbolosEfectoH[] = {"   ", "-D-", "-T-", "-B-", "---", "-L-","-E-","-U-","-Q-","-N-","-X-"};
    const std::string simbolosEfectoV[] = {" ", "D", "T", "B", "|", "L", "E","U","Q","N","X"};

    // El resto del código de impresión permanece igual...
    for (int i = 0; i < alto; ++i) {
        // Imprimir línea de puntos y conexiones horizontales
        for (int j = 0; j < ancho; ++j) {
            std::cout << "*";
            if (j < ancho - 1) {
                NodoPunto* nodo = getNodo(i, j);
                if (nodo->lineaHaciaDerecha) {
                    if (modoClarividente && nodo->efectoLineaDerecha != TipoPoder::NINGUNO) {
                        std::cout << simbolosEfectoH[static_cast<int>(nodo->efectoLineaDerecha)];
                    } else {
                        std::cout << "---";
                    }
                } else {
                    std::cout << "   ";
                }
            }
        }
        std::cout << std::endl;

        // Imprimir línea de conexiones verticales y contenido de las cajas
        if (i < alto - 1) {
            for (int j = 0; j < ancho; ++j) {
                NodoPunto* nodo = getNodo(i, j);
                if (nodo->lineaHaciaAbajo) {
                     if (modoClarividente && nodo->efectoLineaAbajo != TipoPoder::NINGUNO) {
                        std::cout << simbolosEfectoV[static_cast<int>(nodo->efectoLineaAbajo)];
                    } else {
                        std::cout << "|";
                    }
                } else {
                    std::cout << " ";
                }

                if (j < ancho - 1) {
                    Caja caja = matrizCajas[i][j];
                    if (caja.propietario != nullptr) {
                        std::cout << " " << caja.propietario->getInicial() << " ";
                    } else if (caja.poderDisponible != TipoPoder::NINGUNO) {
                        // CORRECCIÓN: Verificar que el índice sea válido
                        int indice = static_cast<int>(caja.poderDisponible);
                        if (indice >= 0 && indice < 11) {
                            std::cout << std::setw(3) << std::left << " " + simbolosPoder[indice];
                        } else {
                            std::cout << " ? "; // Símbolo de error si hay índice inválido
                        }
                    } else {
                        std::cout << "   ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}