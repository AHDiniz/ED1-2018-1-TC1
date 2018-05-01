/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

editor.c: implementações para editores
********************************************/

#include "editor.h"
#include "../lista/lista.h"
#include "../contribuicao/contribuicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tipoEditor{

    char *nome;
    Lista *contribuicoes;
};

Editor* InicializaEditor(const char* nome)
{
  Editor *e = (Editor*) malloc(sizeof(Editor)); // inicializando o struct

    e->nome = (char*) malloc(strlen(nome) +1); // alocando espaço da string nome
    strcpy(e->nome,nome);                      // copiando nome

    e->contribuicoes = NovaLista("Contribuicao"); // inicializando lista de contribuições vazia
}

void InsereContribuicaoEditor(Editor* editor, Contribuicao* contribuicao)
{
    Item *item = NovoItem("Contribuicao",contribuicao); // cria um item para a contribuição

    ListaAdd(editor->contribuicoes,item); // inclui o item na lista de contribuições
}

char* EditorNome(Editor* editor)
{
    char *nome = (char*) malloc(strlen(editor->nome) +1); // alocando espaço nescessario para a string
    strcpy(nome,editor->nome);                            // copiado a string

    return nome;
}

Lista* EditorContribuicoes(Editor* editor)
{
    return editor->contribuicoes;
}

void DestroiEditor(void* editor)
{
    Editor *e = (Editor*) editor; // convertendo para ponteiro de tipo Editor

    // caso esteja vazio aborta-se a função
    if(e == NULL)
    {
        return;
    }

    free(e->nome); // liberando o nome

    DestroiLista(e->contribuicoes, DestroiContribuicao); // liberando a lista

    free(e); // liberando o struct
    e = NULL; // medida de segurança
}
