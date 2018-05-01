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
Contribuicao* InicializaContribuicao(const char* pagina, const char* editor, const char* arquivo)
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
    contribuicao->estado = 0; // Alterando estado para "removido"

    free(contribuicao->editor); // liberando o editor para poupar memória
    free(contribuicao->pagina); // liberando a página para poupar memória
    contribuicao->editor = contribuicao->pagina = NULL;
}

char* ContribuicaoArquivo(Contribuicao* contribuicao)
{
    char *arq = (char*) malloc(strlen(contribuicao->arquivo) +1); // alocando espaço nescessario para a string
    strcpy(arq,contribuicao->arquivo);                            // copiado a string

    return arq;
}

char* ContribuicaoEditor(Contribuicao* contribuicao)
{
    char *ed = (char*) malloc(strlen(contribuicao->editor) +1); // alocando espaço nescessario para a string
    strcpy(ed,contribuicao->editor);                            // copiado a string

    return ed;
}

char* ContribuicaoPagina(Contribuicao* contribuicao)
{
    char *pag = (char*) malloc(strlen(contribuicao->pagina) +1); // alocando espaço nescessario para a string
    strcpy(pag,contribuicao->pagina);                            // copiado a string

    return pag;
}

int ContribuicaoEstado(Contribuicao* contribuicao)
{
    return contribuicao->estado;
}

void DestroiContribuicao(void* contribuicao)
{
    // convertendo para Contrbuicao*
    Contribuicao *c = (Contribuicao*) contribuicao;

    // caso esteja vazio aborta-se a função
    if(c == NULL)
    {
        return;
    }

    // Liberando as strings
    free(c->arquivo); // liberando arquivo

    if(c->editor != NULL) // verificando se a string já não foi removida (pertençe somente ao histórico)
    {
        free(c->editor); // liberando editor
        c->editor = NULL; // medida de sugurança
    }

    if(c->pagina != NULL) // verificando se a string já não foi removida (pertençe somente ao histórico)
    {
        free(c->pagina); // liberando pagina
        c->pagina = NULL; // medida de sugurança
    }

    // Liberando a contribuição
    free(c);
    c = NULL; // medida de sugurança
}
