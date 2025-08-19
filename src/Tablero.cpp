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
            if (rand() % 4 == 0) { 
                int poderIdx = rand() % 5 + 1;
                this->matrizCajas[i][j].poderDisponible = static_cast<TipoPoder>(poderIdx);
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
        std::cout << "[ERROR] Coordenadas fuera de los límites." << std::endl;
        return false;
    }
    if ((abs(fila1 - fial2) + abs(columna1 - columna2)) != 1) {
        std::cout << "[ERROR] Los puntos no son adyacentes." << std::endl;
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
    
    // Lógica para línea HORIZONTAL
    if (esHorizontal) {
        // Chequear caja de ARRIBA
        if (r_linea > 0) {
            NodoPunto* p1 = getNodo(r_linea - 1, c_linea);
            NodoPunto* p2 = getNodo(r_linea - 1, c_linea + 1);
            if (p1->lineaHaciaDerecha && p1->lineaHaciaAbajo && p2->lineaHaciaAbajo) {
                int caja_r = r_linea - 1;
                int caja_c = c_linea;
                if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
                    matrizCajas[caja_r][caja_c].propietario = jugadorActual;
                    if (matrizCajas[caja_r][caja_c].poderDisponible != TipoPoder::NINGUNO) {
                        jugadorActual->agregarPoder(matrizCajas[caja_r][caja_c].poderDisponible);
                        matrizCajas[caja_r][caja_c].poderDisponible = TipoPoder::NINGUNO;
                    }
                    cajasCerradas++;
                }
            }
        }
        // Chequear caja de ABAJO
        if (r_linea < alto - 1) {
            NodoPunto* p1 = getNodo(r_linea, c_linea);
            NodoPunto* p2 = getNodo(r_linea, c_linea + 1);
            if (p1->lineaHaciaAbajo && p2->lineaHaciaAbajo && getNodo(r_linea+1,c_linea)->lineaHaciaDerecha) {
                int caja_r = r_linea;
                int caja_c = c_linea;
                if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
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
    // Lógica para línea VERTICAL (similar)
    else {
        // Chequear caja IZQUIERDA
        if (c_linea > 0) {
            NodoPunto* p1 = getNodo(r_linea, c_linea - 1);
            NodoPunto* p2 = getNodo(r_linea + 1, c_linea - 1);
            if (p1->lineaHaciaDerecha && p1->lineaHaciaAbajo && p2->lineaHaciaDerecha) {
                 int caja_r = r_linea;
                 int caja_c = c_linea - 1;
                 if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
                    matrizCajas[caja_r][caja_c].propietario = jugadorActual;
                    if (matrizCajas[caja_r][caja_c].poderDisponible != TipoPoder::NINGUNO) {
                        jugadorActual->agregarPoder(matrizCajas[caja_r][caja_c].poderDisponible);
                        matrizCajas[caja_r][caja_c].poderDisponible = TipoPoder::NINGUNO;
                    }
                    cajasCerradas++;
                 }
            }
        }
        // Chequear caja DERECHA
        if (c_linea < ancho - 1) {
            NodoPunto* p1 = getNodo(r_linea, c_linea);
            NodoPunto* p2 = getNodo(r_linea + 1, c_linea);
             if (p1->lineaHaciaDerecha && p2->lineaHaciaDerecha && getNodo(r_linea, c_linea+1)->lineaHaciaAbajo) {
                 int caja_r = r_linea;
                 int caja_c = c_linea;
                 if (matrizCajas[caja_r][caja_c].propietario == nullptr) {
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
    // Símbolos para los poderes disponibles en el tablero
    const std::string simbolosPoder[] = {"", "DL", "TS", "BL", "PS", "LS"};
    // Símbolos para los efectos de línea en modo clarividente
    const std::string simbolosEfectoH[] = {"   ", "-D-", "-T-", "-B-", "---", "-L-"};
    const std::string simbolosEfectoV[] = {" ", "D", "T", "B", "|", "L"};

    for (int i = 0; i < alto; ++i) {
        // --- Imprimir línea de puntos y conexiones horizontales ---
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

        // --- Imprimir línea de conexiones verticales y contenido de las cajas ---
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
                        std::cout << std::setw(3) << std::left << " " + simbolosPoder[static_cast<int>(caja.poderDisponible)];
                    } else {
                        std::cout << "   ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}