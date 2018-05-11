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

    // para cada página na lista, verifica se seu nome eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(wiki->paginas) ; i++)
    {
        p = (Pagina*) AchaItem(wiki->paginas,i); // atualizando ponteiro de busca

        if(p != NULL) // medida de segurança
        {
            if(strcmp( PaginaNome(p),pagina) == 0) // compara nome do ponteiro de busca com nome da página
            {
                return i;   // retorna posição
            }
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

    // para cada página na lista, verifica se seu nome eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(wiki->editores) ; i++)
    {
        e = (Editor*) AchaItem(wiki->editores,i); // atualizando ponteiro de busca

        if(e != NULL) // medida de segurança
        {
            if(strcmp( EditorNome(e),editor) == 0) // compara nome do ponteiro de busca com nome do editor
            {
                return i;   // retorna a posição
            }
        }
    }

    return (-1); // caso não encontrada retorna -1
}

// verifica se uma contribuição ja existe numa página e retorna sua posição
static int ProcuraContribuicaoPagina(Pagina* pagina ,char* arquivo)
{
    Lista *conts = ListaContrbPagina(pagina);

    // se a lista estiver vazia retorna -1 (contribuição não encontrada)
    if(ListaVazia(conts))
    {
        return (-1);
    }

    Contribuicao *c; // definindo ponteiro de busca

    // para cada contribuição na lista, verifica se seu arquivo eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(conts) ; i++)
    {
        c = (Contribuicao*) AchaItem(conts,i); // atualizando ponteiro de busca

        if(c != NULL) // medida de segurança
        {
            if(strcmp( ContribuicaoArquivo(c),arquivo) == 0) // compara nome do ponteiro de busca com nome da contribuição
            {
                return i;   // retorna a posição
            }
        }
    }

    return (-1); // caso não encontrada retorna -1
}

// verifica se uma contribuição ja existe num editor e retorna sua posição
static int ProcuraContribuicaoEditor(Editor* editor ,char* arquivo)
{
    Lista *conts = EditorContribuicoes(editor);

    // se a lista estiver vazia retorna -1 (contribuição não encontrada)
    if(ListaVazia(conts))
    {
        return (-1);
    }

    Contribuicao *c; // definindo ponteiro de busca

    // para cada contribuição na lista, verifica se seu arquivo eh igual ao procurado. Caso sim retorna sua posição
    for(i = 0 ; i < TamanhoLista(conts) ; i++)
    {
        c = (Contribuicao*) AchaItem(conts,i); // atualizando ponteiro de busca

        if(c != NULL) // medida de segurança
        {
            if(strcmp( ContribuicaoArquivo(c),arquivo) == 0) // compara nome do ponteiro de busca com nome da contribuição
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

/**************************************************/

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

    Pagina *aux; // auxiliar de busca
    Pagina *pag = (Pagina*) AchaItem(wiki->paginas,posicao); // página que sera retirada

    // removendo os links que levem à página
    for(i = 0 ; i < TamanhoLista(wiki->paginas) ; i++)
    {
        aux = (Pagina*) AchaItem(wiki->paginas, i);
        if(Caminho(aux,pag))
        {
            RetiraLink(aux,pag);
        }
    }

    // removendo as contribuições da página de seus respectivos editores
    Lista *listaCont = ListaContrbPagina(pag); // buscando a lista de contribuições da página
    char *nomeCont; // auxiliar que guarda o nome do arquivo da contribuição
    char *nomeEdit; // auxiliar que guarda o nome do editor da contribuição
    Editor *editor; // auxiliar que guarda o editor da contribuição

    for(i = 0 ; i < TamanhoLista(listaCont) ; i++) // para cada contribuição na lista
    {
        nomeCont = ContribuicaoArquivo( (Contribuicao*) AchaItem(listaCont, i)); // busca o nome de seu arquivo
        nomeEdit = ContribuicaoEditor( (Contribuicao*) AchaItem(listaCont, i)); // busca o nome de seu editor
        editor = (Editor*) AchaItem(wiki->editores, ProcuraEditor(wiki, nomeEdit)); // busca o editor com o nome encontrado

        ListaRemove(EditorContribuicoes(editor), ProcuraContribuicaoEditor(editor, nomeCont), NULL); // remove da lista de contribuições do editor o Item da contribuição (sem libera-la)
    }

    ListaRemove(wiki->paginas,posicao,DestroiPagina); // remove a página, liberando todas as suas contribuições
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

    // removendo as contribuições do editor de suas respectivas páginas
    Lista *listaCont = EditorContribuicoes((Editor*) AchaItem(wiki->editores,posicao)); // buscando a lista de contribuições do editor
    char *nomeCont; // auxiliar que guarda o nome do arquivo da contribuição
    char *nomePag; // auxiliar que guarda o nome da página da contribuição
    Pagina *pagina; // auxiliar que guarda a página da contribuição

    for(i = 0 ; i < TamanhoLista(listaCont) ; i++) // para cada contribuição na lista
    {
        nomeCont = ContribuicaoArquivo( (Contribuicao*) AchaItem(listaCont, i)); // busca o nome de seu arquivo
        nomePag = ContribuicaoPagina( (Contribuicao*) AchaItem(listaCont, i)); // busca o nome de sua página
        pagina = (Pagina*) AchaItem(wiki->paginas, ProcuraPagina(wiki, nomePag)); // busca a página com o nome encontrado

        ListaRemove(ListaContrbPagina(pagina), ProcuraContribuicaoPagina(pagina, nomeCont), NULL); // remove da lista de contribuições da página o Item da contribuição (sem libera-la)
    }

    ListaRemove(wiki->editores,posicao,DestroiEditor); // remove o editor, liberando todas as suas contribuições
}

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

    // buscando página e editor
    Pagina *pag = (Pagina*) AchaItem(wiki->paginas,posicaoPag);
    Editor *ed =  (Editor*) AchaItem(wiki->editores,posicaoEd);

    // verifica se a contribuição já pertence à página
    if(ProcuraContribuicaoPagina(pag,arquivo) == -1)
    {
        ErroContExiste(arquivo);
        return;
    }

    // verifica se a contribuição já pertence ao editor
    if(ProcuraContribuicaoEditor(ed,arquivo) == -1)
    {
        ErroContExiste(arquivo);
        return;
    }

    // inicializando a contribuição
    Contribuicao *cont = InicializaContribuicao(pagina,editor,arquivo);

    // inserindo a contribuição na página
    InsereContribuicaoPagina(pag,cont);

    // inserindo contribuição no editor
    InsereContribuicaoEditor(ed,cont);
}

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
    int posicaoCont = ProcuraContribuicaoPagina(pag,arquivo);

    // verifica se existe a contribuição na página fornecida
    if(posicaoCont == -1)
    {
        ErroContInexistente(arquivo,pagina); // caso não, será exibido mensagem de erro em log.txt
        return;                              // e a função sera abortada
    }

    // buscando a contribuição
    Contribuicao *cont = (Contribuicao*) AchaItem(pag,posicaoCont);

    // verificando o editor da contribuição
    if( strcmp( ContribuicaoEditor(cont), editor) != 0)
    {
        ErroEdtIncorreto(editor); // caso incorreto, será exibido mensagem de erro em log.txt
        return;                   // e a função sera abortada
    }

    // retirando a contribuição
    RetiraContribuicao(cont);
}

void InsereLinkWiki(Wiked* wiki, char* origem, char* destino)
{
    // buscando as posições da página origem e destino
    int posicaoOrigem = ProcuraPagina(wiki,origem);
    int posicaoDestino = ProcuraPagina(wiki,destino);

    // verifica se existe a página origem
    if(posicaoOrigem == -1)
    {
        ErroPagInexistente(origem); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se existe a página destino
    if(posicaoDestino == -1)
    {
        ErroPagInexistente(destino); // caso não, será exibida mensagem de erro em log.txt
        return;                      // e a função sera abortada
    }

    // buscando as paginas
    Pagina *o = (Pagina*) AchaItem(wiki->paginas,posicaoOrigem);
    Pagina *d = (Pagina*) AchaItem(wiki->paginas,posicaoDestino);

    // verifica se já existe um link entre as páginas
    if(Caminho(o,d))
    {
        ErroLinkExiste(origem,destino); // caso sim, será exibida mensagem de erro em log.txt
        return;                         // e a função sera abortada
    }

    // inserindo link
    InsereLink(o,d);
}

void RetiraLinkWiki(Wiked* wiki, char* origem, char* destino)
{
    // buscando as posições da página origem e destino
    int posicaoOrigem = ProcuraPagina(wiki,origem);
    int posicaoDestino = ProcuraPagina(wiki,destino);

    // verifica se existe a página origem
    if(posicaoOrigem == -1)
    {
        ErroPagInexistente(origem); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se existe a página destino
    if(posicaoDestino == -1)
    {
        ErroPagInexistente(destino); // caso não, será exibida mensagem de erro em log.txt
        return;                      // e a função sera abortada
    }

    // buscando as paginas
    Pagina *o = (Pagina*) AchaItem(wiki->paginas,posicaoOrigem);
    Pagina *d = (Pagina*) AchaItem(wiki->paginas,posicaoDestino);

    // verifica se existe um link entre as páginas
    if(Caminho(o,d) == 0)
    {
        ErroLinkInexistente(origem,destino); // caso não, será exibida mensagem de erro em log.txt
        return;                              // e a função sera abortada
    }

    // removendo o link
    RetiraLink(o,d);
}

void CaminhoWiki(Wiked* wiki, char* origem, char* destino)
{
    // buscando as posições da página origem e destino
    int posicaoOrigem = ProcuraPagina(wiki,origem);
    int posicaoDestino = ProcuraPagina(wiki,destino);

    // verifica se existe a página origem
    if(posicaoOrigem == -1)
    {
        ErroPagInexistente(origem); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // verifica se existe a página destino
    if(posicaoDestino == -1)
    {
        ErroPagInexistente(destino); // caso não, será exibida mensagem de erro em log.txt
        return;                      // e a função sera abortada
    }

    // buscando as paginas
    Pagina *o = (Pagina*) AchaItem(wiki->paginas,posicaoOrigem);
    Pagina *d = (Pagina*) AchaItem(wiki->paginas,posicaoDestino);

    // verificando e imprimindo resposta em log.txt
    CaminhoResposta( Caminho(o,d), origem, destino);
}

void ImprimePaginaWiki(Wiked* wiki, char* pagina)
{
    // buscando a posição da página
    int posicao = ProcuraPagina(wiki,pagina);

    // verifica se existe a página especificada
    if(posicao == -1)
    {
        ErroPagInexistente(pagina); // caso não, será exibida mensagem de erro em log.txt
        return;                     // e a função sera abortada
    }

    // buscando a pagina
    Pagina *pag = (Pagina*) AchaItem(wiki->paginas,posicao);

    // imprimindo a página
    ImprimePagina(pag);
}

void ImprimeWiked(Wiked* wiki)
{
    // verifica se a lista de páginas está vazia
    if(ListaVazia(wiki->paginas))
    {
        ErroWikiVazia(); // caso sim, exibe mensagem de erro em log.txt
        return;          // e aborta a função
    }

    // imprimindo cada página da wiki
    for(i = 0 ; i < TamanhoLista(wiki->paginas) ; i++) // para cada posição na lista
    {
        ImprimePagina( (Pagina*) AchaItem(wiki->paginas,i) ); // imprime o objeto da posição
    }
}

void destroiWiked(void* wiki)
{
    // convertendo para tipo Wiked
    Wiked *w = (Wiked*) wiki;

    // liberando as listas
    DestroiLista(w->paginas,DestroiPagina);
    DestroiLista(w->editores,DestroiEditor2);

    // liberando o struct
    free(w);
}
