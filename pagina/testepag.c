#include <stdio.h>
#include "pagina.h"
#include "../lista/lista.h"
#include "../contribuicao/contribuicao.h"

int main(void)
{
    Pagina *pagina1 = InicializaPagina("Pagina1", "pagina1.txt");
    Pagina *pagina2 = InicializaPagina("Pagina2", "pagina2.txt");
    Contribuicao *c1 = InicializaContribuicao("Pagina1","editor","c1.txt");
    Contribuicao *c2 = InicializaContribuicao("Pagina1","editor","c2.txt");
    Contribuicao *c3 = InicializaContribuicao("Pagina2","editor","c3.txt");
    int i;

    InsereContribuicaoPagina(pagina1,c1);
    InsereContribuicaoPagina(pagina1,c2);
    InsereContribuicaoPagina(pagina2,c3);
    InsereContribuicaoPagina(pagina1,c1);

    Contribuicao *aux;

    printf("#1\nNome: %s\nArquivo: %s\n", PaginaNome(pagina1), PaginaArquivo(pagina1));
    for(i = 0 ; i < TamanhoLista(ListaContrbPagina(pagina1)) ; i++)
    {
        aux = (Contribuicao*) AchaItem(ListaContrbPagina(pagina1), i);
        printf("Cont %d: %s\n", i, ContribuicaoArquivo(aux));
    }

    printf("\n#2\nNome: %s\nArquivo: %s\n", PaginaNome(pagina2), PaginaArquivo(pagina2));
    for(i = 0 ; i < TamanhoLista(ListaContrbPagina(pagina2)) ; i++)
    {
        aux = (Contribuicao*) AchaItem(ListaContrbPagina(pagina2), i);
        printf("Cont %d: %s\n", i, ContribuicaoArquivo(aux));
    }

    //ImprimePagina(pagina1);
    //ImprimePagina(pagina2);

    DestroiPagina((void**) &pagina1);
    DestroiPagina((void**) &pagina2);

    return 0;
}