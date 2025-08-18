#ifndef TIPO_PODER_H
#define TIPO_PODER_H

#include <iostream>

enum class TipoPoder{
    DOBLE_LINEA,
    TRAMPA_SECRETA,
    BLOQUEO,
    PASE,
    LLAVE_SECRETA,
    NINGUNO
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
    default:                    return "desconocido";
    }
}

#endif