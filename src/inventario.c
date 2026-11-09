#include <stdio.h>
#include <stdlib.h>

#include "../include/inventario.h"
#include "../include/itens.h"

typedef struct Slot Slot;

struct Slot {
    int id_do_item;
    int quantidade;
};

struct Inventario {
    Slot *slots;
    int qtd;
    int cap;
};

static const char *NOMES_ITENS[] = {
    "Pocao de Vida Pequena",
    "Pocao de Vida Media",
    "Pocao de Vida Grande",
    "Pocao de Estamina Pequena",
    "Pocao de Estamina Media",
    "Pocao de Estamina Grande",
    "Espada",
    "Cajado",
    "Escudo"
};

static int total_itens(){
    return (int)(sizeof(NOMES_ITENS) / sizeof(NOMES_ITENS[0]));
}

const char* nome_item(int id){
    if (id < 1 || id > total_itens()) return "Desconhecido";
    return NOMES_ITENS[id - 1];
}

Inventario* criar_inventario(){

    Inventario *inv = (Inventario*) malloc(sizeof(Inventario));

    if (!inv){
        printf("ERROR: nao foi possivel criar inventario!\n");
        return NULL;
    }

    inv->slots = NULL;
    inv->qtd = 0;
    inv->cap = 0;

    return inv;
}

void destruir_inventario(Inventario *inv){

    if (!inv) return;

    free(inv->slots);
    free(inv);
}

int adicionar_item(Inventario *inv, int id, int qtd){

    int i;
    int nova_cap;
    Slot *tmp;

    if (!inv || id < 1 || id > total_itens() || qtd <= 0) return 0;

    for (i = 0; i < inv->qtd; i++){
        if (inv->slots[i].id_do_item == id){
            inv->slots[i].quantidade += qtd;
            return 1;
        }
    }

    if (inv->qtd == inv->cap){
        nova_cap = (inv->cap == 0) ? 4 : inv->cap * 2;
        tmp = realloc(inv->slots, nova_cap * sizeof(Slot));

        if (!tmp){
            printf("ERROR: memoria insuficiente!\n");
            return 0;
        }

        inv->slots = tmp;
        inv->cap = nova_cap;
    }

    inv->slots[inv->qtd].id_do_item = id;
    inv->slots[inv->qtd].quantidade = qtd;
    inv->qtd++;

    return 1;
}

int remover_item(Inventario *inv, int id, int qtd){

    int i;
    int j;

    if (!inv || id < 1 || qtd <= 0) return 0;

    for (i = 0; i < inv->qtd; i++){

        if (inv->slots[i].id_do_item != id) continue;

        if (inv->slots[i].quantidade > qtd){
            inv->slots[i].quantidade -= qtd;
            return 1;
        }

        for (j = i; j < inv->qtd - 1; j++){
            inv->slots[j] = inv->slots[j + 1];
        }

        inv->qtd--;
        return 1;
    }

    return 0;
}

int consultar_item(Inventario *inv, int id){

    int i;

    if (!inv) return 0;

    for (i = 0; i < inv->qtd; i++){
        if (inv->slots[i].id_do_item == id){
            return inv->slots[i].quantidade;
        }
    }

    return 0;
}

void listar_inventario(Inventario *inv){

    int i;

    if (!inv) return;

    printf("-------- INVENTARIO --------\n");

    if (inv->qtd == 0){
        printf("(vazio)\n");
        printf("----------------------------\n");
        return;
    }

    for (i = 0; i < inv->qtd; i++){
        printf("[%d] %-22s x%d\n",
               i + 1,
               nome_item(inv->slots[i].id_do_item),
               inv->slots[i].quantidade);
    }

    printf("----------------------------\n");
}

int tamanho_inventario(Inventario *inv){
    if (!inv) return 0;
    return inv->qtd;
}

int id_em(Inventario *inv, int pos){
    if (!inv || pos < 0 || pos >= inv->qtd) return -1;
    return inv->slots[pos].id_do_item;
}

int quantidade_em(Inventario *inv, int pos){
    if (!inv || pos < 0 || pos >= inv->qtd) return 0;
    return inv->slots[pos].quantidade;
}
