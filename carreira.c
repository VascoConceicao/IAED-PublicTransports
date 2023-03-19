/* Carreira library */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "paragem.h"
#include "carreira.h"
#include "ligacao.h"

#define max_nome_carreira 20

carreira* create_carreira(char* nome) {
    carreira* new_carreira = malloc(sizeof(carreira));
    new_carreira->Nome = strdup(nome);
    new_carreira->Numero_de_paragens = 0;
    new_carreira->flag = 1;
    new_carreira->Origin = NULL;
    new_carreira->Destiny = NULL;
    new_carreira->Ligacoes = NULL;
    new_carreira->size_ligacoes = 0;

    return new_carreira;
}

float get_custo(carreira* carreira_){
    int i; float sum = 0;
    for (i = 0;i<carreira_->size_ligacoes;i++)sum += carreira_->Ligacoes[i]->Cost;
    return sum;
}

float get_duracao(carreira* carreira_){
    int i; float sum = 0;
    for (i = 0;i<carreira_->size_ligacoes;i++) sum += carreira_->Ligacoes[i]->Duration;
    return sum;
}

carreira* get_carreira(char* Nome, carreira* Carreiras_array[10000],int* size){
    int i;
    for(i=0;i<*size;i++) 
        if(strcmp(Nome,Carreiras_array[i]->Nome) == 0) return Carreiras_array[i];
    return NULL;
}

void print_carreira(carreira** Carreiras_array, char* name, int* size){
    int i; carreira* carreira_;
    float Custo_Total, Duracao_Total;
    if (strcmp(name,"not a name")==0){
        for (i=0;i<*size;i++){
            if (Carreiras_array[i]->flag) printf("%s %d %.2f %.2f\n",Carreiras_array[i]->Nome,Carreiras_array[i]->Numero_de_paragens,0.00,0.00);
            
            else {
                Custo_Total = get_custo(Carreiras_array[i]);
                Duracao_Total = get_duracao(Carreiras_array[i]);

                printf("%s %s %s %d %.2f %.2f\n",Carreiras_array[i]->Nome,Carreiras_array[i]->Origin->Nome,Carreiras_array[i]->Destiny->Nome,Carreiras_array[i]->Numero_de_paragens,Custo_Total,Duracao_Total);
            }
        }
        return;
    }
    carreira_ = get_carreira(name,Carreiras_array,size);
    for (i=0;i<carreira_->size_ligacoes;i++) printf("%s, ",carreira_->Ligacoes[i]->Origin->Nome);
    printf("%s\n",carreira_->Destiny->Nome);
    
}

int insert_carreira(carreira* carreiras_array[10000], int* size, carreira* carreira_to_insert) {

    if (get_carreira(carreira_to_insert->Nome,carreiras_array,size) != NULL) return -1;
    
    carreiras_array[*size] = carreira_to_insert;
    *size += 1;
    return 0;
}

void insert_ligacao(ligacao* ligacao_inserida, carreira* carreira){
    int i;

    if (carreira->size_ligacoes == 0){

        carreira->Ligacoes = (ligacao**)realloc(carreira->Ligacoes,(carreira->size_ligacoes+1)*sizeof(ligacao*));
        carreira->Ligacoes[0] = ligacao_inserida;

        ligacao_inserida->Origin->Numero_de_carreiras += 1;
        ligacao_inserida->Destiny->Numero_de_carreiras += 1;
        
        carreira->Numero_de_paragens = 2;
        carreira->size_ligacoes += 1;
        return;
    }

    if(strcmp(ligacao_inserida->Origin->Nome,carreira->Destiny->Nome) == 0 && strcmp(ligacao_inserida->Destiny->Nome,carreira->Origin->Nome) == 0){

        carreira->Ligacoes = (ligacao**)realloc(carreira->Ligacoes,(carreira->size_ligacoes+1)*sizeof(ligacao*));
        carreira->Ligacoes[carreira->size_ligacoes] = ligacao_inserida;

        carreira->Destiny = ligacao_inserida->Destiny;

        carreira->Numero_de_paragens += 1;
        carreira->size_ligacoes += 1;
        return;
    }

    if(strcmp(ligacao_inserida->Origin->Nome,carreira->Destiny->Nome) == 0){

        carreira->Ligacoes = (ligacao**)realloc(carreira->Ligacoes,(carreira->size_ligacoes+1)*sizeof(ligacao*));
        carreira->Ligacoes[carreira->size_ligacoes] = ligacao_inserida;

        ligacao_inserida->Destiny->Numero_de_carreiras += 1;
        
        carreira->Destiny = ligacao_inserida->Destiny;

        carreira->Numero_de_paragens += 1;
        carreira->size_ligacoes += 1;
        return;
    }

    if(strcmp(ligacao_inserida->Destiny->Nome,carreira->Origin->Nome) == 0){

        carreira->Ligacoes = (ligacao**)realloc(carreira->Ligacoes,(carreira->size_ligacoes+1)*sizeof(ligacao*));

        for (i = carreira->size_ligacoes - 1; i >= 0; i--) carreira->Ligacoes[i + 1] = carreira->Ligacoes[i];
        carreira->Ligacoes[0] = ligacao_inserida;

        ligacao_inserida->Origin->Numero_de_carreiras += 1;

        carreira->Origin = ligacao_inserida->Origin;

        carreira->Numero_de_paragens += 1;
        carreira->size_ligacoes += 1;
        return;
    }

}