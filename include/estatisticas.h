
#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stddef.h>

typedef struct {
    char nome[50];
    int vitorias;
    int derrotas;
} EstatisticaJogador;

typedef struct ListaEstatisticas ListaEstatisticas;

ListaEstatisticas* criar_estatisticas(void);
void destruir_estatisticas(ListaEstatisticas *lista);
int adicionar_estatistica(ListaEstatisticas *lista,
                          const EstatisticaJogador *estatistica);
size_t quantidade_estatisticas(const ListaEstatisticas *lista);
const EstatisticaJogador* obter_estatistica(const ListaEstatisticas *lista,
                                             size_t indice);
void ordenar_estatisticas_por_vitorias(ListaEstatisticas *lista);

#endif
