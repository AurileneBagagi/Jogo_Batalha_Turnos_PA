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

//sug. Auri: pode separar em outra interface de ações;
int dano(Jogador* alvo, int min, int max, int bonus){
    int d = (rand() % (max - min + 1)) + min + bonus;
    d -= buscar_atributo(alvo, ATR_DEFESA);
    if (d < 1) d = 1;
 // Mudei a formula para adicionar o valor do atributo a defesa, vou conferir se esta correto, pode ser que puxe a defesa dele mesmo.
    printf("%s recebeu %d de dano\n", buscar_nome(alvo), d);
    return d;
}
}

int resultado(Jogador* j){
    printf("\n------------------------------\n");
    printf("Parabens! %s\n", buscar_nome(j));
    printf("==============================\n");

    return 1;
}

void distribuir_pontos(Jogador* j){
    const char* nomes[] = { "Vida", "Ataque", "Defesa", "Estamina", "Poder" };
    int op, qtd, i;

    while (buscar_pontos_livres(j) > 0) {
        limpar_tela();
        printf("Distribua os pontos de %s\n", buscar_nome(j));
        printf("Pontos restantes: %d\n\n", buscar_pontos_livres(j));
        for (i = 0; i < NUM_ATRIBUTOS; i++)
            printf("[%d] %-9s: %d\n", i + 1, nomes[i], buscar_atributo(j, (Atributo) i));

        printf("\nAtributo: ");
        if (scanf("%d", &op) != 1) { limpar_buffer(); continue; }
        printf("Quantidade: ");
        if (scanf("%d", &qtd) != 1) { limpar_buffer(); continue; }
        limpar_buffer();

        if (op < 1 || op > NUM_ATRIBUTOS || !adicionar_pontos(j, (Atributo)(op - 1), qtd)) {
            printf("Valor invalido!\n");
            pausar();
        }
    }
    aplicar_atributos(j);
}

/* Retorna 1 se usou item (fim do turno), 0 se voltou/falhou */
int menu_inventario(Jogador* j){
    int op, efeito;

    printf("\n%-42s| QTD.\n", "NOME DO ITEM");
    printf("[1] %-38s| %d\n", "Pocao de Vida (cura 15-25%)", buscar_qtd_item(j, ITEM_VIDA));
    printf("[2] %-38s| %d\n", "Pocao de Ataque (+3 ATQ)", buscar_qtd_item(j, ITEM_ATAQUE));
    printf("[3] %-38s| %d\n", "Pocao de Defesa (+3 DEF)", buscar_qtd_item(j, ITEM_DEFESA));
    printf("[0] Voltar\nEscolha: ");

    if (scanf("%d", &op) != 1) { limpar_buffer(); return 0; }
    limpar_buffer();
    if (op < 1 || op > NUM_ITENS) return 0;

    efeito = usar_item(j, (TipoItem)(op - 1));
    if (efeito == 0)  { printf("Item indisponivel!\n"); return 0; }
    if (efeito == -1) { printf("Vida ja esta cheia!\n"); return 0; }

    if (op == 1) printf("%s recuperou %d de vida!\n", buscar_nome(j), efeito);
    else         printf("Atributo aumentado em %d!\n", efeito);
    return 1;
}
//sug. Auri: pode separar em outra interface de ações;
void turnos(Jogador* a, Jogador* b, int x){
        int acao;

        acoes_text(x);

        scanf("%d", &acao);

        if (acao == 1){
            receber_dano(b, dano(a, 10, 15));
        } else if (acao == 2 && buscar_estamina(a) > 0){
            receber_dano(b, dano(a, 15, 20));
            alterar_estamina(a, 5);
        } else {
            // sug. Auri: o reload tem que mostrar o feedback para o usuario
            printf("Ação invalida! Jogador perdeu o turno!\n");
        }

}

void limpar_tela() {
    printf("\033[H\033[2J\033[3J");
    fflush(stdout); 
}





