/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

editor.c: implementações para editores
********************************************/

#include "editor.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Estrutura do editor
  Deve conter:
  - nome do editor
  - contribuições
*/
struct tipoEditor{

    char *nome;
    Lista *contribuicoes;
};

/*Inicializa um editor
* inputs: nome do editor
* outputs: o editor criado
* pre-condição: nome do editor único
* pos-condição: editor criado e vazio
*/
Editor* InicializaEditor(const char* nome);

/*Libera toda memória alocada em um editor
* inputs: editor
* outputs: NULL
* pre-condição: editor não nulo
* pos-condição: toda memória liberada
*/
void DestroiEditor(void* editor);
