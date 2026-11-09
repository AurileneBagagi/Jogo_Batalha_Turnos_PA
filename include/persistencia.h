#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

typedef enum {
    RESULTADO_VITORIA,
    RESULTADO_DERROTA
} ResultadoPartida;

typedef struct Arquivo Arquivo;

Arquivo* abrir();
void fechar(Arquivo* a);
void ler(Arquivo* a); // auri: ainda vou atualizar aqui.

int salvar_resultados(Arquivo *a, const char* n, ResultadoPartida resultado);

#endif