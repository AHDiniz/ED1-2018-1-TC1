/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

pagina.c: implementações para páginas
********************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pagina.h"

// Implementação da Página:
struct tipoPagina
{
    char* nomePagina; // O nome da página
    char* enderecoArq;  // O endereço do arquivo da página
    Lista* listaContrb; // Lista de contribuições
    Lista* listaLinks; // Lista de links para outras páginas
};

// Auxiliar que insere um conteudo numa lista generica
static void Push(Lista* lista, void* conteudo, const char* tipo)
{
    Item *item = NovoItem(tipo,conteudo); // definindo o item
    ListaAdd(lista,item);                 // inserindo o item
}

// Auxiliar que verifica se uma string pertence a uma lista de strings
static int PertenceListaString(Lista* lista, char* string)
{
    int i; // variável de incrementação

    for(i = 0 ; i< TamanhoLista(lista) ; i++) // varrendo a lista
    {
        if( strcmp((char*) AchaItem(lista,i),string) == 0) // comparando inteiro na lista com num
        {
            return 1; // caso encontrado retorna 1
        }
    }

    return 0; // caso contrário retorna 0
}

// Criando uma nova página:
Pagina* InicializaPagina(const char* pagina, const char* arquivo)
{
    Pagina* p = (Pagina*)malloc(sizeof(Pagina)); // Alocando espaço para a estrutura da página
    p->nomePagina = (char*)malloc(strlen(pagina) + 1); // Alocando espaço para o nome da página
    strcpy(p->nomePagina, pagina); // Dando um valor para o nome da página
    p->enderecoArq = (char *)malloc(strlen(arquivo) + 1); // Alocando espaço para o endereço do arquivo da página
    strcpy(p->enderecoArq, arquivo); // Dando um valor para o endereço do arquivo da página
    p->listaContrb = NovaLista("Contribuicao"); // Criando uma nova lista de contribuições
    p->listaLinks = NovaLista("Pagina"); // Criando uma nova lista de strings (que representam os links para outras páginas)
    return p;
}

// Inserindo um link na lista de links:
void InsereLink(Pagina* origem, Pagina* destino)
{
    if (!VerificaLink(origem, destino)) // O item será adicionado se ele ainda não estivar na lista
    {
        Item* linkItem = NovoItem("Pagina", destino); // Criando um novo item para a lista
        ListaAdd(origem->listaLinks, linkItem); // Adicionando o link na lista
    }
    else
        printf("Já existe link entre %s e %s.", origem->nomePagina, destino->nomePagina); // Mesagem de erro
}

// Retirando um link da lista de links:
void RetiraLink(Pagina* origem, Pagina* destino)
{
    if (VerificaLink(origem, destino)) // Se existe link entre as páginas:
        for (int i = 0; i < TamanhoLista(origem->listaLinks); i++) // Varrendo cada item da lista de links
            if (AchaItem(origem->listaLinks, i) == destino) // Se o item for igual ao nome da página destino...
                ListaRemove(origem->listaLinks, i, NULL); // O item será removido
    else
        printf("Nao ha link entre %s e %s para ser removido.", origem->nomePagina, destino->nomePagina); // Mensagem de erro
}

int VerificaLink(Pagina* origem, Pagina* destino)
{
    int i; // Variável de incrementação
    Pagina *pag;

    for (i = 0; i < TamanhoLista(origem->listaLinks); i++) // Loop para comparar cada item da lista de links com o nome da outra página
    {
        pag = (Pagina*) AchaItem(origem->listaLinks, i);
        if (pag == destino) // Comparando o nome da página com o conteúdo do item
            return 1; // Se o nome da página de destino estiver na lista, então há um link (TRUE)
    }
    return 0; // Caso o nome da página do destino não esteja na lista, não há link (FALSE)
}

// Verificando se existe caminho entre páginas:
int Caminho(Pagina *origem, Pagina *destino)
{
    int i; // Variável de incrementação
    Pagina *pag; // auxiliar de busca
    Pagina *link; // auxiliar de busca
    Lista *fila = NovaLista("Pagina*"); // auxiliar que guarda as páginas que ainda serão analizadas
    Lista *verificados = NovaLista("char*"); // auxiliar que guarda as páginas que já foram analizadas

    Push(fila,origem,"Pagina*"); // inicializando fila

    do
    {
        pag = (Pagina*) AchaItem(fila,0); // buscando o inicio da fila

        for(i = 0 ; i < TamanhoLista(pag->listaLinks) ; i++) // varrendo sua lista de links
        {
            link = (Pagina*) AchaItem(pag->listaLinks,i); // buscando a pagina apontada por cada link

            if(link == destino) // se a página apontada for o destino
            {
                // liberam-se as listas
                DestroiLista(fila,NULL); // liberando lista 'fila'
                DestroiLista(verificados,NULL); // liberando lista 'verificados'
                // e retorna 1 (há caminho, TRUE)
                return 1;
            }

            if(!PertenceListaString(verificados,link->nomePagina)) // caso contrario, verifica se já foi/será analizada
            {
                Push(verificados,link->nomePagina,"char*"); // caso não, marca como analizada adicionando a lista 'verificados'
                Push(fila,link,"Pagina*");                  // e adiciona a fila
            }
        }

        ListaRemove(fila,0,NULL); // removendo o item já analizado da fila

    }while(!ListaVazia(fila)); // repete-se até a fila estar vazia, ou seja, todos os links serem analizados

    DestroiLista(fila,NULL); // liberando lista 'fila'
    DestroiLista(verificados,NULL); // liberando lista 'verificados'

    return 0; // Caso o nome da página do destino não esteja na lista, não há caminho (FALSE)
}

