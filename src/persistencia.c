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

//Aurilene: é preciso organizar ainda as chamadas de cada função.
// Implementar a atualização, se já tiver será atualizado os dados e etc....

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

void ler(Arquivo* a){

    if (!a || !a->arq) {
        printf("ERROR: Arquivo invalido ou nao aberto.\n");
        return;
    }

    rewind(a->arq);
    char linha[256];
    char nome[50];
    int ganho, percas;

    printf("=============== JOGADORES ===============\n");
    printf("NOME             | GANHOU |  PERDEU \n");

    while (fgets(linha, sizeof(linha), a->arq) != NULL){
      if (sscanf(linha, "%49[^;];%d;%d", nome, &ganho, &percas) == 3){
        printf(" %-16s| %-6d | %-6d\n", nome, ganho, percas);
      }
    }
    printf("========================================\n");
    
}

int buscar(Arquivo *a, char* n, int *g, int *p){

    if (!a || !a->arq || !n || !g || !p) {
        printf("ERROR: parametros invalidos!\n");
        return 0;
    }

    rewind(a->arq);
    char linha[256];
    char nome[50];
    int ganho, percas;

    while (fgets(linha, sizeof(linha), a->arq) != NULL){
      if (sscanf(linha, "%49[^;];%d;%d", nome, &ganho, &percas) == 3){
        
        if(strcmp(n, nome) == 0){
            *g = ganho;
            *p = percas;

            return 1;
        }
      }
    }

    return 0;

}

int inserir(Arquivo *a, const char* n, int g, int p){
    
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

void atualizar_resultado(int *g, int *p, char i){

    if (i == 'g'){
        *g += 1;
    } else if ( i == 'p'){
        *p += 1;
    } else {
        printf("ERROR: parametro invalido!");
        return;
    }
    

}

int atualizar(Arquivo *a, const char* n, int g, int p, char i){

    if (!a || !n || g < 0|| p < 0) {
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
        
        if(strcmp(n, nome) == 0 && g == ganho && p == percas){

            atualizar_resultado(&g, &p, i);
           
            fprintf(temp, "%s;%d;%d\n", nome, g, p);
            
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
        atualizar_resultado(&g, &p, i);
        inserir(a, n, g, p);
        x = 1;
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




