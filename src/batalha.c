#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/interface.h"
#include "../include/jogador.h"

// string: precisa prevenir erros
void string(char *destino, int x){

    char nome[50];
    
    printf("Digite o nome do Jogador %d: ", x);
    
    if (fgets(nome, sizeof(nome), stdin) != NULL) {
        size_t tam = strlen(nome);
        if (tam > 0 && nome[tam - 1] == '\n') {
            nome[tam - 1] = '\0';
        }
    }

    int i = 0;
    while(nome[i] != '\0'){
        *destino = nome[i];
        destino++;
        i++;
    }

    *destino = '\0';

    return;
}; 


int main(){
	
	srand(time(NULL));
    iniciar_jogo();

    char nome[50];
    string(nome, 1);

    Jogador* a = criar(nome);
    if (!a) {
        printf("ERROR: Não foi possivel cadastrar jogador\n");
        return 1;
    }

    string(nome, 2);
    Jogador* b = criar(nome);
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


    if (vida_rest(a)> vida_rest(b)) resultado(a);
    else resultado(b);

    destruir(a);
    a = NULL;

    destruir(b);
    b = NULL;

    return 0;
}