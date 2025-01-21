#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Compartimento\Compartimento.h"

//Cabecalho das funcoes
FILE *leitura_arq(int argc, char **argv);

void case_R_file(FILE * file, ListaMinerais * lista_minerais_file);
void operacao_R(float lat_rocha, float long_rocha, float peso_rocha, ListaMinerais* lista_minerais);
void imprime_saida(Compartimento * compartimento,int comparacoes,int movimentacoes, double tempo, char algoritmo[]);

int main(int argc, char **argv){
    if (leitura_arq(argc,argv) != 0){
        FILE *file = leitura_arq(argc,argv);
        if (file == NULL){//verifica se o arquivo tem algo a ser lido
            printf("Arquivo de entrada Invalido");
            return 0;
        }
        int comparacoes1,comparacoes2, movimentacoes1, movimentacoes2;
        clock_t inicio, fim;
        double tempo1,tempo2;
        Compartimento compartimento_1;
        Compartimento compartimento_2;
        //le o numero de rochas
        int N_rochas = 0;
        fscanf(file,"%d",&N_rochas); fgetc(file);

        //executa a leitura das N_rochas
        for(int i=0;i<N_rochas;i++){
            ListaMinerais lista_minerais_file;
            fListaMineraisVazia(&lista_minerais_file);
            case_R_file(file, &lista_minerais_file);
        }
        compartimento_2 = compartimento_1;

        inicio = clock();
        insert_sort(&compartimento_1,&comparacoes1,&movimentacoes1);
        fim = clock();
        tempo1 = (double)(fim-inicio)/CLOCKS_PER_SEC;

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
        return 0;
    }
}

//inicia a leitura dos dados para a operacao R, dispostos em uma linha do arquivo
void case_R_file(FILE * file, ListaMinerais * lista_minerais_file){
    char linha[255];
    char *buffer = NULL;
    const char delim[2] = " ";
    float lat_rocha = 0, long_rocha = 0, peso_rocha = 0;
    fgets(linha,255,file);
    Mineral minerais[3];
    char nome_mineral[15];
    linha[strlen(linha) - 1] = '\0';//captura a linha logo após a instrucao R

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
//chamada da operacao R, que tem como parametro os dados da rocha
operacao_R(lat_rocha, long_rocha, peso_rocha, lista_minerais_file);
}


//Operacao responsavel por coletar uma nova rocha
void operacao_R(float lat_rocha, float long_rocha, float peso_rocha, ListaMinerais* lista_minerais){
    static int contId = 1;

    LocalRochaMineral local = { lat_rocha, long_rocha };
    RochaMineral rocha_file;

    //inicializa a rocha a ser coletada
    inicializaRochaMineral(&rocha_file, contId, peso_rocha , lista_minerais,local);

}


void imprime_saida(Compartimento * compartimento,int comparacoes,int movimentacoes, double tempo, char algoritmo[]){
    imprime_compartimento(compartimento);
    printf("\n");
    printf("Comparacoes: %d\nMovimentacoes: %d\nTempo de execucao: %fs\nAlgoritimo: %s", comparacoes,movimentacoes,tempo,algoritmo);

}