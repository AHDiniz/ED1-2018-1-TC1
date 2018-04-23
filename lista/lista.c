/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

lista.c: implementações para lista genérica
********************************************/

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementando uma lista genérica:
struct lista
{
    Item* primeiro;  // Ponteiro para o primeiro item da lista
    Item* ultimo;    // Ponteiro para o último item da lista
    char* tipo;      // Tag com o tipo de item que a lista contém
    int comprimento; // Comprimento da lista (quantidade de itens)
};

// Implementando um item de uma lista genérica:
struct item
{
    void *conteudo; // Ponteiro para o conteúdo do item
    char *tipo;     // Tag com o tipo do conteúdo do item
    Item *proximo;  // Ponteiro para o próximo item da lista
    int posicao;    // Posição do item na lista
};

// Funções estáticas:

// Função de comparação de tipos entre lista e item:
static int CmpTipoListaItem(Lista* lista, Item* item)
{
    if (strcmp(lista->tipo, item->tipo) == 0)
        return 1;
    else
        return 0;
}

// Alocando uma nova lista dinamicamente:
Lista* NovaLista(const char* tipo)
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); // Alocando dinamicamente o espaço de memória necessário para a nova lista
    
    lista->tipo = (char*)malloc(strlen(tipo) + 1); // Alocando dinamicamente o espaço necessário para a tag de tipo da lista
    strcpy(lista->tipo, tipo); // Copiando o conteúdo da string de entrada para o campo do struct

    lista->primeiro = lista->ultimo = NULL; // A lista está vazia (não há nada nem na primeira nem na última posição)

    lista->comprimento = 0; // A lista tem tamanho zero

    return lista;
}

// Verificação de lista vazia:
int ListaVazia(Lista* lista)
{
    return (lista->comprimento == 0); // Se o comprimento da lista é igual a zero, então não há nenhum item nela
}

// Adicionando um item na lista:
void ListaAdd(Lista* lista, Item* item)
{
    if (!CmpTipoListaItem(lista, item)) // Comparando os tipos da lista e do item
    {
        printf("Tentando inserir um item de um tipo diferente da lista.\n");
        return; // Se forem diferentes, o item não será adicionado na lista
    }
    if (ListaVazia(lista)) // Se a lista for vazia
        lista->primeiro = item; // O primeiro item da lista vai ser o item de entrada da função
    else // Se a lista possuir algum elemento
        lista->ultimo->proximo = item; // O próximo item do atual último da lista é o item de entrada
    lista->ultimo = item; // O último item da lista será o item de entrada
    item->posicao = lista->comprimento; // Definindo a posicao do item de entrada na lista
    lista->comprimento++; // Atualizando o tamanho da lista
}

// Removendo um item da lista:
void ListaRemove(Lista* lista, int pos, FreeContItem Func)
{
    int i;
    if (pos == 0) // Se o item a ser retirado é o primeiro
    {
        Item* alvo = lista->primeiro; // Auxiliar para não perder a referência do item a ser removido
        lista->primeiro = lista->primeiro->proximo; // Atualizando o valor do primeiro item da lista
        Item* item = lista->primeiro;
        // Atualizando o valor das posições dos itens da lista:
        for (i = 0; i < lista->comprimento - 1; i++)
        {
            item->posicao--;
            item = item->proximo;
        }
        LiberaItem(alvo, Func); // Liberando o item alvo da memória
    }
    if (pos == lista->comprimento - 1) // Se o item a ser retirado é o primeiro
    {
        Item* anterior = lista->primeiro; // Auxiliar que apontará para o novo último item
        Item* alvo = lista->ultimo; // Auxiliar para não perder a referência do item a ser removido
        for (i = 0; i < lista->comprimento - 1; i++) // Percorrendo a lista para achar o penúltimo item
            anterior = anterior->proximo;
        // Atualizando o valor do último item da lista:
        lista->ultimo = anterior;
        anterior->proximo = NULL;
        // Liberando o item alvo da memória:
        LiberaItem(alvo, Func);
    }
    else
    {
        // Variáveis auxiliares que ajudarão a percorrer a lista:
        Item* anterior;
        Item* atual = lista->primeiro;
        for (i = 0; i < lista->comprimento; i++) // Percorrendo cada item da lista
            if (atual->posicao == pos) // Se o item atual estiver na posição desejada
                break; // O loop será quebrado
            else
            {
                // Atualizando os valores das variáveis auxiliares:
                anterior = atual;
                atual = atual->proximo;
            }
        anterior->proximo = atual->proximo; // Atualizando os valores dos ponteiros dos itens que continuam na lista
        // Atualizando os valores das posições dos itens da lista:
        anterior = anterior->proximo; // Primeiro item que precisa ter sua posição atualizada
        for (i = i; i < lista->comprimento - 1; i++)
        {
            anterior->posicao--;
            anterior = anterior->proximo;
        }
        LiberaItem(atual, Func); // Liberando o item procurando da memória (vai acabar sendo retirado da lista)
    }
    lista->comprimento--; // Atualizando o valor do comprimento da lista
}

// Alocando um novo item dinamicamente:
Item* NovoItem(const char* tipo, void* conteudo)
{
    Item *item = (Item *)malloc(sizeof(Item)); // Alocando o espaço necessário para um novo item dinamicamente

    item->conteudo = conteudo; // Fazendo o conteudo do item apontar para o conteudo desejado

    item->tipo = (char *)malloc(strlen(tipo) + 1); // Alocando o espaço necessário para a tag do tipo do item dinamicamente
    strcpy(item->tipo, tipo);                      // Definindo a tag do tipo do item

    item->proximo = NULL; // o proximo item só será deifnido quando o item estiver numa lista

    item->posicao = 0; // Inicializando a posição do item com um placeholder

    return item;
}

// Verificação de item com conteúdo opaco:
int ItemVazio(Item* item)
{
    return (item->conteudo == NULL); // Verificando se o conteudo apontado pelo respectivo ponteiro do item é opaco
}

// Liberação de item da memória:
int LiberaItem(Item* item, FreeContItem Func)
{
    if (ItemVazio(item))
    {
        printf("O item possui conteudo opaco.\n");
        return 0;
    }
    if (Func == NULL)
    {
        printf("A funcao de entrada nao existe.\n");
        return 0;
    }
    Func(item->conteudo);
    free(item->tipo);
    free(item);
    return 1;
}