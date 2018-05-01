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
    if(ProcuraPagina(wiki,pagina) >= -1) // verifica se ja existe uma página com esse nome ou se a lista é nula
    {
        ErroPagExiste(pagina); // caso sim, uma mansagem de erro sera exibina em log.txt
        return;                // e a função sera abortada
    }

    // caso contrario, a página sera inserida normalmente
    // inicializando a página
    Pagina *p = InicializaPagina(pagina,arquivo);

    // incluindo pagina na lista
    Push(wiki->paginas,p,"Pagina");
}

void RetiraPaginaWiki(Wiked* wiki, char* pagina)
{
    int posicao = ProcuraPagina(wiki,pagina); // encontra a posição da página ou -1 caso não exista

    // caso a página não seja encontrada imprime mensagem de erro em lo.txt e aborta a função
    if(posicao == -1)
    {
        ErroPagInexistente(pagina);
        return;
    }

    ListaRemove(wiki->paginas,posicao,DestroiPagina); // caso seja encontrada remove a página
}

void InsereEditorWiki(Wiked* wiki, char* editor)
{
    // verifica e já existe um editor com esse nome
    if(ProcuraEditor(wiki,editor) >= -1)
    {
        ErroEdtExiste(editor); // caso sim, será exibida mensagem de erro em log.txt
        return;                // e a função sera abortada
    }

    // caso contrário, o editor será inserido normalmente
    // inicializando editor
    Editor *e = InicializaEditor(editor);

    // inserindo editor na lista
    Push(wiki->editores,e,"Editor");
}

void RetiraEditorWiki(Wiked* wiki, char* editor)
{
    int posicao = ProcuraEditor(wiki,editor); // encontra a posição do editor ou -1 caso não exista

    // caso o editor não seja encontrado imprime mensagem de erro em lo.txt e aborta a função
    if(posicao == -1)
    {
        ErroEdtInexistente(editor);
        return;
    }

    ListaRemove(wiki->editores,posicao,DestroiEditor); // caso seja encontrado remove o editor
}

