/* Carreira header */

#ifndef CARREIRA_H
#define CARREIRA_H

#include "paragem.h"
#include "ligacao.h"

typedef struct {
    char* Nome;
    int Numero_de_paragens, flag;
    paragem* Origin;
    paragem* Destiny;
    ligacao** Ligacoes;
    int size_ligacoes;

}   carreira;

carreira* create_carreira(char* Nome);
float get_custo(carreira* carreira_);
float get_duracao(carreira* carreira_);
void print_carreira(carreira* Carreiras_array[10000], char* name, int* size);
carreira* get_carreira(char* Nome, carreira* Carreiras_array[10000], int* size);
int insert_carreira(carreira* carreiras_array[10000], int* size, carreira* carreira_to_insert);
void insert_ligacao(ligacao* ligacao_nova, carreira* carreira);

#endif
