#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Sonda_espacial/Sonda_espacial.h"
#include "Lista_sondas_espaciais/Lista_sonda_espacial.h"

//Cabecalho das funcoes
FILE *leitura_arq(int argc, char **argv);
void preenche_sonda_arq(int numero_sondas, FILE * file, Lista_sonda_espacial * lista_de_sondas_file);
void preenche_sonda_terminal(int numero_de_sondas,Lista_sonda_espacial *Lista_de_sondas_terminal);
void case_R_file(FILE * file, ListaMinerais * lista_minerais_file, Lista_sonda_espacial * lista_de_sondas_file);
void case_R_arq(ListaMinerais * lista_minerais_terminal, Lista_sonda_espacial * Lista_de_sondas_terminal);
void operacao_R(Lista_sonda_espacial * lista_sondas, float lat_rocha, float long_rocha, float peso_rocha, ListaMinerais* lista_minerais);
float calcula_distancia(float x1, float y1, float x2, float y2);
void operacao_I(Lista_sonda_espacial * lista_sondas);
int operacao_E(Lista_sonda_espacial * lista_sondas);

int main(int argc, char **argv){
    if (leitura_arq(argc,argv) != 0){
        FILE *file = leitura_arq(argc,argv);
        if (file == NULL){//verifica se o arquivo tem algo a ser lido
            printf("Arquivo de entrada Invalido");
            return 0;
        }
        //cria e inicializa sonda espacial
        Lista_sonda_espacial lista_de_sondas_file;
        inicializa_lista_sonda_espacial(&lista_de_sondas_file);

        //recebe numero de sondas
        int numero_sondas = 0;
        fscanf(file, "%d", &numero_sondas); fgetc(file);
        if(numero_sondas == 0){//verifica se e numero valido
            printf("Nenhuma sonda foi enviada pela AEDS\n");
            return 0;
        }

        preenche_sonda_arq(numero_sondas, file, &lista_de_sondas_file);
        
        //le o numero de instrucoes a serem executadas
        int N_instrucao = 0;
        fscanf(file,"%d",&N_instrucao); fgetc(file);

        //executa a quantidade de instrucoes informadas
        for(int i=0;i<N_instrucao;i++){
            char instrucao;

            //le a instrucao informada
            fscanf(file,"%c", &instrucao); fgetc(file);

            //Verifica qual foi o caractere inserido e aciona o "case" correspondente
            switch (instrucao)
            {
            case 'R':{
                ListaMinerais lista_minerais_file;
                fListaMineraisVazia(&lista_minerais_file);
                case_R_file(file, &lista_minerais_file,  &lista_de_sondas_file);
                break;}
            case 'I':
                //chamada da operacao I com apenas a lista de sondas como parametro
                operacao_I(&lista_de_sondas_file);
                break;
            case 'E':
                //chamada da operacao E com apenas a lista de sondas como parametro
                operacao_E(&lista_de_sondas_file);
                break;
            default:
                //caso seja fornecido alguma operacao invalida, ele desconsidera a operacao e apssa para a proxima
                printf("operacao invalida\n");
                break;
            }
        }
    }
    else{//caso nenhum parametro valido tenha sido passado, o fluxo eh desviado para a leitura por terminal
        printf("Iniciando missao espacial\n");
        int numero_de_sondas = 0;
        Lista_sonda_espacial Lista_de_sondas_terminal; //cria lista de sondas
        inicializa_lista_sonda_espacial(&Lista_de_sondas_terminal);//inicializa lista de sondas
        printf("Digite o numero de sondas enviada pela AEDS: \n");
        scanf("%d", &numero_de_sondas); //recebe o numero de sondas
        
        if(numero_de_sondas == 0){//verifica se o numero de sondas informado e valido
            printf("Nenhuma sonda foi enviada pela AEDS\n");
            return 0;
        }
        
        preenche_sonda_terminal(numero_de_sondas, &Lista_de_sondas_terminal);
        
        int N_instrucao_terminal = 0; 
        printf("Digite o numero de operacoes que as sondas realizarao: \n");
        scanf("%d", &N_instrucao_terminal); //le o numero de instrucoes a serem executadas
        //executa a quantidade de instrucoes informadas
        for(int i = 0; i<N_instrucao_terminal; i++){ 
            char instrucao_terminal;
            printf("Insira a operacao %d: \n", i+1);
            getc(stdin);
             //le a instrucao informada
            scanf("%c", &instrucao_terminal);
            
            //Verifica qual foi o caractere inserido e aciona o "case" correspondente
            switch (instrucao_terminal)
            {
            case 'R':
                //inicia a leitura dos dados para a operacao R
                {
                ListaMinerais lista_minerais_terminal;
                fListaMineraisVazia(&lista_minerais_terminal);
                case_R_arq(&lista_minerais_terminal,&Lista_de_sondas_terminal);
                break;}

            case 'I':
                //chamada da operacao I com apenas a lista de sondas como parametro
                operacao_I(&Lista_de_sondas_terminal);
                break;

            case 'E':
                //chamada da operacao E com apenas a lista de sondas como parametro
                operacao_E(&Lista_de_sondas_terminal);
                break;

            default:
                //caso seja inserido alguma operacao invalida, ele desconsidera a operacao e apssa para a proxima
                printf("operacao invalida\n");
                break;
            }
        }
        
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

//percorre as sondas criadas, preenchendo com os valores do arquivo e inserindo em uma lista de sondas
void preenche_sonda_arq(int numero_sondas, FILE * file, Lista_sonda_espacial * lista_de_sondas_file){
    for (int i = 0; i < numero_sondas; i++){
            char id[20];
            sprintf(id, "%d", i+1);
            Sonda_espacial sonda;
            float lat_i,long_i,capacidade_i,velocidade_i,combustivel_i;
            
            fscanf(file, "%f %f %f %f %f", &lat_i,&long_i,&capacidade_i,&velocidade_i,&combustivel_i);
            fgetc(file);

            inicializa_Sonda_Espacial(&sonda, id, lat_i,long_i,capacidade_i,velocidade_i,combustivel_i);
            insere_item_lista_sonda_espacial(lista_de_sondas_file,&sonda);
        }
}

//inicia a leitura dos dados para a operacao R, dispostos em uma linha do arquivo
void case_R_file(FILE * file, ListaMinerais * lista_minerais_file, Lista_sonda_espacial * lista_de_sondas_file){
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
//chamada da operacao R, que tem como parametro a lista de sondas e os dados da rocha
operacao_R(lista_de_sondas_file,lat_rocha, long_rocha, peso_rocha, lista_minerais_file);
}

//percorre as sondas criadas, preenchendo com os valores lidos e inserindo em uma lista de sondas
void preenche_sonda_terminal(int numero_de_sondas,Lista_sonda_espacial *Lista_de_sondas_terminal){
    for(int i = 0; i<numero_de_sondas; i++){; 
    char id[20];
    sprintf(id, "%d", i+1);//converte inteiro para char
    Sonda_espacial sonda;
    float lat_i = 0,long_i = 0,capacidade_i = 0,velocidade_i = 0,combustivel_i = 0;
    printf("Digite a latitude, longitude, capacidade, velocidade e combustivel da sonda %s (ex: -2 10 50 12 100): \n", id);
    scanf("%f %f %f %f %f", &lat_i,&long_i,&capacidade_i,&velocidade_i,&combustivel_i);
    inicializa_Sonda_Espacial(&sonda,id,lat_i,long_i,capacidade_i,velocidade_i,combustivel_i);//inicializa as sondas com as variaveis recebidas
    insere_item_lista_sonda_espacial(Lista_de_sondas_terminal,&sonda);
    }
}

//inicia a leitura dos dados partir do terminal para a operacao R
void case_R_arq(ListaMinerais * lista_minerais_terminal, Lista_sonda_espacial * Lista_de_sondas_terminal){
    char linha_terminal[255];

    printf("Digite a latitude, longitude, peso, categoria e os minerais da rocha (ex: -4.6 137.5 20 Ferrolita Aquavitae): \n");
    getchar();

    //captura a linha fornecida
    scanf("%[^\n]", linha_terminal);
    
    char * buffer = NULL;
    const char delim[2] = " ";
    /*secciona a linha capturada a partir do padrao definido no delim ou seja, 
    separa os 3 primeiros tokens entre espaco e atribui para sua variavel correspondente.*/
    buffer = strtok(linha_terminal,delim);
    float lat_rocha_terminal =  atof (buffer);
    buffer = strtok(NULL,delim);
    float long_rocha_terminal = atof(buffer);
    buffer = strtok(NULL,delim);
    float peso_rocha_terminal = atof (buffer);
    char aux[20];
    
    Mineral minerais_terminal[2];


    int m = 0;

    /*conclui a leitura da linha lendo os ultimos tokens e inserindo na lista. Esses tokens varia de 1 a 3, 
    por isso a verificacao que encerra o while ao chegar em um valor NULL*/
    while((buffer = strtok(NULL, delim)) != NULL){
        strcpy(aux,buffer);
        atribui_mineral(&minerais_terminal[m],aux);
        TItem x = {minerais_terminal[m]};
        insereMineralLista(lista_minerais_terminal, x);
        m++;
    }
    //chamada da operacao R, que tem como parametro a lista de sondas e os dados da rocha
    operacao_R(Lista_de_sondas_terminal,lat_rocha_terminal,long_rocha_terminal,peso_rocha_terminal,lista_minerais_terminal);
}


//Operacao responsavel por coletar uma nova rocha
void operacao_R(Lista_sonda_espacial * lista_sondas, float lat_rocha, float long_rocha, float peso_rocha, ListaMinerais* lista_minerais){
    static int contId = 1;

    LocalRochaMineral local = { lat_rocha, long_rocha };
    RochaMineral rocha_file;

    //inicializa a rocha a ser coletada
    inicializaRochaMineral(&rocha_file, contId, peso_rocha , lista_minerais,local,"00:00:00");

    int cont = lista_sondas->QntItens;
    float menor_d = INFINITY;
    float distancia = 0;

    Celula* sonda_mais_perto = NULL;
    Celula* aux = lista_sondas->pPrimeiro->pProx;

    if (!aux) return;
    //inicia o processo de percerrer todas as sondas e verificar se atende aos requisitos para coletar a rocha
    for (int i = 0;i< cont; i++) {
        distancia = calcula_distancia(aux->item_sonda.Localizacao_sonda.Longitude,aux->item_sonda.Localizacao_sonda.Latitude, long_rocha, lat_rocha);
        //verifica a primeira condicao para coletar uma rocha: ser a sonda mais perto
        if (distancia < menor_d){//se a sonda em questao for a mais perto no momento, verifica o segundo requisito
            if(trocar_rocha(&aux->item_sonda.Compartimento, &rocha_file) == 1){//Ja ter uma rocha da mesma categoria mais pesada
                menor_d = distancia;
                sonda_mais_perto = aux;
                move_Sonda_Espacial(&sonda_mais_perto->item_sonda,lat_rocha,long_rocha);
                return;
            }else if ((aux->item_sonda.Compartimento.peso_atual + rocha_file.peso) <= aux->item_sonda.Compartimento.peso_maximo){//ou ter capacidade de armazenar a rocha
                menor_d = distancia;
                sonda_mais_perto = aux;
            }
        }
        aux = aux->pProx;


    }
    if(sonda_mais_perto == NULL) return;
    //se nenhuma sonda contem a rocha, a sonda mais perto encontrada ira mover-se ate a rocha e coleta-la
    move_Sonda_Espacial(&sonda_mais_perto->item_sonda,lat_rocha,long_rocha);
    inserir_rocha(&sonda_mais_perto->item_sonda.Compartimento, &rocha_file);
    contId++;
}

//recebe como parametro as coordenadas x e y da sonda e da rocha e retorna o valor da distancia euclidiana
float calcula_distancia(float x1, float y1, float x2, float y2){
    return (sqrt(pow((x1 - x2),2) + pow((y1 - y2),2)));
}

//Operacao que imprime as rochas insertidas nas sondas
void operacao_I(Lista_sonda_espacial * lista_sondas){

    int cont_sondas  = lista_sondas->QntItens;
    Celula* aux = lista_sondas->pPrimeiro->pProx;
    //percorre toda a lista de sodas e imprime o compartimento
    for (int i = 0;i < cont_sondas; i++){
        printf("%s\n", aux->item_sonda.Identificador);

        imprime_compartimento(&aux->item_sonda.Compartimento);
        aux = aux->pProx;
    }
}

//operacao responsavel por realizar a redistribuicao das rochas entre as sondas
int operacao_E(Lista_sonda_espacial * lista_sondas){
    if (verifica_lista_vazia(lista_sondas)){//verifica se existem rochas a serem redistribuídas
        return 0;
    }

    int cont_sondas = lista_sondas->QntItens;
    int quantidade_de_rochas = 0;
    Celula *aux = lista_sondas->pPrimeiro->pProx;
    
    //move todas as sondas para a origem (ponto (0,0)) e conta quantas rochas foram coletadas no total
    for (int i = 0; i < cont_sondas; i++){
        move_Sonda_Espacial(&aux->item_sonda, 0 , 0);
        quantidade_de_rochas += aux->item_sonda.Compartimento.tamanho;
        aux = aux->pProx;
    }
    //cria uma lista temporaria de acordo com essa quantidade total de rochas coletadas
    RochaMineral* lista_rochas= (RochaMineral*) malloc(quantidade_de_rochas * sizeof(RochaMineral)); //faz lista de rochas para redistribuir depois
    aux = lista_sondas->pPrimeiro->pProx;
    Ccelula* comp_aux = NULL;
    Ccelula* apontador = NULL;
    int indice = 0;
    //percorre toda a lista de sondas esvaziando os seus compartimentos e armazenando as rochas em um vetor de rochas temporario
    for (int counter = 0; counter < cont_sondas; counter++){
        apontador = aux->item_sonda.Compartimento.primeiro->prox;
        
        while (apontador != NULL) { // percorre todas as rochas do compartimento de cada sonda, removendo-as e adicionando no vetor
            RochaMineral rocha_retirada;
            comp_aux = apontador;
            apontador = apontador->prox;
            remover_rocha(&aux->item_sonda.Compartimento, comp_aux->rocha.categoria, &rocha_retirada);
            lista_rochas[indice++] = rocha_retirada;
        }

        aux = aux->pProx;
    }
    
    //ordena o vetor de forma decrescente a partir do peso das rochas 
    for (int i = 0; i < quantidade_de_rochas; i++){ 
        for (int j = i; j < quantidade_de_rochas; j++){
            if (lista_rochas[i].peso<lista_rochas[j].peso){
                RochaMineral auxiliar = lista_rochas[i]; 
                lista_rochas[i] = lista_rochas[j];
                lista_rochas[j] = auxiliar;
            }
        }
    }
    //distribui as rochas nas sondas, sempre priorizando a sonda com menor carga atual e com capacidade para armazenar a rocha
    for (int i = 0; i < quantidade_de_rochas; i++){ 
        aux = lista_sondas->pPrimeiro->pProx;
        Celula* menor = lista_sondas->pPrimeiro->pProx;
        for (int j = 0 ; j < lista_sondas->QntItens ; j++){//descobre qual a sonda com o menor peso atual

            if (aux->item_sonda.Compartimento.peso_atual < menor->item_sonda.Compartimento.peso_atual && aux->item_sonda.Compartimento.peso_atual + lista_rochas[i].peso <= aux->item_sonda.Compartimento.peso_maximo){
                menor = aux;
            }
            
            aux = aux->pProx;
        }
        //após percorrer todas as sondas, insere a rocha na sonda adequada
        inserir_rocha(&menor->item_sonda.Compartimento, &lista_rochas[i]);
    }

    return 1;
}