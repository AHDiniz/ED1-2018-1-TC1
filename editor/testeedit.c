#include <stdio.h>
#include "editor.h"
#include "../contribuicao/contribuicao.h"
#include "../lista/lista.h"

static void ImprimeConts(Editor* editor, int tam);

int main()
{
    Editor *editor = InicializaEditor("editor");
    Contribuicao *cont1 = InicializaContribuicao("pag","editor","cont1.txt");
    Contribuicao *cont2 = InicializaContribuicao("pag","editor","cont2.txt");
    Contribuicao *cont3 = InicializaContribuicao("pag","editor","cont3.txt");

    int tam = TamanhoLista( EditorContribuicoes(editor) );
    printf("Editor = %s\nContribuicoes:\n", EditorNome(editor));
    ImprimeConts(editor,tam);

    InsereContribuicaoEditor(editor,cont1);
    InsereContribuicaoEditor(editor,cont2);
    InsereContribuicaoEditor(editor,cont3);

    tam = TamanhoLista( EditorContribuicoes(editor) );
    printf("Editor = %s\nContribuicoes:\n", EditorNome(editor));
    ImprimeConts(editor,tam);

    DestroiEditor(editor);

    return 0;
}

static void ImprimeConts(Editor* editor, int tam)
{
    int i;

    for(i = 0 ; i < tam ; i++)
    {
        printf("%s\n", ContribuicaoArquivo( (Contribuicao*) AchaItem( EditorContribuicoes(editor), i)) );
    }
    printf("\n");
}