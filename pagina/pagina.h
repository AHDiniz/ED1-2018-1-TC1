/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

pagina.h: definições para páginas
********************************************/

#ifndef PAGINA_H_
#define PAGINA_H_

#include ":contribuicao/contribuicao.h"
#include ":editor/editor.h"

/*Estrutura da página
  Deve conter:
  - nome da página
  - nome do arquivo
  - arquivos (contribuições)
  - links
*/
typedef struct tipoPagina Pagina;

/*Inicializa uma pagina
* inputs: nome da página e nome do arquivo da página
* outputs: a página
* pre-condição: nome da página único
* pos-condição: página criada e vazia
*/
Pagina* InicializaPagina(char* pagina, char* arquivo);

/*Insere um link entre páginas
* inputs: a página origem e a página destino
* outputs: nenhum
* pre-condição: páginas válidas
* pos-condição: link existe na página origem e aponta para a página destino
*/
void InsereLink(Pagina* origem, Pagina* destino);

/*Retira um link de uma página
* inputs: a página origem e a página destino
* outputs: nenhum
* pre-condição: páginas válidas
* pos-condição: origem não contem link para destino
*/
void RetiraLink(Pagina* origem, Pagina* destino);

/*Verifica se há um link entre duas páginas
* inputs: a página origem e a página destino
* outputs: inteiro de carater booleano (0 ou 1)
* pre-condição: páginas válidas
* pos-condição: nenhum
*/
int Caminho(Pagina* origem, Pagina* destino);

/*Imprime uma página num arquivo .txt
* inputs: a página
* outputs: nenhum
* pre-condição: página válida
* pos-condição: nenhum
*/
void ImprimePagina(Pagina* pagina);

/*Insere uma contribuição numa página
* inputs: a página e a contribuição
* outputs: nenhum
* pre-condição: página, e contribuição válidos
* pos-condição: página contêm a contribuição
*/
void InsereContribuicaoPagina(Pagina* pagina, Contribuicao* contribuicao);

/*Libera toda memória alocada em uma pagina
* inputs: página com ponteiro genérico
* outputs: nenhum
* pre-condição: página não nula
* pos-condição: página vazia e toda memória liberada
*/
void DestroiPagina(void* pagina);

#endif
