# Makefile para o projeto de Estrutura da Dados I
#
# Alan Herculano Diniz e Rafael Belmock Pedruzzi

# Objetivo da compilação é o executável trab (.exe no Windows e .out em outros SO's)
all: trab

# Compilando o trabalho dado que já se tem o arquivo objeto da main
trab: main.o
	gcc -o trab main.o

# Compilando a main
main.o: main.c
	gcc -c main.c

# Compilando os arquivos da lista genérica sem links
lista/lista.o: lista/lista.c lista/lista.h
	gcc -c lista/lista.c

# Compilando os arquivos da contribuição sem links
contribuicao/contribuicao.o: contribuicao/contribuicao.c contribuicao/contribuicao.h
	gcc -c contribuicao/contribuicao.c

# Compilando os arquivos do editor sem links
editor/editor.o: editor/editor.c editor/editor.h
	gcc -c editor/editor.c

# Compilando os arquivos da biblioteca de erros sem links
log/log.o: log/log.c log/log.h
	gcc -c log/log.c

# Compilando os arquivos da página sem links
pagina/pagina.o: pagina/pagina.c pagina/pagina.h
	gcc -c pagina/pagina.c

# Compilando os arquivos da wiki sem links
wiki/wiki.o: wiki/wiki.c wiki/wiki.h
	gcc -c wiki/wiki.c