#include <stdio.h>
#include <string.h>
#include "./Mineral.h"

void atribui_mineral(Mineral * mineral, char nome_mineral[]){//coloca todas as informaçoes em um mineral de acordo com o nome recebido
    char cor[20];
    float dureza;
    float reatividade;

    if (strcmp(nome_mineral, "Ferrolita")==0){
        strcpy(cor,"cinza");
        dureza =0.5;
        reatividade =0.7;
    } else if (strcmp(nome_mineral , "Solarium")==0){
        strcpy(cor,"amarelo");
        dureza = 0.9;
        reatividade =0.2;
    }else if (strcmp(nome_mineral , "Aquavitae")==0){
        strcpy(cor,"azul");
        dureza =0.5;
        reatividade =0.8;

    } else if (strcmp(nome_mineral , "Terranita")==0){
        strcpy(cor,"marrom");
        dureza =0.7;
        reatividade =0.6;
    } else if (strcmp(nome_mineral ,"Calaris")==0){
        strcpy(cor,"vermelho");
        dureza =0.6;
        reatividade =0.5;
    }

    inicializa_mineral(mineral,nome_mineral, cor, dureza,reatividade);
}

void inicializa_mineral(Mineral * mineral, char nome[], char cor[], float dureza, float reatividade){ //inicializa um mineral pegando todas as informaçoes
    set_nome(mineral, nome);
    set_cor(mineral, cor);
    set_dureza(mineral, dureza);
    set_reatividade(mineral, reatividade);
}


char * get_nome(Mineral * mineral){
    return (mineral->nome);
}


char * get_cor(Mineral * mineral){
    return (mineral->cor);
}


float get_dureza(Mineral * mineral){
    return mineral->dureza;
}


float get_reatividade(Mineral * mineral){
    return mineral->reatividade;
}


void set_nome(Mineral * mineral, char * nome){
    strcpy(mineral->nome , nome);
}


void set_cor(Mineral * mineral, char * cor){
    strcpy(mineral->cor, cor);
}


void set_dureza(Mineral * mineral, float dureza){
    mineral->dureza = dureza;
}


void set_reatividade(Mineral * mineral, float reatividade){
    mineral->reatividade = reatividade;
}



