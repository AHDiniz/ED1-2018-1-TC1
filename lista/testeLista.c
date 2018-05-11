/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

testeLista.c: teste da TAD lista genérica
********************************************/

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    Lista* listaInt = NovaLista("char*"); // Criando uma nova lista de inteiros
    int i;
    char *a = (char*) malloc(strlen("bananas") +1);
    strcpy(a,"bananas");
    char *b = (char*) malloc(strlen("cozidas") +1);
    strcpy(a,"cozidas");
    char *c = (char*) malloc(strlen("muito") +1);
    strcpy(a,"muito");
    char *d = (char*) malloc(strlen("saudaveis") +1);
    strcpy(a,"saudaveis");

    printf("Lista Vazia: %s\nComprimento: %d\n", (ListaVazia(listaInt)) ? "sim" : "nao", TamanhoLista(listaInt));

    // Criando itens:
    Item* ia = NovoItem("char*", a);
    Item* ib = NovoItem("char*", b);
    Item* ic = NovoItem("char*", c);
    Item* id = NovoItem("char*", d);

    // Adicionando os itens na lista:
    ListaAdd(listaInt, ia);
    ListaAdd(listaInt, ib);
    ListaAdd(listaInt, ic);
    ListaAdd(listaInt, id);

    // Imprimindo os itens:
    printf("Itens da lista:");
    for (i = 0; i < TamanhoLista(listaInt); i++)
    {
        char* cnt = (char*)(AchaItem(listaInt, i));
        printf(" %s", cnt);
    }
    printf("\n");

    printf("Lista Vazia: %s\nComprimento: %d\n", (ListaVazia(listaInt)) ? "sim" : "nao", TamanhoLista(listaInt));

    // Destruindo a lista e seus itens:
    DestroiLista(listaInt, free);

    return 0;
}
