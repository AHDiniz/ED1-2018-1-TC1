/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

log.c: implementações para mensagens de erro e para função Caminho
********************************************/

#include "log.h"
#include <stdio.h>

// Função de resposta da função Caminho
void CaminhoResposta(int verificacao, char* origem, char* destino)
{
    FILE *file = fopen("log.txt","a"); // Abre o arquivo para escrita, caso não exista o arquivo será criado

    if(verificacao == 0) // Analisando a resposta
        fprintf(file, "NAO HA CAMINHO DA PAGINA %s PARA %s\n", origem, destino); // Verificação igual a 0: Escrevendo resposta negativa no arquivo
    
    else
        fprintf(file, "HA CAMINHO DA PAGINA %s PARA %s\n", origem, destino); // Verificação diferente de zero: Escrevendo resposta positiva no arquivo
    
    fclose(file); // Fechando o arquivo
}

// Funções de resposta de erros (funcionam de maneira idéntica, alterando-se apenas as mensagens. Por isso somente a primeira será comentada)
// Erro001: página inexistente
void ErroPagInexistente(char* pagina)
{
    FILE *file = fopen("log.txt","a"); // Abrindo arquivo para escrita

    fprintf(file, "ERRO: nao existe a pagina %s\n", pagina); // Escrevendo mensagem de erro

    fclose(file); // Fechando arquivo
}

// Erro002: editor inexistente
void ErroEdtInexistente(char* editor)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe o editor %s\n", editor);

    fclose(file);
}

// Erro003: contribuição inexistente
void ErroContInexistente(char* contribuicao, char* pagina)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe a contribuicao %s na pagina %s\n", contribuicao, pagina);

    fclose(file);
}

// Erro004: página incorreta
void ErroPagIncorreta(char* pagina)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: pagina %s incorreta\n", pagina);

    fclose(file);
}

// Erro005: editor incorreto
void ErroEdtIncorreto(char* editor)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: editor %s incorreto\n", editor);

    fclose(file);
}

// Erro006: página já existe
void ErroPagExiste(char* pagina)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: pagina %s ja existe\n", pagina);

    fclose(file);
}

// Erro007: editor já existe
void ErroEdtExiste(char* editor)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: editor %s ja existe\n", editor);

    fclose(file);
}

// Erro008: contribuição já existe
void ErroContExiste(char* contribuicao)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: contribuicao %s ja existe\n", contribuicao);

    fclose(file);
}

void ErroTXT(void)
{
    FILE *file = fopen("log.txt","a");

    fprintf(file, "ERRO: nomes de arquivos devem terminar em .txt\n");

    fclose(file);
}
