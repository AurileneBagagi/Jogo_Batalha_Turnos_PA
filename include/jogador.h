
#ifndef JOGADOR_H
#define JOGADOR_H

#define PONTOS_INICIAIS 10

typedef struct Jogador Jogador;

Jogador* criar(char *nome);

//void adiciona_personagem();
int vida_rest(Jogador* j);
int buscar_estamina(Jogador* j);
int receber_dano(Jogador* j, int dano);
int alterar_estamina(Jogador* j, int dano);

//void alterar_mochila(Jogador* j, int item);
void buscar_atributos(Jogador* j);
void destruir(Jogador* j);
const char* buscar_nome(Jogador* j);
char* criar_barra(char* cor, int quantidade, char *barra, int total);

/* Pocao de Cura */
int usar_pocao(Jogador* j);
int buscar_pocoes(Jogador* j);



#endif
