#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#include "../include/interface.h"
#include "../include/jogador.h"
#include "../include/persistencia.h"


int atualiza_resultado(Arquivo* arq, Jogador* a, Jogador* b){
    resultado_partida(a);
    int atu_a = salvar_resultados(arq, buscar_nome(a), RESULTADO_VITORIA);
    int atu_b = salvar_resultados(arq, buscar_nome(b), RESULTADO_DERROTA);

    if (atu_a != 1 ||atu_b != 1)return -1;
    else return 1;

}


int main(){

    bem_vindo();
    srand(time(NULL));

    //ARQUIVO
    Arquivo *arq = abrir();
    if (!arq) {
        printf("ERROR: Não foi possivel abrir arquivo!\n");
        return 1;
    }

    //HISTORICO
    ListaEstatisticas *estatisticas = ler_estatisticas(arq);
    if (!estatisticas) {
        printf("ERROR: Não foi possivel obter estatisticas!\n");
        fechar(arq);
        return 1;
    }

    mostrar_historico(estatisticas);
    destruir_estatisticas(estatisticas);

    // JOGADORES
    char nome[50];
    if (receber_nome(nome, 1) == 0) return 1;
    Jogador* a = criar(nome);
    
    if (!a) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        fechar(arq);

        return 1;
    }

    if (receber_nome(nome, 2) == 0) return 1;
    Jogador* b = criar(nome);

    if (!b) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        fechar(arq);
        destruir_jogador(a);

        return 1;
    }

    //JOGO 
    limpar_tela();

    while (vida_rest(a)> 0 && vida_rest(b)> 0){
        atributos(a,b);
        turnos(a, b);
        if(vida_rest(b)<=0) break;

        atributos(a, b);
        turnos(b, a);
    }

    atributos(a,b);

    
    int salvar = 0;
    if (vida_rest(a)> vida_rest(b)){ 
        salvar = atualiza_resultado(arq, a, b);
    } else{
        salvar = atualiza_resultado(arq, b, a);
    }

    if (salvar != 1){
        destruir_jogador(a);
        destruir_jogador(b);
        fechar(arq);
        printf("ERROR: Não foi possivel salvar resultado\n");
        return 1;
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

    destruir_jogador(a);
    a = NULL;

    destruir_jogador(b);
    b = NULL;

    return 0;
}
