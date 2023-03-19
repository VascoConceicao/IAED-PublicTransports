/* Ligacao header */

#ifndef LIGACAO_H
#define LIGACAO_H

#include "paragem.h"

typedef struct {
    paragem* Origin;
    paragem* Destiny;
    float Cost;
    float Duration;

}   ligacao;

ligacao* create_ligacao(paragem *Origin, paragem *Destiny, float cost, float duration);

#endif