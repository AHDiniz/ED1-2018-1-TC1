# Makefile para facilitar a compilação para Linux

# Compilador:
CC = gcc

# Opções de compilação:
CFLAGS = -Wall -g -O3

# Nome do programa executável:
EXE = wikedLinux.out

# Alvo principal da compilação:
all: $(EXE)

# Receita de compilação do executável:
$(EXE): main.o contribuicao.o editor.o lista.o log.o pagina.o wiki.o
	$(CC) $(CFLAGS) -o $(EXE) main.o contribuicao.o editor.o lista.o log.o pagina.o wiki.o

# Receita de compilação do arquivo-objeto do ponto de entrada:
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Receita de compilação do arquiv-objeto da biblioteca do TAD de contribuição:
log.o: log/log.c log/log.h
	$(CC) $(CFLAGS) -c log/log.c

# Receita de compilação do arquivo-objeto da biblioteca do TAD de wiki:
wiki.o: wiki/wiki.c wiki/wiki.h pagina.o lista.o log.o contribuicao.o
	$(CC) $(CFLAGS) -c wiki/wiki.c pagina.o lista.o log.o contribuicao.o

# Receita de compilação do arquiv-objeto da biblioteca do TAD de contribuição:
pagina.o: pagina/pagina.c pagina/pagina.h editor.o contribuicao.o lista.o
	$(CC) $(CFLAGS) -c pagina/pagina.c editor.o contribuicao.o lista.o

# Receita de compilação do arquiv-objeto da biblioteca do TAD de contribuição:
contribuicao.o: contribuicao/contribuicao.c contribuicao/contribuicao.h
	$(CC) $(CFLAGS) -c contribuicao/contribuicao.c

# Receita de compilação do arquiv-objeto da biblioteca do TAD de contribuição:
editor.o: editor/editor.c editor/editor.h contribuicao.o
	$(CC) $(CFLAGS) -c editor/editor.c contribuicao.o

# Receita de compilação do arquiv-objeto da biblioteca do TAD de contribuição:
lista.o: lista/lista.c lista/lista.h
	$(CC) $(CFLAGS) -c lista/lista.c

# Comando para limpar todos os arquivos objetos:
clean:
	rm *.o