#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Compartimento\Compartimento.h"

//Cabecalho das funcoes
FILE *leitura_arq(int argc, char **argv);
void case_R_file(FILE * file, ListaMinerais * lista_minerais_file, Compartimento * Compartimento);
void cria_rocha(float lat_rocha, float long_rocha, float peso_rocha, ListaMinerais* lista_minerais, Compartimento * Compartimento);
void imprime_saida(Compartimento * compartimento,int comparacoes,int movimentacoes, double tempo, char algoritmo[]);

int main(int argc, char **argv){
    if (leitura_arq(argc,argv) != 0){
        FILE *file = leitura_arq(argc,argv);
        if (file == NULL){//verifica se o arquivo tem algo a ser lido
            printf("Arquivo de entrada Invalido");
            return 0;
        }

        int comparacoes1 = 0,comparacoes2 = 0, movimentacoes1 = 0, movimentacoes2 = 0;
        clock_t inicio = 0, fim = 0;
        double tempo1 = 0,tempo2 = 0;

        //le o numero de rochas do arquivo
        int N_rochas = 0;
        fscanf(file,"%d",&N_rochas); fgetc(file);

        //cria vazio os compartimentos a ser preenchido com as rochas e, posteriormente, ordenados
        Compartimento compartimento_1;
        Compartimento compartimento_2;
        faz_compartimento_vazio(&compartimento_1,N_rochas);
        faz_compartimento_vazio(&compartimento_2,N_rochas);

        //executa a leitura das N_rochas
        for(int i=0;i<N_rochas;i++){
            ListaMinerais lista_minerais_file;
            fListaMineraisVazia(&lista_minerais_file);
            case_R_file(file, &lista_minerais_file, &compartimento_2);
        }

        //Clonando o compartimento para que os dados possam ser ordenados duas vezes
        compartimento_1 = compartimento_2;

        //inicio da medicao de tempo do algoritimo 1
        inicio = clock();
        insert_sort(&compartimento_1,&comparacoes1, &movimentacoes1);
        fim = clock();
        tempo1 = (double)(fim-inicio)/CLOCKS_PER_SEC;

        //inicio da medicao de tempo do algoritimo 2
        inicio = clock();
        quick_sort(&compartimento_2,&comparacoes2,&movimentacoes2);
        fim = clock();
        tempo2 = (double)(fim-inicio)/CLOCKS_PER_SEC;

        imprime_saida(&compartimento_1,comparacoes1,movimentacoes1,tempo1,"InsertSort");
        imprime_saida(&compartimento_2,comparacoes2,movimentacoes2,tempo2,"QuickSort");
    }    
    return 0;
}


FILE *leitura_arq(int argc, char **argv){
    //verifica se existe argumentos validos para iniciar leitura por arquivo
    if(argc > 1 && strcmp(argv[1], "-f") == 0){
        FILE *file = fopen(argv[2],"r");

    return file;
    }
    else{
        printf("Arquivo não encontrado");
        return 0;
    }
}

//inicia a leitura dos dados para criar a rocha, dispostos em uma linha do arquivo
void case_R_file(FILE * file, ListaMinerais * lista_minerais_file, Compartimento * Compartimento){
    char linha[255];
    char *buffer = NULL;
    const char delim[2] = " ";
    float lat_rocha = 0, long_rocha = 0, peso_rocha = 0;
    fgets(linha,255,file);
    Mineral minerais[3];
    char nome_mineral[15];
    linha[strlen(linha) - 1] = '\0';

    /*secciona a linha capturada a partir do padrao definido no delim ou seja, 
    separa os 3 primeiros tokens entre espaco e atribui para sua variavel correspondente.*/
    buffer = strtok(linha,delim);
    lat_rocha = atof(buffer);

    buffer = strtok(NULL,delim);
    long_rocha = atof(buffer);

    buffer = strtok(NULL,delim);
    peso_rocha = atof(buffer);

    int m = 0;
    fListaMineraisVazia(lista_minerais_file);

    /*conclui a leitura da linha lendo os ultimos tokens e inserindo na lista. Esses tokens varia de 1 a 3, 
    por isso a verificacao que encerra o while ao chegar em um valor NULL*/
    while((buffer = strtok(NULL, delim)) != NULL){
        strcpy(nome_mineral, buffer);
        atribui_mineral(&minerais[m], nome_mineral);
        TItem a = {minerais[m]}; 
        insereMineralLista(lista_minerais_file, a);
        m++;
}
cria_rocha(lat_rocha, long_rocha, peso_rocha, lista_minerais_file, Compartimento);
}


//Funcao responsavel por criar uma nova rocha
void cria_rocha(float lat_rocha, float long_rocha, float peso_rocha, ListaMinerais* lista_minerais, Compartimento * Compartimento){
    static int contId = 1;

    LocalRochaMineral local = { lat_rocha, long_rocha };
    RochaMineral rocha_file;

    //inicializa a rocha e insere no compartimento
    inicializaRochaMineral(&rocha_file, contId, peso_rocha , lista_minerais,local);
    inserir_rocha(Compartimento,&rocha_file);
}

//funcao que imprime o compartimento ordenado e informações dessa ordenacao
void imprime_saida(Compartimento * compartimento,int comparacoes,int movimentacoes, double tempo, char algoritmo[]){
    imprime_compartimento(compartimento);
    printf("\n");
    printf("Comparacoes: %d\nMovimentacoes: %d\nTempo de execucao: %lfs\nAlgoritimo: %s\n", comparacoes,movimentacoes,tempo,algoritmo);
    printf("\n");

}