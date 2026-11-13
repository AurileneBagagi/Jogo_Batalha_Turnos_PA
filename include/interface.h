#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogador.h"
#include "estatisticas.h"

void bem_vindo();
void turnos(Jogador* a, Jogador* b);

void acoes_texto(Jogador* j);

int resultado_partida(Jogador* j);
int receber_nome(char *destino, int x);

void mostrar_historico(const ListaEstatisticas *estatisticas);
void mostrar_ranking(const ListaEstatisticas *estatisticas, int limite);

int dano(Jogador* j, int min, int max);
void limpar_tela();
void pocao(Jogador* j);

#endif 
