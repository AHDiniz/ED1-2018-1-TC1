/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

contribuicao.c: implementações para contribuições
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contribuicao.h"

struct tipoContribuicao
{

    char *arquivo;
    char *editor;
    char *pagina;
    int estado;
};

Contribuicao* InicializaContribuicao(char* pagina, char* editor, char* arquivo)
{

    Contribuicao *c = (Contribuicao*) malloc(sizeof(Contribuicao));

    c->arquivo = (char*) malloc(strlen(arquivo) +1);
    strcpy(c->arquivo,arquivo);

    c->editor = (char*) malloc(strlen(editor) +1);
    strcpy(c->editor,editor);

    c->pagina = (char*) malloc(strlen(pagina) +1);
    strcpy(c->pagina,pagina);

    c->estado = 1;

    return c;
}

/*Retira uma contribuição de uma página da WIKED!
* inputs: a contribuição
* outputs: nenhum
* pre-condição: contribuição válida
* pos-condição: contribuição recebe estado "removido" (estado = 0)
*/
void RetiraContribuicao(Contribuicao* contribuicao);

void DestroiContribuicao(void* contribuicao){

    Contribuicao *c = (Contribuicao*) contribuicao;

    free(c->arquivo);
    free(c->editor);
    free(c->pagina);
    free(c);
}
