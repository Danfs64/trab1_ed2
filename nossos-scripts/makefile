#Gera o executável padrão e limpa os .o
all: trab1 clean

#Cria o executável usando os .o gerados
trab1: beta.o quick.o stack.o linkedList.o
	gcc -o trab1 beta.o quick.o stack.o linkedList.o -lm -g -Wall

#Gera os .o necessários
beta.o: beta.c
	gcc -c beta.c -lm -g -Wall

quick.o: quick.c
	gcc -c quick.c -lm -g -Wall

stack.o: stack.c
	gcc -c stack.c -lm -g -Wall

linkedList.o: linkedList.c
	gcc -c linkedList.c -lm -g -Wall

#Processo de compilação com a tag -O2 pra otimização
otim: execo clean 

execo: beta.o2 quick.o2 stack.o2 linkedList.o2
	gcc -O2 -o trab1 beta.o quick.o stack.o linkedList.o -lm -g -Wall
beta.o2: beta.c
	gcc -O2 -c beta.c -lm -g -Wall

quick.o2: quick.c
	gcc -O2 -c quick.c -lm -g -Wall

stack.o2: stack.c
	gcc -O2 -c stack.c -lm -g -Wall

linkedList.o2: linkedList.c
	gcc -O2 -c linkedList.c -lm -g -Wall

#Limpa todos os .o
clean:
	rm *.o

#Roda o programa com o exemplo berlin52.tsp
run: trab1 clean
	./trab1 in/berlin52.tsp

#Roda o programa com o teste simples danfs5.tsp
run2: trab1 clean
	./trab1 in/danfs5.tsp

#Roda o programa com o maior caso, o d18512.tsp
run3: trab1 clean
	./trab1 in/d18512.tsp