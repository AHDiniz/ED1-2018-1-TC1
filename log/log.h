/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

log.h: definições para mensagens de erro e para função Caminho
********************************************/

#ifndef LOG_H_
#define LOG_H_

/*mensagem de resposta da função Caminho
* inputs: confirmação, nome da origem e nome do destino
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem:
  caso 0:    "HA CAMINHO DA PAGINA %s PARA %s"
  caso != 0: "NAO HA CAMINHO DA PAGINA %s PARA %s"
*/
void CaminhoResposta(int i, char* origem, char* destino);

/*Erro001: página inexistente
* inputs: nome da página
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: nao existe a pagina %s"
*/
void ErroPagInexistente(char* pagina);

/*Erro002: editor inexistente
* inputs: nome do editor
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: nao existe o editor %s"
*/
void ErroEdtInexistente(char* editor);

/*Erro003: contribuição inexistente
* inputs: nome da contribuição
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: nao existe a contribuicao %s"
*/
void ErroContInexistente(char* contribuicao);

/*Erro004: página incorreta
* inputs: nome da página
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: pagina %s incorreta"
*/
void ErroPagIncorreta(char* pagina);

/*Erro005: editor incorreto
* inputs: nome do editor
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: editor %s incorreto"
*/
void ErroEdtIncorreto(char* editor);

/*Erro006: página já existe
* inputs: nome da página
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: pagina %s ja existe"
*/
void ErroPagExiste(char* pagina);

/*Erro007: editor já existe
* inputs: nome do editor
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: editor %s ja existe"
*/
void ErroEdtExiste(char* editor);

/*Erro008: contribuição já existe
* inputs: nome da contribuição
* outputs: nenhum
* pre-condição: nenhum
* pos-condição: nenhum
* mensagem: "ERRO: a contribuicao %s ja existe"
*/
void ErroContExiste(char* contribuicao);

#endif
