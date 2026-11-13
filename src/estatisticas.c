#include <stdio.h>
#include <stdlib.h>
#include "../include/estatisticas.h"

//é um vetor dinamico

struct ListaEstatisticas {
    EstatisticaJogador *itens;
    size_t quantidade;
    size_t capacidade; // capacidade do vetor
};

ListaEstatisticas* criar_estatisticas(void){
    ListaEstatisticas *lista = malloc(sizeof(ListaEstatisticas));

    if (!lista){
        printf("ERROR: nao foi possivel criar lista de estatisticas!\n");
        return NULL;
    }

    lista->itens = NULL;
    lista->quantidade = 0;
    lista->capacidade = 0;

    return lista;
}

int adicionar_estatistica(ListaEstatisticas *lista, const EstatisticaJogador *estatistica){
    if (!lista || !estatistica) return 0;

    if (lista->quantidade == lista->capacidade){
        size_t nova_capacidade;

        if (lista->capacidade == 0) {
            nova_capacidade = 4;
        } else {
            nova_capacidade = lista->capacidade * 2;
        }

        EstatisticaJogador *temp = realloc(lista->itens, nova_capacidade * sizeof(EstatisticaJogador));

        if (!temp){
            printf("ERROR: memoria insuficiente!\n");
            return 0;
        }

        lista->itens = temp;
        lista->capacidade = nova_capacidade;
    }

    lista->itens[lista->quantidade] = *estatistica;
    lista->quantidade++;

    return 1;
}

size_t quantidade_estatisticas(const ListaEstatisticas *lista){
    if (!lista) return 0;
    return lista->quantidade;
}

const EstatisticaJogador* obter_estatistica(const ListaEstatisticas *lista, size_t indice){
    if (!lista || indice >= lista->quantidade) return NULL;
    return &lista->itens[indice];
}

void destruir_estatisticas(ListaEstatisticas *lista){
    if (!lista){
        printf("ERROR: acao invalida!.\n");
        return;

    } 

    free(lista->itens);
    free(lista);
}