// Imprimindo a página num arquivo de texto:
void ImprimePagina(Pagina* pagina)
{
    FILE *output; // Arquivo de sáida
    FILE *contArq; // Arquivo auxiliar
    int chr; // Variável auxiliar de impressão
    int i; // Variável de incrementação
    Contribuicao *cont; // Variável auxiliar
    Pagina *pag; // Variável auxiliar
    output = fopen(pagina->enderecoArq, "w"); // Abrindo o arquivo
    if (!output)
    {
        printf("Nao foi possivel abrir o arquivo.\n"); // Mensagem de erro
        return;
    }
    fprintf(output, "%s\n", pagina->nomePagina); // Imprimindo o nome da página
    // Imprimindo o hístorico de contribuições:
    fprintf(output, "\n--> Historico de contribuicoes:\n");
    for (i = 0; i < TamanhoLista(pagina->listaContrb); i++) // para cada contribuição na página
    {
        cont = (Contribuicao*) AchaItem(pagina->listaContrb, i); // encontra a contribuição
        if (ContribuicaoEstado(cont)) // se não removida
        {
            fprintf(output, "%s %s\n", ContribuicaoEditor(cont), ContribuicaoArquivo(cont)); // imprime seu editor e seu nome
        }
        else // caso removida
        {
            fprintf(output, "%s %s <<retirada>>\n", ContribuicaoEditor(cont), ContribuicaoArquivo(cont)); // imprime explicitando a retirada
        }
    }
    // Imprimindo os links:
    fprintf(output, "\n--> Lista de links:\n");
    for (i = 0; i < TamanhoLista(pagina->listaLinks); i++) // para cada link
    {
        pag = (Pagina*) AchaItem(pagina->listaLinks, i); // busca a página linkada
        fprintf(output, "%s %s\n", pag->nomePagina, pag->enderecoArq); // e imprime seu nome e arquivo 
    }
    // Imprimindo os textos:
    fprintf(output, "\n--> Textos:");
    for (i = 0; i < TamanhoLista(pagina->listaContrb); i++) // para cada cotribuição
    {
        cont = (Contribuicao*) AchaItem(pagina->listaContrb, i); // buscando a contribuição
        if (ContribuicaoEstado(cont)) // se não foi removida
        {
            contArq = fopen(ContribuicaoArquivo(cont), "r"); // abre seu arquivo
            fprintf(output, "\n\n-------- %s (%s) --------\n\n", ContribuicaoArquivo(cont), ContribuicaoEditor(cont)); // imprime seu arquivo e editor

            chr = getc(contArq); // inicializando o auxiliar

            while(!feof(contArq)) // enquanto não alcançar o fim do arquivo
            {
                fputc(chr, output); // imprime o auxiliar
                chr = getc(contArq); // e atualiza o auxiliar
            }

            fclose(contArq); // fechando o arquivo da contribuição
        }
    }
    if (fclose(output) != 0) // fechando o arquivo da página
        printf("Nao foi possivel fechar o arquivo texto.\n"); // Mensagem de erro
}

// Inserindo contribuição na página:
void InsereContribuicaoPagina(Pagina* pagina, Contribuicao* contribuicao)
{
    /*
    // Verificando se o item já está na lista:
    for (int i = 0; i < TamanhoLista(pagina->listaContrb); i++)
        if ( !strcmp(ContribuicaoArquivo( (Contribuicao*) ConteudoItem(AchaItem(pagina->listaContrb, i))), ContribuicaoArquivo(contribuicao)))
            {
                printf("A contribuicao ja esta na pagina.\n"); // Mensagem de erro
                return;
            }
    */
    Item *contrbItem = NovoItem("Contribuicao", contribuicao); // Criando um novo item para ser inserido na lista
    ListaAdd(pagina->listaContrb, contrbItem); // Adicionando um item na lista
}

// Retornando o nome da página:
char* PaginaNome(Pagina *pagina)
{
    return pagina->nomePagina;
}

// Retornando o endereço do arquivo da página:
char* PaginaArquivo(Pagina* pagina)
{
    return pagina->enderecoArq;
}

// Retorno da lista de contribuições:
Lista* ListaContrbPagina(Pagina* pagina)
{
    return pagina->listaContrb;
}

// Retorno da lista de contribuições:
Lista *ListaLinksPagina(Pagina *pagina)
{
    return pagina->listaLinks;
}

// Destruindo a página:
void DestroiPagina(void* pagina)
{
    Pagina *pag = (Pagina*) pagina;

    free(pag->nomePagina); // Liberando o espaço para o nome da página
    free(pag->enderecoArq); // Liberando o espaço para o endereço da página
    DestroiLista(pag->listaLinks, NULL); // Destruindo a lista de links
    DestroiLista(pag->listaContrb, DestroiContribuicao); // Destruindo a lista de contribuições
    free(pag); // Liberando espaço reservado para a página
}
