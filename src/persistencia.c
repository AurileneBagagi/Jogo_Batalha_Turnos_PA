#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/persistencia.h"

//caso haja necessidade de alterar o path
#define PATH "data/jogador.csv" 
#define PATH_TEMP "data/temp.csv"

struct Arquivo {

    FILE *arq;

};

static void verifica(){

    FILE *arq = fopen(PATH, "r");

    if (arq == NULL){
        arq = fopen(PATH, "w");

        if (arq != NULL){
            fclose(arq);
        }
    } else {
        fclose(arq);
    }
}

Arquivo* abrir(){

    verifica();

    Arquivo *arq = (Arquivo*) malloc(sizeof(Arquivo));
    if(!arq) {
        printf("ERROR: não foi possível abrir o arquivo");
        return NULL;
    }

    arq->arq = fopen(PATH, "r+");
    if (arq->arq == NULL){
        free(arq);
        return NULL;
    }
    return arq;

}

ListaEstatisticas* ler_estatisticas(Arquivo* a){
    if (!a || !a->arq) {
        printf("ERROR: Arquivo invalido ou nao aberto.\n");
        return NULL;
    }

    ListaEstatisticas *estatisticas = criar_estatisticas();
    if (!estatisticas) return NULL;

    rewind(a->arq);
    char linha[256];
    EstatisticaJogador estatistica;

    while (fgets(linha, sizeof(linha), a->arq) != NULL){
        if (sscanf(linha, "%49[^;];%d;%d",
                   estatistica.nome,
                   &estatistica.vitorias,
                   &estatistica.derrotas) == 3
            && !adicionar_estatistica(estatisticas, &estatistica)){
            destruir_estatisticas(estatisticas);
            return NULL;
        }
    }

    if (ferror(a->arq)){
        printf("ERROR: falha ao ler arquivo.\n");
        destruir_estatisticas(estatisticas);
        return NULL;
    }

    return estatisticas;
}

static int inserir_jogador(Arquivo *a, const char* n, int g, int p){
    
    if (!a || !a->arq || !n) {
        printf("ERROR: parametros invalidos!\n");
        return 0;
    }

    if (fseek(a->arq, 0, SEEK_END) != 0) {
        printf("ERROR: acao invalida!\n");
        return 0;
    }

    int x = fprintf(a->arq, "%s;%d;%d\n", n, g, p);

    if (x < 0){
        printf("ERROR: acao invalida!\n");
        return 0;
    }

    fflush(a->arq);

    return 1;
    
}

static void atualizar_resultado(int *vitoria, int *derrota, ResultadoPartida resultado){

    switch (resultado){
        case RESULTADO_VITORIA:
            *vitoria+=1;
            break;
        case RESULTADO_DERROTA:
            *derrota+=1;
            break;
        
        default:
            printf("ERROR: parametro invalido!");
            break;
    }
}

int salvar_resultados(Arquivo *a, const char* n, ResultadoPartida resultado){

    if (!a || !n ) {
        printf("ERROR: parametros invalidos!\n");
        return 0;
    }

    //boas práticas: perguntar ao professor depois se é válido.
    if (a->arq != NULL) {
        fclose(a->arq);
        a->arq = NULL;
    }

    FILE *velho = fopen(PATH, "r");
    FILE *temp = fopen(PATH_TEMP, "w");

    if (!velho || !temp) {
        if (velho) fclose(velho);
        if (temp)   fclose(temp);
        
        // retornar, não usei a outra função abrir() para evitar ponteiro desnecessario
        a->arq = fopen(PATH, "r+");
        return 0;
    }

    char linha[256];
    char nome[50];
    int ganho, percas;
    int x = 0;

    while (fgets(linha, sizeof(linha), velho) != NULL){

      if (sscanf(linha, "%49[^;];%d;%d", nome, &ganho, &percas) == 3){
        
        if(strcmp(n, nome) == 0){

            atualizar_resultado(&ganho, &percas, resultado);
           
            fprintf(temp, "%s;%d;%d\n", nome, ganho, percas);
            
            x = 1;
            continue;
        }
      }

      fputs(linha, temp);
    }

    fclose(velho);
    fclose(temp);

    if (x) {
        remove(PATH);
        rename(PATH_TEMP, PATH);
    } else {
        remove(PATH_TEMP);
    }

    a->arq = fopen(PATH, "r+");

    if (x == 0){
        ganho = 0, percas = 0;
        atualizar_resultado(&ganho, &percas, resultado);
        x = inserir_jogador(a, n, ganho, percas);
    }

    return x;

}


void fechar(Arquivo* a){

   if (!a) {
        printf("ERROR: acao invalida!.\n");
        return; 
    }

    if (a->arq != NULL){
        fclose(a->arq);
    }

    free(a);

}




