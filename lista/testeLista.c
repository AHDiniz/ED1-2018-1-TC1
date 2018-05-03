/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

testeLista.c: teste da TAD lista genérica
********************************************/

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Lista* listaInt = NovaLista("int"); // Criando uma nova lista de inteiros
    int a = 0, b = 1, c = 2, d = 3, i; // Inteiros para teste

    printf("Lista Vazia: %s\nComprimento: %d\n", (ListaVazia(listaInt)) ? "sim" : "nao", TamanhoLista(listaInt));

    // Criando itens:
    Item* ia = NovoItem("int", &a);
    Item* ib = NovoItem("int", &b);
    Item* ic = NovoItem("int", &c);
    Item* id = NovoItem("int", &d);

    // Adicionando os itens na lista:
    ListaAdd(listaInt, ia);
    ListaAdd(listaInt, ib);
    ListaAdd(listaInt, ic);
    ListaAdd(listaInt, id);

    // Imprimindo os itens:
    printf("Itens da lista: ");
    for (i = 0; i < TamanhoLista(listaInt); i++)
    {
        int* cnt = (int*)(AchaItem(listaInt, i));
        printf("%d", *cnt);
    }
    printf("\n");

    printf("Lista Vazia: %s\nComprimento: %d\n", (ListaVazia(listaInt)) ? "sim" : "nao", TamanhoLista(listaInt));

    // Destruindo a lista e seus itens:
    DestroiLista(listaInt, free);

    return 0;
}