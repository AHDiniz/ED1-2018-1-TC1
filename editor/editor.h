/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

editor.h: definições para editores
********************************************/

#ifndef EDITOR_H_
#define EDITOR_H_

/*Estrutura do editor
  Deve conter:
  - nome do editor
  - contribuições
*/
typedef struct tipoEditor Editor;

/*Inicializa um editor
* inputs: nome do editor
* outputs: o editor criado
* pre-condição: nome do editor único
* pos-condição: editor criado e vazio
*/
Editor* InicializaEditor(const char* nome);

/*Insere uma contribuição num editor
* inputs: o editor e a contribuição
* outputs: nenhum
* pre-condição: editor e contribuição válidos
* pos-condição: editor contêm a contribuição
*/
void InsereContribuicaoEditor(Editor* editor, Contribuicao* contribuicao);

/*Retorna o nome do editor
* inputs: o editor
* outputs: string nome do editor
* pre-condição: editor não nulo
* pos-condição: editor não alterado
*/
char* EditorNome(Editor* editor);

/*Retorna um ponteiro para as contribuições do editor
* inputs: o editor
* outputs: ponteiro para lista de contribuições
* pre-condição: editor não nulo
* pos-condição: editor não alterado
*/
Lista* EditorContribuicoes(Editor* editor);

/*Libera toda memória alocada em um editor
* inputs: endereço de ponteiro genérico para editor
* outputs: nenhum
* pre-condição: editor não nulo
* pos-condição: toda memória liberada
*/
void DestroiEditor(void** editor);

#endif
