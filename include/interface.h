#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogador.h"

void iniciar_jogo();
void turnos(Jogador* a, Jogador* b);

void atributos(Jogador* a, Jogador* b);  /* apagar*/ 
void acoes_text(Jogador* j);
int resultado(Jogador* j);

int dano(Jogador* j, int min, int max);
void limpar_tela();
void distribuir_pontos(Jogador* j);  /* apagar*/ 
void pocao(Jogador* j);

#endif 
