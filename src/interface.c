#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/interface.h"
#include "../include/cores.h"

void iniciar_jogo(){

    printf("==============================\n");
    printf("     BEM VINDOS(AS) AO     \n");
    printf("JOGO DE BATALHA DE TURNOS!\n");
    printf("==============================\n\n");

}

void atributos(Jogador* a, Jogador* b){
    printf("\n---------------------\n");
    buscar_atributos(a);
    printf("-----------------------\n");
    printf("\n---------------------\n");
    buscar_atributos(b);
    printf("---------------------\n");

}

void acoes_text(Jogador* j){
    printf("\n--------ACOES-----------\n\n");
    printf("Escolha sua acao Jogador \"%s\":\n", buscar_nome(j));
    printf("[1] Atacar (Dano: 10-15)\n");
    printf("[2] Habilidade (Dano: 15-20, Custo: 10 estamina)\n");
    printf("[3] Pocao de Cura | Qtd: %d\n", buscar_pocoes(j));
    printf("Digite um numero: ");
}

int dano(Jogador* j, int min, int max){
    (void)j;
    int d = (rand() % (max - min + 1)) + min;
    limpar_tela();
    printf ("%sO jogador \"%s\" deu %d de dano\n%s",TXT_VERMELHO_B, buscar_nome(j), d, RESET);
    return d;
}

int resultado(Jogador* j){
    printf("\n------------------------------\n");
    printf("Parabens! %s\n", buscar_nome(j));
    printf("==============================\n");

    return 1;
}

void turnos(Jogador* a, Jogador* b){
        int acao = 0;

        acoes_text(a);

        if (scanf("%d", &acao) != 1) {
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
            }
            acao = 0; 
        }

        if (acao == 1){
            receber_dano(b, dano(a, 10, 15));
        } else if (acao == 2 && buscar_estamina(a) > 0){
            receber_dano(b, dano(a, 15, 20));
            alterar_estamina(a, 5);
        } else if (acao == 3){
            usar_pocao(a);
        } else {
            limpar_tela();
            printf("Ação invalida! Jogador \"%s\" perdeu o turno!\n", buscar_nome(a));
        }
}

void limpar_tela() {
    printf("\033[H\033[2J\033[3J");
    fflush(stdout); 
}





