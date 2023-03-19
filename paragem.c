/* Paragem library */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "paragem.h"

/* print_paragem (-1 print all) , create_paragem, insert_paragem, get_paragem */

paragem* create_paragem(char* nome, double Latitude, double Longitude){

    paragem* new_paragem = malloc(sizeof(paragem));
    new_paragem->Nome = strdup(nome);
    new_paragem->Latitude = Latitude;
    new_paragem->Longitude = Longitude;
    new_paragem->Numero_de_carreiras = 0;

    return new_paragem;
}

void print_paragem(paragem** Paragens_array, paragem* paragem,int index, int* size){
    int i;
    if (index == -1){
        for (i=0;i<*size;i++)
            printf("%s: %16.12f %16.12f %d\n",Paragens_array[i]->Nome,Paragens_array[i]->Latitude,Paragens_array[i]->Longitude,Paragens_array[i]->Numero_de_carreiras);
        return;
    }
    printf("%16.12f %16.12f\n",paragem->Latitude,paragem->Longitude);
}

paragem* get_paragem(char* Nome, paragem* Paragens_array[10000],int* size){ /* -1 if it doesn't exist*/
    int i;
    for(i=0;i<*size;i++) 
        if(strcmp(Nome,Paragens_array[i]->Nome) == 0) return Paragens_array[i];
    return NULL;
}

int insert_paragem(paragem* paragem_to_insert, paragem* paragens_array[10000], int* size){ /* -1 if already exists*/

    if (get_paragem(paragem_to_insert->Nome,paragens_array,size) != NULL) return -1;
    
    paragens_array[*size] = paragem_to_insert;
    *size += 1;
    return 0;
}