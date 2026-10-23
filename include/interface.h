#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogador.h"

void iniciar_jogo();
void turnos(Jogador* a, Jogador* b, int x);
//void reloading_tela();
void atributos(Jogador* a, Jogador* b);
void acoes_text(int x);
int resultado(Jogador* j);
//void salvar();
int dano(Jogador* j, int min, int max);
void limpar_tela();

#endif 
