#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct Jogador Jogador;

Jogador* criar(char *nome);

//void adiciona_personagem();
int vida_rest(Jogador* j);
int receber_dano(Jogador* j, int dano);
int alterar_estamina(Jogador* j, int dano);
//void alterar_mochila(Jogador* j, int item);
void buscar_atributos(Jogador* j);
void destruir(Jogador* j);
const char* buscar_nome(Jogador* j);

#endif 