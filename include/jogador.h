#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct Jogador Jogador;

Jogador* criar(char *nome, int g, int p);

int vida_rest(Jogador* j);
int buscar_estamina(Jogador* j);
int receber_dano(Jogador* j, int dano);
int alterar_estamina(Jogador* j, int dano);
int buscar_ganhos(Jogador* j);
int buscar_percas(Jogador* j);


void buscar_atributos(Jogador* j);
void destruir(Jogador* j);

const char* buscar_nome(Jogador* j);
char* criar_barra(char* cor, int quantidade, char *barra, int total);

#endif 
