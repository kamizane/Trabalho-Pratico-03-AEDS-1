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
    if(compartimento->tamanho != compartimento->tamanho_maximo){
        compartimento->rochas[compartimento->ultimo] = *rocha;
        compartimento->ultimo++;
        compartimento->tamanho++;
        return 1;
    }
    return 0;
}
