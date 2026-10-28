#include <stdio.h>
#include <string.h>

#include "../include/interface.h"
#include "../include/jogador.h"
#include "../include/persistencia.h"

// string: precisa prevenir erros
int string(char *destino, int x){

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

void atualiza_resultado(Arquivo* arq, Jogador* a, Jogador* b){
    resultado(a);
    atualizar(arq, buscar_nome(a), buscar_ganhos(a), buscar_percas(a), 'g');
    atualizar(arq, buscar_nome(b), buscar_ganhos(b), buscar_percas(b), 'p');
}


int main(){

    int ganhos = 0, percas = 0;

    iniciar_jogo();

    //Aurilene: falta organizar umas coisas do arquivo. 
    Arquivo *arq = abrir();
    if (!arq) {
        printf("ERROR: Não foi possivel abrir arquivo!\n");
        return 1;
    }

    ler(arq);

    char nome[50];
    if (string(nome, 1) == 0) return 1;
    buscar(arq, nome, &ganhos, &percas);
    Jogador* a = criar(nome, ganhos, percas);

    //Jogador* a = criar(nome);
    if (!a) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        return 1;
    }

    ganhos = 0, percas = 0;
    if (string(nome, 2) == 0) return 1;
    buscar(arq, nome, &ganhos, &percas);
    Jogador* b = criar(nome, ganhos, percas);

    //Jogador* b = criar(nome);
    // FIM;
    if (!b) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        return 1;
    }
    
    while (vida_rest(a)> 0 && vida_rest(b)> 0){

        atributos(a,b);
        turnos(a, b, 1);
        if(vida_rest(b)<=0) break;

        atributos(a, b);
        turnos(b, a, 2);
    }

    atributos(a,b);

     //Aurilene: falta organizar umas chamadas de ateração do arquivo. 
    if (vida_rest(a)> vida_rest(b)){ 
        atualiza_resultado(arq, a, b);
    } else{
        atualiza_resultado(arq, b, a);
    }

    ler(arq);

    //GERENCIAMENTO DE MEMORIA

    fechar(arq);
    arq = NULL;

    destruir(a);
    a = NULL;

    destruir(b);
    b = NULL;

    return 0;
}