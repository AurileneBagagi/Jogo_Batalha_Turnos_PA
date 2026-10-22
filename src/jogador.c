#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/jogador.h"

struct Jogador {
    //int id;
    char nome[50];

    int vida;
    int estamina;

};

Jogador* criar(char *nome){
    Jogador* j = (Jogador*) malloc(sizeof(struct Jogador));

    if(!j) {
        printf("ERROR: não foi possível criar jogador! Tente novamente");
        return NULL;
    }

    //j->id = id;
    strcpy(j->nome, nome);

    j->estamina = 15;
    j->vida = 50;

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

    printf ("Jog. %s:  VIDA: %d | ESTAMINA: %d\n", j->nome, j->vida, j->estamina);

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



