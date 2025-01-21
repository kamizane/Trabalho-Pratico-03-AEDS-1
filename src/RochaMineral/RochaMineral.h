#ifndef ROCHA_MINERAL_H
#define ROCHA_MINERAL_H

#include "../ListaMinerais/ListaMinerais.h"
typedef ListaMinerais MLista;

//estabelecendo a localização da rocha mineral como uma estrutura que possui latitude e longitude
typedef struct LocalRochaMineral{
    float latitude;
    float longitude;
}LocalRochaMineral;

//definição do tipo RochaMineral
typedef struct RochaMineral{
    int id;
    float peso;
    MLista *lista;
    char categoria[20];
    LocalRochaMineral local;
}RochaMineral;

//cabeçalho das funções

void inicializaRochaMineral(RochaMineral *rocha, int id, float peso, MLista *lista,
    LocalRochaMineral local);

int getId(RochaMineral* rocha);
float getPeso(RochaMineral* rocha);
char *getCategoria(RochaMineral* rocha);
MLista *getListaMinerais(RochaMineral* rocha);
float getLatitude(RochaMineral* rocha);
float getLongitude(RochaMineral* rocha);

void setId(RochaMineral* rocha, int id);
void setPeso(RochaMineral* rocha, float peso);
void setListaMinerais(RochaMineral* rocha, MLista* lista);
void setCategoria(RochaMineral* rocha, char *categoria);
void setLatitude(RochaMineral* rocha, float latitude);
void setLongitude(RochaMineral* rocha, float longitude);

void escolheCategoria(RochaMineral *rocha);

#endif
