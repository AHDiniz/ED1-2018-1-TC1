# Makefile para o projeto de Estrutura da Dados I
#
# Alan Herculano Diniz e Rafael Belmock Pedruzzi

all: trab

trab: main.o
	gcc -o trab main.o

main.o: main.c
	gcc -c main.c