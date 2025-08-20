#ifndef TIPO_PODER_H
#define TIPO_PODER_H

#include <iostream>

enum class TipoPoder {
    NINGUNO = 0,
    DOBLE_LINEA = 1,
    TRAMPA_SECRETA = 2, 
    BLOQUEO = 3,
    PASE = 4,
    LLAVE_SECRETA = 5,
    ESCURRIDIZO=6,
    UNION_A_FUTURO=7,
    A_QUE_COSTO=8,
    NUEVAS_TIERRAS=9,
    EXPLOSIVOS=10
};

//FUNCION QUE CONVIERTE UN PODER EN UN STRING LEGIBLE
inline std::string poderAString(TipoPoder poder){
    switch (poder)
    {
    case TipoPoder::DOBLE_LINEA: return "Doble Linea";
    case TipoPoder::BLOQUEO: return "Bloqueo";
    case TipoPoder::LLAVE_SECRETA: return "Llave secreta";
    case TipoPoder::PASE: return "Pase";
    case TipoPoder::TRAMPA_SECRETA: return "Trampa secreta";
    case TipoPoder::NINGUNO:         return "Ninguno";
    case TipoPoder::ESCURRIDIZO:    return "Escurridizo";
    case TipoPoder::UNION_A_FUTURO:  return "Union a futuro";
    case TipoPoder::A_QUE_COSTO:    return "A que costo";
    case TipoPoder::NUEVAS_TIERRAS: return "Nuevas Tierras";
    case TipoPoder::EXPLOSIVOS:     return "Explosivos";
    default:                    return "desconocido";
    }
}

#endif