/*Insere uma contribuição numa página e num editor da WikED!
* inputs: a wiki, nome da página, nome do editor e nome da contribuição
* outputs: nenhum
* pre-condição: wiki, página, editor e contribuição válidos
* pos-condição: página e editor contêm a contribuição
*/
void InsereContribuicaoWiki(Wiked* wiki, char* pagina, char* editor, char* arquivo)
{
    // buscando as posições da página e do editor
    int posicaoPag = ProcuraPagina(wiki,pagina);
    int posicaoEd = ProcuraEditor(wiki,editor);

    // verifica se existe a página especificada
    if(posicaoPag == -1)
    {
        ErroPagInexistente(pagina); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se existe o editor especificado
    if(posicaoEd == -1)
    {
        ErroEdtInexistente(editor); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se o arquivo termina em .txt
    if( ! VerificaTXT(arquivo))
    {
        ErroTXT(); // caso não, será exibido mensagem de erro em log.txt
        return;    // e a função sera abortada
    }

    // inicializando a contribuição
    Contribuicao *cont = InicializaContribuicao(pagina,editor,arquivo);

    // inserindo a contribuição na página
    InsereContribuicaoPagina( AchaItem(wiki->paginas,posicaoPag) , cont );

    // inserindo contribuição no editor
    InsereContribuicaoPagina( AchaItem(wiki->editores,posicaoEd) , cont );
}

/*Retira uma contribuição de uma página da WIKED!
* inputs: a wiki, nome da página, nome do editor e o nome do arquivo
* outputs: nenhum
* pre-condição: wiki, página, editor e contribuição válidos
* pos-condição: contribuição recebe estado "removido"
*/
void RetiraContribuicaoWiki(Wiked* wiki, char* pagina, char* editor, char* arquivo)
{
    // buscando as posições da página e do editor
    int posicaoPag = ProcuraPagina(wiki,pagina);
    int posicaoEd = ProcuraEditor(wiki,editor);

    // verifica se existe a página especificada
    if(posicaoPag == -1)
    {
        ErroPagInexistente(pagina); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se existe o editor especificado
    if(posicaoEd == -1)
    {
        ErroEdtInexistente(editor); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se o arquivo termina em .txt
    if( ! VerificaTXT(arquivo))
    {
        ErroTXT(); // caso não, será exibido mensagem de erro em log.txt
        return;    // e a função sera abortada
    }

    // buscando a página da contribuição
    Pagina *pag = (Pagina*) AchaItem(wiki->paginas,posicaoPag);

    // buscando a posição da contribuição
    int posicaoCont = ProcuraContribuicao(pag,arquivo);

    // verifica se existe a contribuição na página fornecida
    if(posicaoCont == -1)
    {
        ErroContInexistente(arquivo,pagina); // caso não, será exibido mensagem de erro em log.txt
        return;                              // e a função sera abortada
    }

    // buscando a contribuição
    Contribuicao *cont = AchaItem(pag,posicaoCont);

    // verificando o editor da contribuição
    if( strcmp( ContribuicaoEditor(cont), editor) != 0)
    {
        ErroEdtIncorreto(editor); // caso incorreto, será exibido mensagem de erro em log.txt
        return;                   // e a função sera abortada
    }

    // retirando a contribuição
    RetiraContribuicao(cont);
}

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

/****************** AUXILIARES ******************/

//Verifica se uma página já existe e retorna sua posição
static int ProcuraPagina(Wiked* wiki,char* pagina)
{
    // se a lista estiver vazia retorna -1 (página não encontrada)
    if(ListaVazia(wiki->paginas))
    {
        return (-1);
    }

    Pagina *p; // definindo ponteiro de busca
    char *nome; // string auxiliar

    // para cada página na lista, verifica se seu nome eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(wiki->paginas) ; i++)
    {
        p = (Pagina*) AchaItem(wiki->paginas,i); // atualizando ponteiro de busca

        if(p != NULL) // medida de segurança
        {
            nome = PaginaNome(p); // nome de "p"
            if(strcmp(nome,pagina) == 0) // compara nome de "pagina" com nome de "p"
            {
                free(nome); // libera nome
                return i;   // retorna posição
            }
            free(nome); // libera nome
        }
    }

    return (-1); // caso não encontrada retorna -1
}

// Verifica se um editor já existe e retorna sua posição
static int ProcuraEditor(Wiked* wiki, char* editor)
{
    // se a lista estiver vazia retorna -1 (página não encontrada)
    if(ListaVazia(wiki->editores))
    {
        return (-1);
    }

    Editor *e; // definindo ponteiro de busca
    char *nome; // string auxiliar

    // para cada página na lista, verifica se seu nome eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(wiki->editores) ; i++)
    {
        e = (Editor*) AchaItem(wiki->editores,i); // atualizando ponteiro de busca

        if(e != NULL) // medida de segurança
        {
            nome = EditorNome(e);        // nome do editor "e"
            if(strcmp(nome,editor) == 0) // compara nome de "editor" com nome de "e"
            {
                free(nome); // libera nome
                return i;   // retorna a posição
            }
            free(nome); // libera nome
        }
    }

    return (-1); // caso não encontrada retorna -1
}

// verifica se uma contribuição ja existe e retorna sua posição
static int ProcuraContribuicao(Pagina* pagina ,char* arquivo)
{
    Lista *conts = PaginaContribuicoes(pagina);

    // se a lista estiver vazia retorna -1 (contribuição não encontrada)
    if(ListaVazia(conts))
    {
        return (-1);
    }

    Contribuicao *c; // definindo ponteiro de busca
    char *nome; // string auxiliar

    // para cada contribuição na lista, verifica se seu arquivo eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(conts) ; i++)
    {
        c = (Contribuicao*) AchaItem(conts,i); // atualizando ponteiro de busca

        if(c != NULL) // medida de segurança
        {
            nome = ContribuicaoArquivo(c); // nome do arquivo "c"
            if(strcmp(nome,arquivo) == 0) // compara nome de "arquivo" com nome de "c"
            {
                return i;   // retorna a posição
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

// verifica se a string termina em .txt
static int VerificaTXT(char* string)
{
    int tamanho = strlen(string); // numero de caracteres na string

    if(tamanho <= 4) // se houver 4 ou menos caracteres, .txt não eh sufixo
    {
        return 0; // retorno de caráter booleano
    }

    // verifica se os 4 últimos caracteres são .txt
    if(strcmp( string + tamanho -4 ,".txt") == 0)
    {
        return 1; // caso sim, retorno afirmativo
    }

    return 0; // caso contrário o sufixo não eh .txt
}
