/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

wiki.c: implementações para a WikED!
********************************************/

#include "wiki.h"
#include "../pagina/pagina.h"
#include "../lista/lista.h"
#include "../log/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i; // variavel global de teste

struct tipoWiked
{
    Lista *paginas;
    Lista *editores;
};

Wiked* InicializaWiki(void)
{
    Wiked *wiki = (Wiked*) malloc(sizeof(Wiked)); // alocando a struct

    wiki->paginas = NovaLista("Pagina"); // alocando a lista de páginas

    wiki->editores = NovaLista("Editor"); // alocando a lista de editores

    return wiki;
}

void InserePaginaWiki(Wiked* wiki, char* pagina, char* arquivo)
{
    if(ProcuraPagina(wiki,pagina) != -1) // verifica se ja existe uma página com esse nome ou se a lista é nula
    {
        ErroPagExiste(pagina); // caso sim: uma mansagem de erro sera exibina em log.txt
        return;                // e a função sera abortada
    }

    // caso contrario: a página sera inserida normalmente
    // inicializando a página
    Pagina *p = InicializaPagina(pagina,arquivo);

    // incluindo pagina na lista
    Push(wiki->paginas,p,"Pagina");
}

void RetiraPaginaWiki(Wiked* wiki, char* pagina)
{
    int p = ProcuraPagina(wiki,pagina); // encontra a posição da página ou -1 caso não exista

    // caso a página não seja encontrada imprime mensagem de erro em lo.txt e aborta a função
    if(p == -1)
    {
        ErroPagInexistente(pagina);
        return;
    }

    ListaRemove(wiki->paginas,p,DestroiPagina); // caso seja encontrada remove a página
}

/*Insere um novo editor na WIKED!
* inputs: a wiki e o nome do editor
* outputs: nenhum
* pre-condição: wiki e editor válidos
* pos-condição: wiki contem o editor
*/
void InsereEditorWiki(Wiked* wiki, char* editor);

/*Retira um editor da WIKED!
* inputs: a wiki e o nome do editor
* outputs: nenhum
* pre-condição: wiki e editor válidos
* pos-condição: wiki não contem o editor e suas contribuições
*/
void RetiraEditorWiki(Wiked* wiki, char* editor);

/*Insere uma contribuição numa página e num editor da WikED!
* inputs: a wiki, nome da página, nome do editor e nome da contribuição
* outputs: nenhum
* pre-condição: wiki, página, editor e contribuição válidos
* pos-condição: página e editor contêm a contribuição
*/
void InsereContribuicaoWiki(Wiked* wiki, char* pagina, char* editor, char* arquivo);

/*Retira uma contribuição de uma página da WIKED!
* inputs: a wiki, nome da página, nome do editor e o nome do arquivo
* outputs: nenhum
* pre-condição: wiki, página, editor e contribuição válidos
* pos-condição: contribuição recebe estado "removido"
*/
void RetiraContribuicaoWiki(Wiked* wiki, char* pagina, char* editor, char* arquivo);

/*Insere um link entre páginas
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: link existe na página origem e aponta para a página destino
*/
void InsereLinkWiki(Wiked* wiki, char* origem, char* destino);

/*Retira um link de uma página
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: origem não contem link para destino
*/
void RetiraLinkWiki(Wiked* wiki, char* origem, char* destino);

/*Verifica se há um link entre duas páginas (resposta impressa no arquivo log.txt)
* inputs: wiki, nome da página origem e nome da página destino
* outputs: nenhum
* pre-condição: wiki e páginas válidas
* pos-condição: nenhum
*/
void CaminhoWiki(Wiked* wiki, char* origem, char* destino);

/*Imprime uma página num arquivo .txt
* inputs: wiki e nome da página
* outputs: nenhum
* pre-condição: wiki e página válidos
* pos-condição: nenhum
*/
void ImprimePaginaWiki(Wiked* wiki, char* pagina);

/*Imprime todas as páginas da WIKED!
* inputs: a wiki
* outputs: nenhum
* pre-condição: wiki válida
* pos-condição: nenhum
*/
void ImprimeWiked(Wiked* wiki);

/*Libera toda memoria alocada na WIKED!
* inputs: a wiki com ponteiro genérico
* outputs: nenhum
* pre-condição: wiki não nula
* pos-condição: toda memória liberada
*/
void destroiWiked(void* wiki)
{
    // convertendo para tipo Wiked
    Wiked *w = (Wiked*) wiki;

    // liberando as listas
    DestroiLista(w->paginas,DestroiPagina);
    DestroiLista(w->editores,DestroiEditor);

    // liberando o struct
    free(w);
}

//Verifica se uma página já existe e retorna sua posição
static int ProcuraPagina(Wiked* wiki,char* pagina)
{
    // se a lista estiver vazia retorna -1 (página não encontrada)
    if(ListaVazia(wiki->paginas))
    {
        return (-1);
    }

    Pagina *p; // definindo ponteiro de busca

    // para cada página na lista, verifica se seu nome eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(wiki->paginas) ; i++)
    {
        p = (Pagina*) AchaItem(wiki->paginas,i);

        if(p != NULL)
        {
            if(strcmp(p->nome,pagina) == 0)
            {
                 return i;
            }
        }
    }

    return (-1); // caso não encontrada retorna -1
}

//insere um conteudo numa lista generica
static void Push(Lista* lista, void* conteudo, const char* tipo)
{
    Item *item = NovoItem(tipo,conteudo); // definindo o item
    ListaAdd(lista,item);                 // inserindo o item
}
