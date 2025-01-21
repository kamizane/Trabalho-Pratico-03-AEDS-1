
#ifndef MINERAL_H
#define MINERAL_H


//define a struct mineral contendo nome, cor, dureza e reatividade
typedef struct Mineral {
    char nome[20];
    char cor[20];
    float dureza;
    float reatividade;
} Mineral;

void atribui_mineral(Mineral * mineral, char nome_mineral[]);

void inicializa_mineral(Mineral * mineral, char nome[], char cor[], float dureza, float reatividade);


char * get_nome(Mineral * mineral);
char * get_cor(Mineral * mineral);
float get_dureza(Mineral * mineral);
float get_reatividade(Mineral * mineral);


void set_nome(Mineral * mineral, char * nome);
void set_cor(Mineral * mineral, char * cor);
void set_dureza(Mineral * mineral, float dureza);
void set_reatividade(Mineral * mineral, float reatividade);

#endif