#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H
#define inicio_arranjo_compartimento 0

#include "../RochaMineral/RochaMineral.h"

typedef struct{

    RochaMineral* rochas;
    int tamanho_maximo;
    int tamanho;
    int ultimo, primeiro;
    float peso_atual;

} Compartimento;


void faz_compartimento_vazio(Compartimento* compartimento, int tamanho_maximo);

int tamanho_do_compartimento(Compartimento* compartimento);

int compartimento_eh_vazio(Compartimento* compartimento);

int imprime_compartimento(Compartimento* compartimento);

float retorna_peso_atual(Compartimento* compartimento);

int inserir_rocha(Compartimento* compartimento, RochaMineral* rocha);
void insertion_sort(Compartimento* compartimento, int* comparacoes, int* movimentacoes);
void quick_sort(Compartimento* compartimento, int* comparacoes, int* movimentacoes);


#endif