#include <stdio.h>
#include <stdlib.h>
#include "contribuicao.h"

int main()
{
    char *pagina = "pagina";
    char *editor = "editor";
    char *arquivo = "arquivo.txt";

    Contribuicao *cont = InicializaContribuicao(pagina,editor,arquivo);

    char *pag = ContribuicaoPagina(cont);
    char *ed = ContribuicaoEditor(cont);
    char *arq = ContribuicaoArquivo(cont);

    printf("Imprimindo contribuicao:\nPagina: %s\nEditor: %s\nArquivo: %s\nEstado: %d\n\n", pag, ed, arq, ContribuicaoEstado(cont));

    RetiraContribuicao(cont);

    printf("Imprimindo contribuicao:\nPagina: NULL\nEditor: NULL\nArquivo: %s\nEstado: %d\n\n", arq, ContribuicaoEstado(cont));

    DestroiContribuicao((void**) &cont);

    if(cont == NULL)
    {
        printf("cont liberado");
    }

    return 0;
}