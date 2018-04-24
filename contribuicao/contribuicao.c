/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

contribuicao.c: implementações para contribuições
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contribuicao.h"

/*Estrutura da contribuição
  Deve conter:
  - nome do arquivo (.txt)
  - nome do editor
  - nome da página
  - estado (presente = 1 / removido = 0)
*/
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

Contribuicao* DestroiContribuicao(Contribuicao* contribuicao){

    free(c->arquivo);
    free(c->editor);
    free(c->pagina);
    free(c);

    return NULL;
}
