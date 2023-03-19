/* Paragem header */

#ifndef PARAGEM_H
#define PARAGEM_H

typedef struct {
    char* Nome;
    double Latitude, Longitude;
    int Numero_de_carreiras;
    
}   paragem;


paragem* create_paragem(char* nome, double Longitude, double Latitude);
void print_paragem(paragem** Paragens_array, paragem* paragem,int index, int* size);
paragem* get_paragem(char* Nome, paragem* Paragens_array[10000],int* size);
int insert_paragem(paragem* paragem_to_insert, paragem* paragens_array[10000], int* size);

#endif