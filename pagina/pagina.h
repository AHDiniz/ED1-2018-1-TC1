/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

pagina.h: definições para páginas
********************************************/

#ifndef PAGINA_H_
#define PAGINA_H_

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

/*Libera toda memória alocada em uma pagina
* inputs: página
* outputs: NULL
* pre-condição: página não nula
* pos-condição: página vazia e toda memória liberada
*/
Pagina* DestroiPagina(Pagina* pagina);

/*Insere uma contribuição numa página e num editor
* inputs: a página, o editor e a contribuição
* outputs: nenhum
* pre-condição: página, editor e contribuição válidos
* pos-condição: página e editor contêm a contribuição
*/
void InsereContribuicao(Pagina* pagina, Editor* editor, Contribuicao* contribuicao);

#endif
