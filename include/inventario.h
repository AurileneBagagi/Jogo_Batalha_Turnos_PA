#ifndef INVENTARIO_H
#define INVENTARIO_H

typedef struct Inventario Inventario;

Inventario* criar_inventario();
void destruir_inventario(Inventario *inv);

int adicionar_item(Inventario *inv, int id, int qtd);
int remover_item(Inventario *inv, int id, int qtd);
int consultar_item(Inventario *inv, int id);
void listar_inventario(Inventario *inv);

int tamanho_inventario(Inventario *inv);
int id_em(Inventario *inv, int pos);
int quantidade_em(Inventario *inv, int pos);

const char* nome_item(int id);

#endif
