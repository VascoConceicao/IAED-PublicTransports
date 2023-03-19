/* Ligacao library */

#include <stdlib.h>

#include "paragem.h"
#include "ligacao.h"

ligacao* create_ligacao(paragem *Origin, paragem *Destiny, float cost, float duration){

    ligacao* new_ligacao;
    new_ligacao = (ligacao*)malloc(sizeof(ligacao*));
    new_ligacao->Origin = Origin;
    new_ligacao->Destiny = Destiny;
    new_ligacao->Cost = cost;
    new_ligacao->Duration = duration;
    
    return new_ligacao;
}