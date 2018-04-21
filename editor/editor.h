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
Editor* InicializaEditor(char* nome);

/*Libera toda memória alocada em um editor
* inputs: editor
* outputs: NULL
* pre-condição: editor não nulo
* pos-condição: toda memória liberada
*/
Editor* DestroiEditor(Editor* editor);

#endif
