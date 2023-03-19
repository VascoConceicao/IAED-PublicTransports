/* Main code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include"carreira.h"
#include"ligacao.h"
#include"paragem.h"

#define max_carreiras 200
#define max_paragens 10000
#define max_ligacoes 30000

#define max_nome_carreira 21
#define max_input 200

void swap(char* a, char* b) {
    char temp[strlen(a) + 1];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

int partition(char arr[][max_nome_carreira], int low, int high) {
    char pivot[50];
    strcpy(pivot, arr[high]);
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(char arr[][max_nome_carreira], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void i_command(char input[][max_input], int size_input, carreira** Carreiras_array, int* size_carreiras, paragem** Paragens_array, int* size_paragens){

    int i,j,k,curr_count;
    paragem* paragem_aux;
    char carreiras_array_aux[max_carreiras][max_nome_carreira];

    for (i=0;i<*size_paragens;i++){
        if (Paragens_array[i]->Numero_de_carreiras > 1){
            curr_count = 0;
            printf("%s %d:",Paragens_array[i]->Nome,Paragens_array[i]->Numero_de_carreiras);
            for(j=*size_carreiras-1;j>=0;j--){
                k = 0;
                if (Carreiras_array[j]->size_ligacoes != 0){
                    paragem_aux = Carreiras_array[j]->Ligacoes[k]->Origin;
                    while (1){
                        if (paragem_aux == NULL) break;
                        if (strcmp(paragem_aux->Nome,Paragens_array[i]->Nome)==0) {
                            strcpy(carreiras_array_aux[curr_count],Carreiras_array[j]->Nome);
                            curr_count += 1;
                            break;
                        }
                        if (k == Carreiras_array[j]->size_ligacoes) break;
                        paragem_aux = Carreiras_array[j]->Ligacoes[k]->Destiny;
                        k += 1;
                    }
                }
            }
            quicksort(carreiras_array_aux,0,Paragens_array[i]->Numero_de_carreiras-1);
            for (j = 0;j<Paragens_array[i]->Numero_de_carreiras;j++){
                if (j != Paragens_array[i]->Numero_de_carreiras) printf(" ");
                printf("%s",carreiras_array_aux[j]);
            }
            printf("\n");
        }

    }

    return;
}

void l_command(char input[][max_input], carreira** Carreiras_array, int* size_carreiras, paragem** Paragens_array, int* size_paragens){

    int i;
    float cost, duration;
    carreira *carreira;
    paragem *paragem_origin, *paragem_destiny;
    ligacao* Ligacao_nova;

    carreira = get_carreira(input[1], Carreiras_array, size_carreiras);
    if (carreira == NULL) {printf("%s: no such line.\n",input[1]); return;}

    paragem_origin = get_paragem(input[2],Paragens_array,size_paragens);
    if(paragem_origin == NULL) {printf("%s: no such stop.\n",input[2]); return;}
    paragem_destiny = get_paragem(input[3],Paragens_array,size_paragens);
    if(paragem_destiny == NULL) {printf("%s: no such stop.\n",input[3]); return;}


    if(carreira->flag){
        carreira->Origin = paragem_origin;
        carreira->Destiny = paragem_destiny;
        carreira->flag = 0;
    }
    else{
        if(strcmp(paragem_origin->Nome,carreira->Destiny->Nome) != 0 && strcmp(paragem_destiny->Nome,carreira->Origin->Nome) != 0) {
            printf("link cannot be associated with bus line.\n");
            return;
        }
    }

    cost = atof(input[4]);
    duration = atof(input[5]);
    if(cost<0 || duration<0) {
        carreira->Origin = NULL;
        carreira->Destiny = NULL;
        carreira->flag = 1;
        printf("negative cost or duration.\n"); 
        return;
    }

    Ligacao_nova = create_ligacao(paragem_origin,paragem_destiny,cost,duration);
    insert_ligacao(Ligacao_nova,carreira);

}

void c_command(char input[][max_input], int size_input, carreira** Carreiras_array, int* size){
    if (size_input == 1) {print_carreira(Carreiras_array,"not a name",size); return;}

    if (size_input == 2) {
        carreira* Carreira_nova = create_carreira(input[1]);
        int controlo = insert_carreira(Carreiras_array,size,Carreira_nova);
        if (controlo == -1) print_carreira(Carreiras_array,input[1],size);
        return;
    }
}

void p_command(char input[][max_input], int size_input, paragem** Paragens_array, int* size){

    if (size_input == 1) {print_paragem(Paragens_array,NULL,-1,size);return;}

    if (size_input == 2) {
        paragem* paragem = get_paragem(input[1],Paragens_array,size);
        if (paragem == NULL) {printf("%s: no such stop.\n",input[1]); return;}
        print_paragem(Paragens_array,paragem,0,size);
        return;
    }
    
    if (size_input == 4) {
        paragem* Paragem_nova = create_paragem(input[1],atof(input[2]),atof(input[3]));
        int controlo = insert_paragem(Paragem_nova,Paragens_array,size);
        if (controlo == -1) printf("%s: stop already exists.\n",input[1]);
    }
}

int main(){
    int size_paragens = 0, size_carreiras = 0, count = 0,i;
    char *token, *token_aux, token_copy[max_input], input[max_input],input_strings_array[6][max_input];
    const char s[2] = " ";
    paragem* Paragens_array[10000];
    carreira* Carreiras_array[10000];

    while (1){

        count = 0;

        if(scanf("%[^\n]%*c", input)){};
        if (strcmp(input,"q") == 0) break;

        token = strtok(input, s);

        while(token != NULL) {

            if (token[0] == 34){

                strcpy(token_copy,token);
                token_aux = strtok(NULL, s);

                strcat(token_copy," ");
                strcat(token_copy, token_aux);

                token_copy[strlen(token_copy)-1] = '\0';
                memmove(token_copy,token_copy + 1,strlen(token_copy));
                
                strcpy(input_strings_array[count],token_copy);
            }

            else strcpy(input_strings_array[count],token);

            count += 1;
            token = strtok(NULL, s);
        }

/*         printf("Input: ");
        for(i=0;i<count;i++) printf("%s ",input_strings_array[i]);
        printf("\n"); */

        if (input[0] == 'p') {
            p_command(input_strings_array,count,Paragens_array,&size_paragens);
            continue;
        }

        if (input[0] == 'c') {
            c_command(input_strings_array,count,Carreiras_array,&size_carreiras);
            continue;
        }

        if (input[0] == 'l') {
            l_command(input_strings_array,Carreiras_array,&size_carreiras,Paragens_array,&size_paragens);
            continue;
        }

        if (input[0] == 'i') {
            i_command(input_strings_array,count,Carreiras_array,&size_carreiras,Paragens_array,&size_paragens);
            continue;
        }

    }
    
    return 0;
}