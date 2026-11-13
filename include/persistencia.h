#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "estatisticas.h"

typedef enum {
    RESULTADO_VITORIA,
    RESULTADO_DERROTA
} ResultadoPartida;

typedef struct Arquivo Arquivo;

Arquivo* abrir();
ListaEstatisticas* ler_estatisticas(Arquivo* a);

void fechar(Arquivo* a);

int salvar_resultados(Arquivo *a, const char* n, ResultadoPartida resultado);
void ranking(Arquivo *a, int limite); //limite para informar a quantidade de posições no ranking, por exemplo:  top 5.

#endif