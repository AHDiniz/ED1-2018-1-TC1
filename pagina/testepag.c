#include <stdio.h>
#include "pagina.h"
#include "../lista/lista.h"
#include "../contribuicao/contribuicao.h"

void PrintPagina(Pagina*);

int main(void)
{
    Pagina *pagina1 = InicializaPagina("Pagina1", "pagina1.txt");
    Pagina *pagina2 = InicializaPagina("Pagina2", "pagina2.txt");
    Contribuicao *c1 = InicializaContribuicao("Pagina1","editor","c1.txt");
    Contribuicao *c2 = InicializaContribuicao("Pagina1","editor","c2.txt");
    Contribuicao *c3 = InicializaContribuicao("Pagina2","editor","c3.txt");

    InsereContribuicaoPagina(pagina1,c1);
    InsereContribuicaoPagina(pagina1,c2);
    InsereContribuicaoPagina(pagina2,c3);

    PrintPagina(pagina1);
    PrintPagina(pagina2);

    InsereLink(pagina1,pagina2);
    InsereLink(pagina2,pagina1);

    PrintPagina(pagina1);
    PrintPagina(pagina2);

    printf("\nCaminho p1-p2: %d\nCaminho p2-p1: %d\n", Caminho(pagina1,pagina2), Caminho(pagina2,pagina1));

    RetiraLink(pagina2,pagina1);

    PrintPagina(pagina1);
    PrintPagina(pagina2);
    
    ImprimePagina(pagina1);
    ImprimePagina(pagina2);

    DestroiPagina(pagina1);
    DestroiPagina(pagina2);

    return 0;
}

void PrintPagina(Pagina* pagina)
{
    int i;
    Contribuicao *aux;
    Pagina *aux2;

    printf("\nNome: %s\nArquivo: %s\n", PaginaNome(pagina), PaginaArquivo(pagina));
    for(i = 0 ; i < TamanhoLista(ListaContrbPagina(pagina)) ; i++)
    {
        aux = (Contribuicao*) AchaItem(ListaContrbPagina(pagina), i);
        printf("Cont %d: %s\n", i, ContribuicaoArquivo(aux));
    }
    for(i = 0 ; i < TamanhoLista(ListaLinksPagina(pagina)) ; i++)
    {
        aux2 = (Pagina*) AchaItem(ListaLinksPagina(pagina), i);
        printf("Link %d:\nPag Nome: %s\nPag Arq: %s\n", i, PaginaNome(aux2), PaginaArquivo(aux2));
    }
}