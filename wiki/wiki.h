/********************************************
Trabalho ED1 2018/1: Sistema colaborativo
Alan Herculano Diniz e Rafael Belmock Pedruzzi
wiki.h: definições para implementação da WikED!
********************************************/

#ifndef WIKI_H_
#define WIKI_H_

#include "../pagina/pagina.h"
#include "../editor/editor.h"
#include "../lista/lista.h"
#include "../log/log.h"

/*Estrutura da WIKED!
  Deve conter:
  - páginas
  - editores
*/
typedef struct tipoWiked Wiked;

/*Inicializa a WIKED!
* inputs: nenhum
* outputs: a wiki
* pre-condição: nenhum
* pos-condição: wiki criada e vazia
*/
Wiked* InicializaWiki(void);

/*Insere uma página na WIKED!
* inputs: a wiki, o nome da página e o nome do arquivo da página
* outputs: nenhum
* pre-condição: wiki e página válidos
* pos-condição: pagina pertence a wiki
*/
void Wiki_InserePagina(Wiked* wiki, char* pagina, char* arquivo);

/*Retira uma página da WIKED!
* inputs: wiki e nome da página
* outputs: nenhum
* pre-condição: wiki e a página válidos
* pos-condição: wiki não contem a página e não há links para a página
*/
void Wiki_RetiraPagina(Wiked* wiki, char* pagina);

/*Insere um novo editor na WIKED!
* inputs: a wiki e o nome do editor
* outputs: nenhum
* pre-condição: wiki e editor válidos
* pos-condição: wiki contem o editor
*/
void Wiki_InsereEditor(Wiked* wiki, char* editor);

/*Retira um editor da WIKED!
* inputs: a wiki e o nome do editor
* outputs: nenhum
* pre-condição: wiki e editor válidos
* pos-condição: wiki não contem o editor e suas contribuições
*/
void Wiki_RetiraEditor(Wiked* wiki, char* editor);

/*Insere uma contribuição numa página e num editor da WikED!
* inputs: a wiki, nome da página, nome do editor e nome da contribuição
* outputs: nenhum
* pre-condição: wiki, página, editor e contribuição válidos
* pos-condição: página e editor contêm a contribuição
*/
void Wiki_InsereContribuicao(Wiked* wiki, char* pagina, char* editor, char* arquivo);

/*Retira uma contribuição de uma página da WIKED!
* inputs: a wiki, nome da página, nome do editor e o nome do arquivo
* outputs: nenhum
* pre-condição: wiki, página, editor e contribuição válidos
* pos-condição: contribuição recebe estado "removido"
*/
void Wiki_RetiraContribuicao(Wiked* wiki, char* pagina, char* editor, char* arquivo);

/*Insere um link entre páginas
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: link existe na página origem e aponta para a página destino
*/
void Wiki_InsereLink(Wiked* wiki, char* origem, char* destino);

/*Retira um link de uma página
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: origem não contem link para destino
*/
void Wiki_RetiraLink(Wiked* wiki, char* origem, char* destino);

/*Verifica se há um link entre duas páginas (resposta impressa no arquivo log.txt)
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: nenhum
*/
void Wiki_Caminho(Wiked* wiki, char* origem, char* destino);

/*Imprime uma página num arquivo .txt
* inputs: wiki e nome da página
* outputs: nenhum
* pre-condição: wiki e página válidos
* pos-condição: nenhum
*/
void Wiki_ImprimePagina(Wiked* wiki, char* pagina);

/*Imprime todas as páginas da WIKED!
* inputs: a wiki
* outputs: nenhum
* pre-condição: wiki válida
* pos-condição: nenhum
*/
void ImprimeWiked(Wiked* wiki);

/*Libera toda memoria alocada na WIKED!
* inputs: ponteiro genérico para a wiki
* outputs: nenhum
* pre-condição: wiki não nula
* pos-condição: toda memória liberada
*/
void DestroiWiked(void* wiki);

#endif
