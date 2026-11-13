#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#include "../include/interface.h"
#include "../include/jogador.h"
#include "../include/persistencia.h"


void atualiza_resultado(Arquivo* arq, Jogador* a, Jogador* b){
    resultado(a);
    salvar_resultados(arq, buscar_nome(a), RESULTADO_VITORIA);
    salvar_resultados(arq, buscar_nome(b), RESULTADO_DERROTA);
}


int main(){

    iniciar_jogo();
    srand(time(NULL));

    Arquivo *arq = abrir();
    if (!arq) {
        printf("ERROR: Não foi possivel abrir arquivo!\n");
        return 1;
    }

    ListaEstatisticas *estatisticas = ler_estatisticas(arq);
    if (!estatisticas) {
        fechar(arq);
        return 1;
    }

    mostrar_historico(estatisticas);
    destruir_estatisticas(estatisticas);
    estatisticas = NULL;

    // JOGADORES
    char nome[50];
    if (receber_nome(nome, 1) == 0) return 1;
    Jogador* a = criar(nome);
    
    if (!a) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        return 1;
    }

    if (receber_nome(nome, 2) == 0) return 1;
    Jogador* b = criar(nome);

    if (!b) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        return 1;
    }

    limpar_tela();

    while (vida_rest(a)> 0 && vida_rest(b)> 0){
        atributos(a,b);
        turnos(a, b);
        if(vida_rest(b)<=0) break;

        atributos(a, b);
        turnos(b, a);
    }


    atributos(a,b);

    if (vida_rest(a)> vida_rest(b)){ 
        atualiza_resultado(arq, a, b);
    } else{
        atualiza_resultado(arq, b, a);
    }

    estatisticas = ler_estatisticas(arq);
    if (estatisticas) {
        ordenar_estatisticas_por_vitorias(estatisticas);
        mostrar_ranking(estatisticas, 5);
        destruir_estatisticas(estatisticas);
        estatisticas = NULL;
    } else {
        printf("ERROR: Não foi possivel montar o ranking!\n");
    }

    //GERENCIAMENTO DE MEMORIA

    fechar(arq);
    arq = NULL;

    destruir(a);
    a = NULL;

    destruir(b);
    b = NULL;

    return 0;
}
