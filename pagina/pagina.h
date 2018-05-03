/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

pagina.h: definições para páginas
********************************************/

#ifndef PAGINA_H_
#define PAGINA_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../contribuicao/contribuicao.h"
#include "../editor/editor.h"
#include "../lista/lista.h"

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
Pagina* InicializaPagina(const char* pagina, const char* arquivo);

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

/*Retorna o nome da página
* inputs: a página
* outputs: string nome da página
* pre-condição: página não nula
* pos-condição: página não alterada
*/
char* PaginaNome(Pagina* pagina);

/*Retorna o nome do arquivo da página
* inputs: a página
* outputs: string nome do arquivo da página
* pre-condição: página não nula
* pos-condição: página não alterada
*/
char* PaginaArquivo(Pagina* pagina);

/*
Retorno da lista de contribuições:
- Entrada: ponteiro para a página;
- Saída: ponteiro para a lista de contribuições;
- Pré-condições: página alocada e não nula;
- Pós-condições: nenhum efeito colateral;
*/
Lista* ListaContrbPagina(Pagina* pagina);

/*
Retorno da lista de links:
- Entrada: ponteiro para a página;
- Saída: ponteiro para a lista de links;
- Pré-condições: página alocada e não nula;
- Pós-condições: nenhum efeito colateral;
*/
Lista* ListaLinksPagina(Pagina *pagina);

/*Libera toda memória alocada em uma pagina
* inputs: endereço de ponteiro genérico para página
* outputs: nenhum
* pre-condição: página não nula
* pos-condição: página vazia e toda memória liberada
*/
void DestroiPagina(void** pagina);

#endif
