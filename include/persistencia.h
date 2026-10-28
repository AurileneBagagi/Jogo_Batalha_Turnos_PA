#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "jogador.h"

typedef struct Arquivo Arquivo;

Arquivo* abrir();
void fechar(Arquivo* a);
void ler(Arquivo* a);
int buscar(Arquivo *a, char* n, int *g, int *p);
int inserir(Arquivo *a, const char* n, int g, int p);
int atualizar(Arquivo *a, const char* n, int g, int p, char i);

#endif