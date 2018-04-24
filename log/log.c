/********************************************
Trabalho ED1 2018/1: Sistema colaborativo

Alan Herculano Diniz e Rafael Belmock Pedruzzi

log.c: implementações para mensagens de erro e para função Caminho
********************************************/

#include <stdio.h>

// Função de resposta da função Caminho
void CaminhoResposta(int verificacao, char* origem, char* destino){

    FILE* file = fopen("log.txt","a"); // Abre o arquivo para escrita, caso não exista o arquivo será criado

    if(verificacao == 0) // Analisando a resposta
        fprintf(file, "NAO HA CAMINHO DA PAGINA %s PARA %s\n", origem, destino); // Verificação igual a 0: Escrevendo resposta negativa no arquivo
    
    else
        fprintf(file, "HA CAMINHO DA PAGINA %s PARA %s\n", origem, destino); // Verificação diferente de zero: Escrevendo resposta positiva no arquivo
    
    fclose(file); // Fechando o arquivo
}

// Funções de resposta de erros (funcionam de maneira idéntica, alterando-se apenas as mensagens. Por isso somente a primeira será comentada)
// Erro001: página inexistente
void Erro001(char* pagina){

    FILE* file = fopen("log.txt","a"); // Abrindo arquivo para escrita

    fprintf(file, "ERRO: nao existe a pagina %s\n", pagina); // Escrevendo mensagem de erro

    fclose(file); // Fechando arquivo
}

// Erro002: editor inexistente
void Erro002(char* editor){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe o editor %s\n", editor);

    fclose(file);
}

// Erro003: contribuição inexistente
void Erro003(char* contribuicao){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe a contribuicao %s\n", contribuicao);

    fclose(file);
}

// Erro004: página incorreta
void Erro004(char* pagina){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: pagina %s incorreta\n", pagina);

    fclose(file);
}

// Erro005: editor incorreto
void Erro005(char* editor){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: editor %s incorreto\n", editor);

    fclose(file);
}
