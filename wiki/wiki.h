/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

wiki.h: definições para implementação da WikED!
********************************************/

#ifndef WIKI_H_
#define WIKI_H_

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
* inputs: a wiki e a página
* outputs: nenhum
* pre-condição: wiki e página válidos
* pos-condição: pagina pertence a wiki
*/
void InserePagina(Wiked* wiki, Pagina* pagina);

/*Retira uma página da WIKED!
* inputs: wiki e nome da página
* outputs: nenhum
* pre-condição: wiki e a página válidos
* pos-condição: wiki não contem a página e não há links para a página
*/
void RetiraPagina(Wiked* wiki, char* pagina);

/*Insere um novo editor na WIKED!
* inputs: a wiki e o editor
* outputs: nenhum
* pre-condição: wiki e editor válidos
* pos-condição: wiki contem o editor
*/
void InsereEditor(Wiked* wiki, Editor* editor);

/*Retira um editor da WIKED!
* inputs: a wiki e o nome do editor
* outputs: nenhum
* pre-condição: wiki e editor válidos
* pos-condição: wiki não contem o editor e suas contribuições
*/
void RetiraEditor(Wiked* wiki, char* editor);

/*Retira uma contribuição de uma página da WIKED!
* inputs: a wiki, nome da página, nome do editor e o nome do arquivo
* outputs: nenhum
* pre-condição: página, editor e contribuição válidos
* pos-condição: contribuição recebe estado "removido"
*/
void RetiraContribuicao(Wiked* wiki, char* pagina, char* editor, char* arquivo);

/*Insere um link entre páginas
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: link existe na página origem e aponta para a página destino
*/
void InsereLink(Wiked* wiki, char* origem, char* destino);

/*Retira um link de uma página
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: origem não contem link para destino
*/
void RetiraLink(Wiked* wiki, char* origem, char* destino);

/*Verifica se há um link entre duas páginas (resposta impressa no arquivo log.txt)
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: nenhum
*/
void Caminho(Wiked* wiki, char* origem, char* destino);

/*Imprime uma página num arquivo .txt
* inputs: wiki e nome da página
* outputs: nenhum
* pre-condição: wiki e página válidos
* pos-condição: nenhum
*/
void ImprimePagina(Wiked* wiki, char* pagina);

/*Imprime todas as páginas da WIKED!
* inputs: a wiki
* outputs: nenhum
* pre-condição: wiki válida
* pos-condição: nenhum
*/
void ImprimeWiked(Wiked* wiki);

/*Libera toda memoria alocada na WIKED!
* inputs: a wiki
* outputs: NULL
* pre-condição: wiki não nula
* pos-condição: toda memória liberada
*/
Wiked* destroiWiked(Wiked* wiki);

#endif
