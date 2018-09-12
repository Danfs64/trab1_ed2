all: trab1 clean

trab1: beta.o
	gcc -o trab1 beta.o -lm -g -Wall

lab1.o: beta.c
	gcc -c beta.c -lm -g -Wall

clean:
	rm *.o

run: trab1 clean
	./trab1 in/danfs5.tsp
