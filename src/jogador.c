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

	int atributos[NUM_ATRIBUTOS];
    int pontos_livres;
    int itens[NUM_ITENS];

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
	// atributos 
    for (i = 0; i < NUM_ATRIBUTOS; i++) j->atributos[i] = 0;
    for (i = 0; i < NUM_ITENS; i++) j->itens[i] = ITENS_INICIAIS;
    j->pontos_livres = PONTOS_INICIAIS;

    aplicar_atributos(j);
    return j;
}

int vida_rest(Jogador* j){

    if (!j) {
        printf("ERROR: acao invalida!.\n");
        return -1; 
    }

    return j->vida;

}

int buscar_estamina(Jogador* j){

    if (!j) {
        printf("ERROR: acao invalida!.\n");
        return -1; 
    }

    return j->estamina;
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
		free(barra_v);
        free(barra_e);
        return;
    }
    printf("%s%sJogador %s%s:  \nVIDA:     %s\nESTAMINA: %s\n", 
	BG_BRANCO,
	TXT_PRETO,
	j->nome,
	RESET,
	criar_barra(BG_VERDE, j->vida, barra_v, j->vida_total),
	criar_barra(BG_AZUL, j->estamina, barra_e, j->estamina_total));
	printf("ATQ: %d | DEF: %d | PODER: %d\n",
    j->atributos[ATR_ATAQUE], j->atributos[ATR_DEFESA], j->atributos[ATR_PODER]);


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

/* ===== ATRIBUTOS ===== */

int buscar_atributo(Jogador* j, Atributo a){
    if (!j || a < 0 || a >= NUM_ATRIBUTOS) return -1;
    return j->atributos[a];
}

int buscar_pontos_livres(Jogador* j){
    if (!j) return -1;
    return j->pontos_livres;
}

int adicionar_pontos(Jogador* j, Atributo a, int qtd){
    if (!j || a < 0 || a >= NUM_ATRIBUTOS || qtd <= 0 || qtd > j->pontos_livres) return 0;
    j->atributos[a] += qtd;
    j->pontos_livres -= qtd;
    return 1;
}

void aplicar_atributos(Jogador* j){
    if (!j) return;
    j->vida_total = VIDA_BASE + j->atributos[ATR_VIDA] * VIDA_POR_PONTO;
    j->vida = j->vida_total;
    j->estamina_total = ESTAMINA_BASE + j->atributos[ATR_ESTAMINA] * ESTAMINA_POR_PONTO;
    j->estamina = j->estamina_total;
}

/* ===== INVENTARIO ===== */

int buscar_qtd_item(Jogador* j, TipoItem t){
    if (!j || t < 0 || t >= NUM_ITENS) return -1;
    return j->itens[t];
}

/* Retorna: >0 efeito aplicado | 0 item indisponivel | -1 vida ja cheia */
int usar_item(Jogador* j, TipoItem t){
    int efeito;
    if (!j || t < 0 || t >= NUM_ITENS || j->itens[t] <= 0) return 0;

    switch (t) {
        case ITEM_VIDA:
            if (j->vida >= j->vida_total) return -1;
            efeito = j->vida_total * (CURA_MIN_PCT + rand() % (CURA_MAX_PCT - CURA_MIN_PCT + 1)) / 100;
            if (j->vida + efeito > j->vida_total) efeito = j->vida_total - j->vida;
            j->vida += efeito;
            break;
        case ITEM_ATAQUE:
            efeito = BONUS_POCAO;
            j->atributos[ATR_ATAQUE] += efeito;
            break;
        case ITEM_DEFESA:
            efeito = BONUS_POCAO;
            j->atributos[ATR_DEFESA] += efeito;
            break;
        default:
            return 0;
    }
    j->itens[t]--;
    return efeito;
}


