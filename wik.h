#ifndef WIK_H_
#define WIK_H_

/*Estrutura da WIKED!
  Deve conter:
  - páginas
  - editores
*/
typedef struct tipoWiked Wiked;

/*Estrutura do editor
  Deve conter:
  - nome do editor
  - contribuições
*/
typedef struct tipoEditor Editor;

/*Estrutura da página
  Deve conter:
  - nome da página
  - nome do arquivo
  - arquivos (contribuições)
  - links
*/
typedef struct tipoPagina Pagina;

/*Estrutura da contribuição
  Deve conter:
  - nome do arquivo (.txt)
  - nome do editor
  - nome da página
  - estado (presente / removido)
*/
typedef struct tipoContribuicao Contribuicao;

/*Inicializa a WIKED!
* inputs: nenhum
* outputs: a wik
* pre-condição: nenhum
* pos-condição: wik criada e vazia
*/
Wiked* InicializaWik();

/*Insere uma página na WIKED!
* inputs: a wik e a página
* outputs: nenhum
* pre-condição: wik e página válidos
* pos-condição: pagina pertence a wik
*/
void InserePagina(Wiked* wik, Pagina* pagina);

/*Retira uma página da WIKED!
* inputs: wik e nome da página
* outputs: a pagina removida
* pre-condição: wik e a página válidos
* pos-condição: wik não contem a página e não há links para a página
*/
Pagina* RetiraPagina(Wiked* wik, char* pagina);

/*Insere um novo editor na WIKED!
* inputs: a wik e o editor
* outputs: nenhum
* pre-condição: wik e editor válidos
* pos-condição: wik contem o editor
*/
void InsereEditor(Wiked* wik, Editor* editor);

/*Retira um editor da WIKED!
* inputs: a wik e o nome do editor
* outputs: o editor removido
* pre-condição: wik e editor válidos
* pos-condição: wik não contem o editor e suas contribuições
*/
Editor* RetiraEditor(Wiked* wik, char* editor);

/*Insere uma contribuição numa página da WIKED!
* inputs: a página e a contribuição
* outputs: nenhum
* pre-condição: página e contribuição válidos
* pos-condição: página contem a contribuição
*/
void InsereContribuicao(Pagina* pagina, Contribuicao* contribuicao);

/*Retira uma contribuição de uma página da WIKED!
* inputs: a wik, nome da página, nome do editor e o nome do arquivo
* outputs: contribuição retirada
* pre-condição: página, editor e contribuição válidos
* pos-condição: contribuição recebe estado "removido"
*/
Contribuicao* RetiraContribuicao(Wiked* wik, char* pagina, char* editor, char* arquivo);

/*Insere um link entre páginas
* inputs: wik, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wik e páginas válidas
* pos-condição: link existe na página origem e aponta para a página destino
*/
void InsereLink(Wiked* wik, char* origem, char* destino);

/*Retira um link de uma página
* inputs: wik, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wik e páginas válidas
* pos-condição: origem não contem link para destino
*/
void RetiraLink(Wiked* wik, char* origem, char* destino);

/*Verifica se há um link entre duas páginas (resposta impressa no arquivo log.txt)
* inputs: wik, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wik e páginas válidas
* pos-condição: nenhum
*/
void Caminho(Wiked* wik, char* origem, char* destino);

/*Imprime uma página num arquivo .txt
* inputs: wik e nome da página
* outputs: nenhum
* pre-condição: wik e página válidos
* pos-condição: nenhum
*/
void ImprimePagina(Wiked* wik, char* pagina);

/*Imprime todas as páginas da WIKED!
* inputs: a wik
* outputs: nenhum
* pre-condição: wik válida
* pos-condição: nenhum
*/
void ImprimeWiked(Wiked* wik);

/*Libera toda memoria alocada na WIKED!
* inputs: a wik
* outputs: NULL
* pre-condição: wik não nula
* pos-condição: toda memória liberada
*/
Wiked* destroiWiked(Wiked* wik);

/*Inicializa uma pagina
* inputs: nome da página e nome do arquivo da página
* outputs: a página
* pre-condição: nome da página único
* pos-condição: página criada e vazia
*/
Pagina* InicializaPagina(char* pagina, char* arquivo);

/*Inicializa um editor
* inputs: nome do editor
* outputs: o editor criado
* pre-condição: nome do editor único
* pos-condição: editor criado e vazio
*/
Editor* InicializaEditor(char* nome);

/*Inicializa uma contribuição
* inputs: nome da página, nome do editor e nome do arquivo
* outputs: a contribuição
* pre-condição: nome do arquivo, editor e página válidos
* pos-condição: contribuição criada e linkada ao editor e a página
*/
Contribuicao* InicializaContribuicao(char* pagina, char* editor, char* arquivo);

#endif
