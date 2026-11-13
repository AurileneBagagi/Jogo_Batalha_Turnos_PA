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

#endif