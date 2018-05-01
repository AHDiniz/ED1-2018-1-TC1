/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

pagina.c: implementações para páginas
********************************************/

#include "pagina.h"

// Implementação da Página:
struct tipoPagina
{
    char* nomePagina; // O nome da página
    char* enderecoArq;  // O endereço do arquivo da página
    Lista* listaContrb; // Lista de contribuições
    Lista* listaLinks; // Lista de links para outras páginas
};

// Criando uma nova página:
Pagina* InicializaPagina(const char* pagina, const char* arquivo)
{
    Pagina* p = (Pagina*)malloc(sizeof(Pagina)); // Alocando espaço para a estrutura da página
    p->nomePagina = (char*)malloc(strlen(pagina) + 1); // Alocando espaço para o nome da página
    strcpy(p->nomePagina, pagina); // Dando um valor para o nome da página
    p->enderecoArq = (char *)malloc(strlen(arquivo) + 1); // Alocando espaço para o endereço do arquivo da página
    strcpy(p->enderecoArq, arquivo); // Dando um valor para o endereço do arquivo da página
    p->listaContrb = NovaLista("Contribuicao"); // Criando uma nova lista de contribuições
    p->listaLinks = NovaLista("char*"); // Criando uma nova lista de strings (que representam os links para outras páginas)
    return p;
}

// Inserindo um link na lista de links:
void InsereLink(Pagina* origem, Pagina* destino)
{
    if (!Caminho(origem, destino)) // O item será adicionado se ele ainda não estivar na lista
    {
        Item* linkItem = NovoItem("char*", destino->nomePagina); // Criando um novo item para a lista
        ListaAdd(origem->listaLinks, linkItem); // Adicionando o link na lista
    }
    else
        printf("Já existe link entre %s e %s.", origem->nomePagina, destino->nomePagina); // Mesagem de erro
}

// Retirando um link da lista de links:
void RetiraLink(Pagina* origem, Pagina* destino)
{
    if (Caminho(origem, destino)) // Se existe link entre as páginas:
        for (int i = 0; i < TamanhoLista(origem->listaLinks); i++) // Varrendo cada item da lista de links
            if (strcmp(ConteudoItem(AchaItem(origem->listaLinks, i)), destino->nomePagina) == 0) // Se o item for igual ao nome da página destino...
                ListaRemove(origem->listaLinks, i, free); // O item será removido
    else
        printf("Nao ha link entre %s e %s para ser removido.", origem->nomePagina, destino->nomePagina); // Mensagem de erro
}

// Verificando se existe link entre páginas:
int Caminho(Pagina *origem, Pagina *destino)
{
    int i; // Variável de incrementação
    for (i = 0; i < TamanhoLista(origem->listaLinks); i++) // Loop para comparar cada item da lista de links com o nome da outra página
        if (strcmp(ConteudoItem(AchaItem(origem->listaLinks, i)), destino->nomePagina) == 0) // Comparando o nome da página com o conteúdo do item
            return 1; // Se o nome da página de destino estiver na lista, então há um caminho (TRUE)
    return 0; // Caso o nome da página do destino não esteja na lista, não há caminho (FALSE)
}

// Imprimindo a página num arquivo de texto:
void ImprimePagina(Pagina* pagina)
{
    FILE* output; // Arquivo de sáida
    int i; // Variável de incrementação
    output = fopen(pagina->enderecoArq, "w"); // Abrindo o arquivo
    if (!output)
    {
        printf("Arquivo nao encontrado.\n"); // Mensagem de erro
        return;
    }
    fprintf(output, "Pagina %s\n", pagina->nomePagina); // Imprimindo o nome da página
    // Imprimindo as contribuições:
    fprintf(output, "Lista de Contribuicoes: ");
    for (i = 0; i < TamanhoLista(pagina->listaContrb); i++)
        if (ContribuicaoEstado(ConteudoItem(AchaItem(pagina->listaContrb, i))))
            fprintf(output, "%s, ", ContribuicaoEditor(ConteudoItem(AchaItem(pagina->listaContrb, i))));
        else
            fprintf(output, "%s(retirada), ", ContribuicaoEditor(ConteudoItem(AchaItem(pagina->listaContrb, i))));
    // Imprimindo os links:
    fprintf(output, "\nLista de links: ");
    for (i = 0; i < TamanhoLista(pagina->listaLinks); i++)
        fprintf(output, "%s, ", ConteudoItem(AchaItem(pagina->listaLinks, i)));
    // Imprimindo os textos:
    fprintf(output, "\nTextos:");
    for (i = 0; i < TamanhoLista(pagina->listaContrb); i++)
        if (ContribuicaoEstado(ConteudoItem(AchaItem(pagina->listaContrb, i))))
            fprintf(output, "%s, ", ContribuicaoPagina(ConteudoItem(AchaItem(pagina->listaContrb, i))));
    if (fclose(output) != 0)
        printf("Nao foi possivel fechar o arquivo texto.\n"); // Mensagem de erro
}

// Inserindo contribuição na página:
void InsereContribuicaoPagina(Pagina* pagina, Contribuicao* contribuicao)
{
    // Verificando se o item já está na lista:
    for (int i = 0; i < TamanhoLista(pagina->listaContrb); i++)
        if (ConteudoItem(AchaItem(pagina->listaContrb, i)) == contribuicao)
            {
                printf("A contribuicao ja esta na pagina."); // Mensagem de erro
                return;
            }
    Item* contrbItem = NovoItem("Contribuicao", contribuicao); // Criando um novo item para ser inserido na lista
    ListaAdd(pagina->listaContrb, contrbItem); // Adicionando um item na lista
}

// Retornando o nome da página:
char* PaginaNome(Pagina *pagina)
{
    char* ret = (char*)malloc(strlen(pagina->nomePagina + 1));
    free(pagina->nomePagina);
    return ret;
}

// Retornando o endereço do arquivo da página:
char* PaginaArquivo(Pagina* pagina)
{
    char *ret = (char *)malloc(strlen(pagina->enderecoArq + 1));
    free(pagina->enderecoArq);
    return ret;
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
void DestroiPagina(Pagina* pagina)
{
    free(pagina->nomePagina); // Liberando o espaço para o nome da página
    free(pagina->enderecoArq); // Liberando o espaço para o endereço da página
    DestroiLista(pagina->listaContrb, DestroiContribuicao); // Destruindo a lista de contribuições
    DestroiLista(pagina->listaLinks, free); // Destruindo a lista de links
    free(pagina); // Liberando espaço reservado para a página
}