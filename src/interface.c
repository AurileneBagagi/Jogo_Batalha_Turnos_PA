#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/interface.h"

void iniciar_jogo(){

    printf("==============================\n");
    printf("     BEM VINDOS(AS) AO     \n");
    printf("JOGO DE BATALHA DE TURNOS!\n");
    printf("==============================\n\n");

}

void atributos(Jogador* a, Jogador* b){
	limpar_tela();
    printf("\n---------------------\n");
    buscar_atributos(a);
    printf("------------------------------\n");
    printf("\n---------------------\n");
    buscar_atributos(b);
    printf("---------------------\n");

}

void acoes_text(int x){
    printf("\n--------AÇOES-----------\n\n");
    printf("Escolha sua acao Jogador %d:\n", x);
    printf("[1] Atacar (Dano: 10-15)\n");
    printf("[2] Habilidade personagem (Custo: 10xp)\n");
    printf("[3] Usar Itens \n");
    printf("Digite um número: ");
}

//pode separar em outra interface de ações;
int dano(Jogador* j, int min, int max){
    int dano = (rand() % (max - min + 1)) + min;

    printf ("O inimigo recebeu %d de dano\n", dano);

    return dano;

}

int resultado(Jogador* j){
    printf("\n------------------------------\n");
    printf("Parabens! %s\n", buscar_nome(j));
    printf("==============================\n");
}
//pode separar em outra interface de ações;
void turnos(Jogador* a, Jogador* b, int x){
        int acao;

        acoes_text(x);

        scanf("%d", &acao);

        if (acao == 1){
            receber_dano(b, dano(a, 10, 15));
        } else if (acao == 2){
            receber_dano(b, dano(a, 15, 20));
            alterar_estamina(a, 5);
        }

}

void limpar_tela() {
    printf("\033[H\033[2J\033[3J");
    fflush(stdout); 
}





