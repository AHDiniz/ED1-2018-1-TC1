#ifndef LISTA_H

#define LISTA_H

// Definindo um novo tipo de lista:
typedef struct lista Lista;

// Definindo um tipo para o item da lista:
typedef struct item Item;

/*
Nova Lista:
- Entrada: nenhuma;
- Saída: um ponteiro para uma nova lista vazia;
- Pré-condições: nenhuma;
- Pós-condições: a lista está vazia;
*/
Lista* NovaLista(void);

/*
Adicionar item na lista:
- Entrada: a lista e o item a ser adicionado;
- Saída: nenhuma;
- Pré-condições: a lista e o item não podem estar vazios;
- Pós-condições: o item é adicionado na lista e ela fica maior;
*/
void ListaAdd(Lista* lista, Item* item);

/*
Remover item na lista:
- Entrada: a lista e a posição do item a ser removido;
- Saída: o item removido;
- Pré-condições: a lista não pode estar vazia e a posição deve ficar entre zero e o tamanho atual da lista;
- Pós-condições: o item é removido da lista e ela fica menor;
*/
Item* ListaRemove(Lista* lista, int pos);

#endif