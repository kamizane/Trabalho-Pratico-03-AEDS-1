#ifndef LISTA_MINERAIS_H
#define LISTA_MINERAIS_H
#define InicioArranjo 0
#define MaxTam 3

#include "..\Mineral/mineral.h"

//definindo o tipo Apontador
typedef int Apontador;
typedef Mineral TChave;

typedef struct TItem
{
  TChave Chave;
}TItem;

//definindo o tipo ListaMinerais
typedef struct ListaMinerais{
  TItem minerais[MaxTam];
  Apontador Primeiro, Ultimo;
}ListaMinerais;

//cabeçalho das funções básicas
int listaMineraisEVazia(ListaMinerais* pLista);
int insereMineralLista(ListaMinerais* pLista, TItem x);
void fListaMineraisVazia(ListaMinerais* pLista);
int retiraMineralLista(ListaMinerais* pLista, char *nome);
void imprimeListaMinerais(ListaMinerais* pLista);

#endif
