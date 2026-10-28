
#ifndef JOGADOR_H
#define JOGADOR_H

#define PONTOS_INICIAIS 10

typedef enum { ATR_VIDA, ATR_ATAQUE, ATR_DEFESA, ATR_ESTAMINA, ATR_PODER, NUM_ATRIBUTOS } Atributo;
typedef enum { ITEM_VIDA, ITEM_ATAQUE, ITEM_DEFESA, NUM_ITENS } TipoItem;

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

/* Atributos */
int buscar_atributo(Jogador* j, Atributo a);
int buscar_pontos_livres(Jogador* j);
int adicionar_pontos(Jogador* j, Atributo a, int qtd);
void aplicar_atributos(Jogador* j);

/* Inventario */
int buscar_qtd_item(Jogador* j, TipoItem t);
int usar_item(Jogador* j, TipoItem t);

#endif
