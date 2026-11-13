#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/interface.h"
#include "../include/cores.h"


void iniciar_jogo(){

    printf("=========================================\n");
    printf("            BEM VINDOS(AS) AO     \n");
    printf("        JOGO DE BATALHA DE TURNOS!\n");
    printf("=========================================\n\n");

}

void atributos(Jogador* a, Jogador* b){
    printf("\n---------------------\n");
    buscar_atributos(a);
    printf("\n");
    buscar_atributos(b);
    printf("---------------------\n");

}

void acoes_text(Jogador* j){
    printf("\n--------ACOES-----------\n\n");
    printf("Escolha sua acao Jogador \"%s\":\n", buscar_nome(j));
    printf("[1] Atacar (Dano: 10-20)\n");
    printf("[2] Habilidade (Dano: 21-31, Custo: 10 estamina)\n");
    printf("[3] Pocao de Cura | Qtd: %d\n", buscar_pocoes(j));
    printf("Digite um numero: ");
}

int dano(Jogador* j, int min, int max){
    (void)j;
    int d = (rand() % (max - min + 1)) + min;
    limpar_tela();
    printf ("%sO jogador \"%s\" deu %d de dano\n%s",TXT_VERDE_B, buscar_nome(j), d, RESET);
    return d;
}

int resultado(Jogador* j){
    printf("\n========================================\n");
    printf("PARABENS! \"%s\" ganhou o jogo!\n", buscar_nome(j));
    printf("========================================\n");

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
            receber_dano(b, dano(a, 10, 20));
        } else if (acao == 2 && buscar_estamina(a) > 0){
            receber_dano(b, dano(a, 21, 31));
            alterar_estamina(a, 10);
        } else if (acao == 3){
            usar_pocao(a);
        } else {
            limpar_tela();
            printf("%sAção invalida! Jogador \"%s\" perdeu o turno!\n%s", TXT_VERMELHO, buscar_nome(a), RESET);
        }
}

int receber_nome(char *destino, int x){

    char nome[50];
    
    printf("Digite o nome do Jogador %d: ", x);
    fflush(stdout);
    
    if (fgets(nome, sizeof(nome), stdin) != NULL) {
        size_t tam = strlen(nome);
        if (tam > 0 && nome[tam - 1] == '\n') {
            nome[tam - 1] = '\0';
        } else {
            printf("\nERROR: Nome do jogador excedeu o tamanho de 50 caracteres\n");
            return 0;
        }

        if (nome[0] == '\0') {
            printf("\nERROR: Nada foi digitado\n");
            return 0;
        }
    }

    int i = 0;
    while(nome[i] != '\0'){
        *destino = nome[i];
        destino++;
        i++;
    }

    *destino = '\0';

    return 1;
}; 

void mostrar_historico(const ListaEstatisticas *estatisticas){
    if (!estatisticas){
        printf("ERROR: historico invalido!.\n");
        return;
    }

    printf("=============== JOGADORES ===============\n");
    printf("NOME             | GANHOU |  PERDEU \n");

    for (size_t i = 0; i < quantidade_estatisticas(estatisticas); i++){
        const EstatisticaJogador *linha = obter_estatistica(estatisticas, i);
        printf(" %-16s| %-6d | %-6d\n", linha->nome, linha->vitorias,  linha->derrotas);
    }

    printf("========================================\n");
}
void mostrar_ranking(const ListaEstatisticas *estatisticas, int limite){
    if (!estatisticas){
        printf("ERROR: historico invalido!\n");
        return;
    }

    int total = (int) quantidade_estatisticas(estatisticas);
    if (total == 0){
        printf("Ainda nao ha jogadores no ranking.\n");
        return;
    }

    if (limite <= 0 || limite > total) limite = total;

    printf("====== RANKING DE VITORIAS ======\n");
    printf(" #  NOME             | VITORIAS\n");
    for (int i = 0; i < limite; i++){
        const EstatisticaJogador *linha = obter_estatistica(estatisticas, (size_t) i);
        printf("%2d  %-16s | %-8d\n", i + 1, linha->nome, linha->vitorias);
    }
    printf("=================================\n");
}

void limpar_tela() {
    printf("\033[H\033[2J\033[3J");
    fflush(stdout); 
}





