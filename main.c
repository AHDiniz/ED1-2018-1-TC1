/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

main.c: ponto de entrada do programa
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wiki/wiki.h"
#define MAXTAM 20

int main(int argc, char* argv[])
{
    FILE *entrada;
    char funcao[MAXTAM]; // auxiliar que guarda a função
    // auxiliares que guardam os argumentos
    char arg1[MAXTAM];
    char arg2[MAXTAM];
    char arg3[MAXTAM];

    entrada = fopen("log.txt", "w"); // inicializando arquivo de log
    fclose(entrada);

    entrada = fopen(argv[1], "r"); // abrindo arquivo de entrada para leitura

    Wiked *wiki = InicializaWiki(); // inicializando a WikED!

    fscanf(entrada, "%s", funcao); // inicializando a primeira função

    while(strcmp(funcao,"FIM")) // loop termina ao encontrar função FIM
    {
        switch(strlen(funcao)) // avalia o tamanho da função para agilizar sua identificação
        {
            case 7: // função CAMINHO
                    fscanf(entrada, " %s %s", arg1, arg2); // lendo os argumentos da função
                    Wiki_Caminho(wiki,arg1,arg2);
                    break;
            
            case 10: // função INSERELINK ou RETIRALINK
                    fscanf(entrada, " %s %s", arg1, arg2); // lendo os argumentos (ambas utilizam dois)
                    if(!strcmp(funcao,"INSERELINK")) // indentificando a função
                    {
                        Wiki_InsereLink(wiki,arg1,arg2);
                    }
                    else
                    {
                        Wiki_RetiraLink(wiki,arg1,arg2);
                    }
                    break;

            case 12: // funções IMPRIMEWIKED, INSEREPAGINA, RETIRAPAGINA, INSEREEDITOR ou RETIRAEDITOR
                    if(!strcmp(funcao,"IMPRIMEWIKED")) // avaliando primeiro o caso IMPRIMEWIKED pois não possui parâmetros
                    {
                        ImprimeWiked(wiki);
                    }
                    else
                    {
                        fscanf(entrada, " %s", arg1); // buscando um parâmetro
                        if(!strcmp(funcao,"INSEREPAGINA")) // testando INSEREPAGINA (dois parâmetros)
                        {
                            fscanf(entrada, " %s", arg2); // buscando seu outro parâmetro
                            Wiki_InserePagina(wiki,arg1,arg2);
                        }
                        else // funções remanecentes utilizam somente um argumento
                        {
                            if(!strcmp(funcao,"RETIRAPAGINA"))
                            {
                                Wiki_RetiraPagina(wiki,arg1);
                            }
                            if(!strcmp(funcao,"INSEREEDITOR"))
                            {
                                Wiki_InsereEditor(wiki,arg1);
                            }
                            if(!strcmp(funcao,"RETIRAEDITOR"))
                            {
                                Wiki_RetiraEditor(wiki,arg1);
                            }
                        }
                    }
                    break;

            case 13: // função IMPRIMEPAGINA
                    fscanf(entrada, " %s", arg1);
                    Wiki_ImprimePagina(wiki,arg1);
                    break;

            case 18: // função INSERECONTRIBUICAO ou RETIRACONTRIBUICAO
                    fscanf(entrada, " %s %s %s", arg1, arg2, arg3); // ambas utilizam três argumentos
                    if(!strcmp(funcao,"INSERECONTRIBUICAO"))
                    {
                        Wiki_InsereContribuicao(wiki,arg1,arg2,arg3);
                    }
                    else
                    {
                        Wiki_RetiraContribuicao(wiki,arg1,arg2,arg3);
                    }
                    break;
            
            default: printf("ERRO: comando nao reconhecido\n"); // mensagem de erro em caso a função escolida não se enquadre
        }

        fscanf(entrada, " %s", funcao); // atualizando funcao
    }

    if(fclose(entrada)) // fechando o arquivo
    {
        printf("ERRO: arquivo nao pode ser fechado\n");
        exit(0);
    }

    DestroiWiked(wiki);

    return 0;
}
