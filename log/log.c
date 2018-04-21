#include <stdio.h>

void CaminhoResposta(int i, char* origem, char* destino){

    FILE* file;
    fopen("log.txt","a");

    if(i == 0)
        fprintf(file, "NAO HA CAMINHO DA PAGINA %s PARA %s\n", origem, destino);
    
    else
        fprintf(file, "HA CAMINHO DA PAGINA %s PARA %s\n", origem, destino);
    
    fclose(file);
}

void Erro001(char* pagina){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe a pagina %s\n", pagina);

    fclose(file);
}

void Erro002(char* editor){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe o editor %s\n", editor);

    fclose(file);
}

void Erro003(char* contribuicao){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: nao existe a contribuicao %s\n", contribuicao);

    fclose(file);
}

void Erro004(char* pagina){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: pagina %s incorreta\n", pagina);

    fclose(file);
}

void Erro005(char* editor){

    FILE* file = fopen("log.txt","a");

    fprintf(file, "ERRO: editor %s incorreto\n", editor);

    fclose(file);
}
