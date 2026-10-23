#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/jogador.h"
#include "../include/cores.h"
#define ESTAMINA_BASE 25
#define VIDA_BASE 100

struct Jogador {
    //int id;
    char nome[50];

    int vida;
    int vida_total;
    int estamina;
    int estamina_total;

};

Jogador* criar(char *nome){
    Jogador* j = (Jogador*) malloc(sizeof(struct Jogador));

    if(!j) {
        printf("ERROR: não foi possível criar jogador! Tente novamente");
        return NULL;
    }

    //j->id = id;
    strcpy(j->nome, nome);

    j->estamina = ESTAMINA_BASE;
    j->estamina_total = ESTAMINA_BASE;
    j->vida = VIDA_BASE;
    j->vida_total = VIDA_BASE;

    return j;
}

int vida_rest(Jogador* j){

    if (!j) {
        printf("ERROR: acao invalida!.\n");
        return -1; 
    }

    return j->vida;

}

int receber_dano(Jogador* j, int dano){

    if (!j) {
        printf("ERROR: acao invalida!.\n");
        return -1; 
    }

    if (j->vida < dano){
        j->vida = 0;
        return j->vida;

    } else {
        j->vida-=dano;
        return j->vida;
    }

}

int alterar_estamina(Jogador* j, int perca){

    if (!j) {
        printf("ERROR: acao invalida!.\n");
        return -1; 
    }

    if (j->estamina >= perca){
        j->estamina-=perca;
        return j->estamina;

    } else {
        printf("Recurso insuficiente!\n");
        return -1; 
    }

}

void buscar_atributos(Jogador* j){
	
    int tamanho_vida = (j->vida * 13) + (j->vida_total - j->vida) + 20;
    int tamanho_estamina = (j->estamina * 13) + (j->estamina_total - j->estamina) + 20;

    char* barra_v = (char*) malloc(tamanho_vida * sizeof(char));
    char* barra_e = (char*) malloc(tamanho_estamina * sizeof(char));

    if (barra_v == NULL || barra_e == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return;
    }
    printf("%s%sJogador %s%s:  \nVIDA:     %s\nESTAMINA: %s\n", 
	BG_BRANCO,
	TXT_PRETO,
	j->nome,
	RESET,
	criar_barra(BG_VERDE, j->vida, barra_v, j->vida_total),
	criar_barra(BG_AZUL, j->estamina, barra_e, j->estamina_total));

    free(barra_v);
    free(barra_e);
}

char* criar_barra(char* cor, int quantidade, char *barra, int total) {
    int i = 0;
    int j, c, r;
    char* reset = "\033[0m";
    
    for(j = 0; j < quantidade && j <= total; j++) {
        for(c = 0; cor[c] != '\0'; c++) {
            barra[i++] = cor[c];
        }
        barra[i++] = ' '; 
        for(r = 0; reset[r] != '\0'; r++) {
            barra[i++] = reset[r];
        }
    }
    
    for(; j < total; j++) {
        barra[i++] = '/';
    }
    barra[i] = '\0'; 
    
    return barra;
}

const char* buscar_nome(Jogador* j){

    if (!j) {
        printf("ERROR: acao invalida!.\n");
        return NULL; 
    }

    return j->nome;
}

void destruir(Jogador* j){

    if (j) free(j);

}



