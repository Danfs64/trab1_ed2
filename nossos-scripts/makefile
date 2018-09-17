#Gera o executável e limpa os .o
all: trab1 clean

#Cria o executável usando os .o gerados
trab1: beta.o quick.o stack.o
	gcc -o trab1 beta.o quick.o stack.o -lm -g -Wall

#Gera os .o necessários
beta.o: beta.c
	gcc -c beta.c -lm -g -Wall

quick.o: quick.c
	gcc -c quick.c -lm -g -Wall

stack.o: stack.c
	gcc -c stack.c -lm -g -Wall

#Limpa todos os .o e os arquivos de saída
clean:
	rm *.o out/*

#Roda o programa com o exemplo berlin52.tsp
run: trab1 clean
	./trab1 in/berlin52.tsp

#Roda o programa com o teste simples danfs5.tsp
run2: trab1 clean
	./trab1 in/danfs5.tsp
