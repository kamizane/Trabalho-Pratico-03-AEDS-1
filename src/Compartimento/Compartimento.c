#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Compartimento.h"

#define inicio_arranjo_compartimento 0



void faz_compartimento_vazio(Compartimento* compartimento, int tamanho_maximo){ //cria um compartimento vazio com um peso maximo fornecido pelo usuario
    compartimento->rochas = (RochaMineral*)calloc(sizeof(RochaMineral),tamanho_maximo);
    compartimento->tamanho_maximo = tamanho_maximo;
    compartimento->primeiro = inicio_arranjo_compartimento;
    compartimento->ultimo = compartimento->primeiro;
    compartimento->tamanho = 0;
    compartimento->peso_atual = 0;
}

int tamanho_do_compartimento(Compartimento* compartimento){
    return compartimento->tamanho;
}

int compartimento_eh_vazio(Compartimento* compartimento){
    return (compartimento->tamanho == 0);
}

int imprime_compartimento(Compartimento* compartimento){  //imprime as rochas presentes no compartimento com a sua categoria e peso 
    
    //verifica se é vazio antes de fazer qualquer impressão
    if (compartimento_eh_vazio(compartimento)){
        printf("compartimento vazio!\n");
        return 0;
    }
    
    //percorre todas as rochas, imprimindo-as
    for(int i = 0;i<compartimento->tamanho;i++){
        printf("%s %.2f\n",compartimento->rochas[i].categoria, compartimento->rochas[i].peso);
    }
    return 1;
}

float retorna_peso_atual(Compartimento* compartimento){
    return compartimento->peso_atual;
}


int inserir_rocha(Compartimento* compartimento, RochaMineral* rocha){ //adiciona rocha ao compartimento
    if(compartimento->tamanho < compartimento->tamanho_maximo){
        compartimento->rochas[compartimento->ultimo] = *rocha;
        compartimento->ultimo++;
        compartimento->tamanho++;
        return 1;
    }
    return 0;
}

void insert_sort(Compartimento* compartimento, int* comparacoes, int* movimentacoes){
    int n = compartimento->ultimo;

    for(int i = 0; i < n; i++){
        RochaMineral chave = compartimento->rochas[i];

        int j = i - 1;

        while (j >= 0 && compartimento->rochas[i].peso > chave.peso){
            *comparacoes++;
            compartimento->rochas[j+1] = compartimento->rochas[i];
            *movimentacoes++;
            j--;
        }
        compartimento->rochas[j+1] = chave;
        
    }
}


void particao_quick(Compartimento*compartimento, int esq, int dir, int*i, int*j, int * comparacoes, int * movimentacoes){
    *comparacoes +=1;
    RochaMineral pivo, aux;  
    *i = esq; *j = dir;
    pivo = compartimento->rochas[(*i + *j)/2];  

    do{
        while(pivo.peso > compartimento->rochas[*i].peso){
            (*i)++;
            *comparacoes +=1;
        }
        while(pivo.peso < compartimento->rochas[*j].peso){
            (*j)--;
            *comparacoes+=1;
        }
        if(*i<=*j){
            *comparacoes +=1;
            aux = compartimento->rochas[*i]; compartimento->rochas[*i] = compartimento->rochas[*j]; compartimento->rochas[*j] = aux;
            *movimentacoes+=1;
            (*i)++; (*j)--;
        }

        *comparacoes +=1;
    }while(*i <=*j);
}

void ordena_quick(Compartimento* compartimento, int esq, int dir, int * comparacoes, int * movimentacoes){

    int i,j;
    particao_quick(compartimento, esq, dir, &i,&j, comparacoes, movimentacoes);
    if(esq<j)ordena_quick(compartimento,esq,j, comparacoes, movimentacoes);
    *comparacoes +=1;
    if(i<dir)ordena_quick(compartimento,i,dir, comparacoes, movimentacoes);
    *comparacoes +=1;
}

void quick_sort(Compartimento* compartimento, int* comparacoes, int* movimentacoes){
    ordena_quick(compartimento,0, compartimento->tamanho-1,comparacoes,movimentacoes);
    
}

 
