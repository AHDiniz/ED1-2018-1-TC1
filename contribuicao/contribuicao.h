#ifndef CONTRIBUICAO_H_
#define CONTRIBUICAO_H_

/*Estrutura da contribuição
  Deve conter:
  - nome do arquivo (.txt)
  - nome do editor
  - nome da página
  - estado (presente / removido)
*/
typedef struct tipoContribuicao Contribuicao;

/*Inicializa uma contribuição
* inputs: nome da página, nome do editor e nome do arquivo
* outputs: a contribuição
* pre-condição: nome do arquivo, editor e página válidos
* pos-condição: contribuição criada e linkada ao editor e a página
*/
Contribuicao* InicializaContribuicao(char* pagina, char* editor, char* arquivo);

/*Libera toda memória alocada em um editor
* inputs: contribuição
* outputs: NULL
* pre-condição: contribuição não nula
* pos-condição: toda memória liberada
*/
Contribuicao* DestroiContribuicao(Contribuicao* contribuicao);

#endif
