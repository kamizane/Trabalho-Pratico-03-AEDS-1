#include <stdio.h>
#include <string.h>
#include ".\ListaMinerais.h"

#define InicioArranjo 0
#define MaxTam 3

//função que verifica se lista é vazia
int listaMineraisEVazia(ListaMinerais* pLista){
    return (pLista->Ultimo == pLista->Primeiro);
}

//função que insere um novo mineral na lista
int insereMineralLista(ListaMinerais* pLista, TItem x){
    //certificando que a lista não está cheia - tamanho 3 ou maior
    if (pLista->Ultimo == MaxTam){
        //se a lista estiver cheia, não é possível adicionar o mineral
        return 0;
    }
    //adicionando o mineral x na última posição disponível
    pLista->minerais[pLista->Ultimo] = x;

    //incrementando o Apontador Ultimo, já que temos mais um elemento na lista
    pLista->Ultimo++;
    
    //inserção concluída
    return 1;
}

//função que cria uma lista vazia de minerais
void fListaMineraisVazia(ListaMinerais* pLista){
    //Apontador Primeiro = 0
    pLista->Primeiro = InicioArranjo;
    //Apontador Ultimo = 0
    pLista->Ultimo = pLista->Primeiro;
}

//função que retira um mineral da lista a partir do nome do mineral
int retiraMineralLista(ListaMinerais* pLista, char *nome){
    //certificando que a lista não é vazia
    if (listaMineraisEVazia(pLista)){
        return 0;
    }else{

        //passando por todos os elementos da lista procurando o nome desejado
        for (int i = pLista->Primeiro; i < pLista->Ultimo; i++){
            //comparando o nome desejado com o nome do mineral da posição i da lista de minerais
            TChave m = pLista->minerais[i].Chave;
            if(strcmp(m.nome, nome) == 0){
                
                //subtraindo 1 do Apontador Ultimo, pois temos um item a menos na lista
                pLista->Ultimo--;

                //passando os minerais seguintes ao 'minerais[i]' para a posição anterior
                for(int j = i+1; j <= pLista->Ultimo; j++){
                    pLista->minerais[j-1] = pLista->minerais[j];
                }

                //remoção concluída
                return 1;
            }
        }
        //não foi encontrado o mineral
        return 0;
    }
    
} 

//digitando os atributos de cada elemento da lista
void imprimeListaMinerais(ListaMinerais* pLista){
    for(int i = pLista->Primeiro; i < pLista->Ultimo; i++){
        TChave m = pLista->minerais[i].Chave;
        printf("Nome: %s, Cor: %s, Dureza: %f, Reatividade: %f\n", 
        m.nome, m.cor, m.dureza, m.reatividade);
    }
} 

