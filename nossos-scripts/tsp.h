#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quick.h"
#include "stack.h"
#include "linkedList.h"

typedef struct data Data;
typedef struct city_node City;
typedef struct edge Edge;
typedef struct adj Adj;

//Criação do vetor de adjacencias
Adj* make_Adj(int);

//Liberação do vetor de adjacencias
void free_Adj(Adj* x, int n);

//Gera o vetor com todas as aresta possíveis de um problema
Edge* make_edges(Data* x);

//Lê as informações do problema de um arquivo, gera e retorna o struct
Data* read_data(FILE* archive);

//Cria o struct principal do problema
Data* create_data(char* name, char* type, char* edge, int dimension, City** cities);

//Cria um struct de cidade
City* create_city(int x, int y);

//Libera toda a memória usada por um Data
Data* clear_data(Data* data);

//Cria um arquivo de saída com a MST
void print_mst(Data* data, Edge* nec);

//Cria um arquivo de saída com o Tour
void print_tour(Data* data, int* tr);

//Função usada de callback para empilhar as cidades adjacentes de uma determinada cidade
void* visit(void* data,void* stack);

//Tour baseado em busca em profundidade em grafos
int* tour(Adj* x, int n, City** b, int* dist);
