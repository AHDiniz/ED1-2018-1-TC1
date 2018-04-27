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

// Inicializa um struct contribuição
Contribuicao* InicializaContribuicao(char* pagina, char* editor, char* arquivo)
{
    Contribuicao *c = (Contribuicao*) malloc(sizeof(Contribuicao)); // alocando espaço para a struct

    c->arquivo = (char*) malloc(strlen(arquivo) +1); // alocando espaço para string arquivo
    strcpy(c->arquivo,arquivo);                      // copiando string arquivo

    c->editor = (char*) malloc(strlen(editor) +1); // alocando espaço para string editor
    strcpy(c->editor,editor);                      // copiando string editor

    c->pagina = (char*) malloc(strlen(pagina) +1); // alocando espaço para string pagina
    strcpy(c->pagina,pagina);                      // copiando string pagina

    c->estado = 1; // indicando estado "presente"

    return c; // retornando contribuição
}

void RetiraContribuicao(Contribuicao* contribuicao)
{
    contribuicao->estado = 0;
}

void DestroiContribuicao(void* contribuicao)
{
    // convertendo para Contrbuicao*
    Contribuicao *c = (Contribuicao*) contribuicao;
    // Liberando as strings
    free(c->arquivo);
    free(c->editor);
    free(c->pagina);
    // Liberando a contribuição
    free(c);
}
