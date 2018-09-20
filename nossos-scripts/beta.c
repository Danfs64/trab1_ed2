#include "beta.h"

#define distance(v1,v2) round(sqrt(pow((v2->x - v1->x),2) + pow((v2->y - v1->y),2)))
#define number_of_edges(n) ((n/2)*(n-1))+(((n-1)/2)*((n%2) != 0))
#define Default 30

//Estrutura que armazena todas as informações do problema
struct data{
    char* name;
    char type[4];
    int dimension;
    char edge_weight_dimension[7];
    City** node_coord_section;
};
//Estrutura que representa uma cidade, contem o id e as coordenadas
struct city_node{
    float x, y;
};
//Estrutura que representa uma aresta da mst, com suas arestas e seu peso
struct edge{
    int x1, x2;
    int dist;
    int check;
};

//Função de comparação para o quicksort
static int compar(const void* x1, const void* x2){
  return ((Edge*)x1)->dist > ((Edge*)x2)->dist? 1:0;
}

//Gera o vetor com todas as aresta possíveis de um problema
Edge* make_edges(Data* x){
    int index = 0, h = number_of_edges(x->dimension);
    Edge* y = malloc(sizeof(Edge)*h);

    for(int i = 0; i < (x->dimension - 1); i++){
        for(int j = i+1; j < x->dimension; j++){

            y[index].x1 = i+1;
            y[index].x2 = j+1;
            y[index].dist = distance(x->node_coord_section[i],x->node_coord_section[j]);

            y[index].check = 0;
            index++;
        }
    }

    return y;
}
//Cria um struct de cidade
City* create_city(int x, int y){
  City* b = malloc(sizeof(*b));

  b->x = x;
  b->y = y;

  return b;
}
//Cria o struct principal do problema
Data* create_data(char* name, char* type, char* edge, int dimension, City** cities){
    Data* x = malloc(sizeof(*x));

    x->name = strdup(name);
    strcpy(x->type, type);
    x->dimension = dimension;
    strcpy(x->edge_weight_dimension, edge);
    x->node_coord_section = cities;

    return x;
}
//Lê as informações do problema de um arquivo, gera e retorna o struct
Data* read_data(FILE* archive){
    char trash[Default], name[Default], edge[Default], type[Default];
    int dimension,id;
    float x, y;
    City** c;

    fscanf(archive, "%s %s\n", trash, name);

    while(strcmp(trash,"TYPE:")){
        fscanf(archive,"%s\n", trash);
    }
    fscanf(archive, "%s\n", type);

    fscanf(archive, "%s %d\n", trash, &dimension);

    fscanf(archive, "%s %s\n", trash,edge);
    fscanf(archive, "%s\n",trash);

    c = malloc(sizeof(City*)*dimension);
    for(int i = 0; i < dimension; i++){
        fscanf(archive, "%d %f %f\n", &id, &x, &y);
        c[i] = create_city(x,y);

    }

    Data* a = create_data(name,type,edge,dimension,c);

    return a;
}
//Libera toda a memória usada por um Data
Data* clear_data(Data* data) {
  for (int i = 0; i < data->dimension; i++) {
    free(data->node_coord_section[i]);
  }
  free(data->node_coord_section);
  free(data->name);
  free(data);

  return NULL;
}
//Cria um arquivo de saída com a MST
void print_mst(Data* data, Edge* nec) {
  char name[Default];
  strcpy(name, "mst/");
  strcat(name, data->name);
  strcat(name, ".mst");
  FILE* arq = fopen(name, "w+");

  fprintf(arq, "NAME: %s\nTYPE: MST\nDIMENSION: %d\nMST_SECTION\n",
                      data->name, data->dimension);

  for (int i = 0; i < data->dimension-1; i++) {
    fprintf(arq, "%d %d\n", nec[i].x1, nec[i].x2);
  }
  fprintf(arq, "EOF\n");

  fclose(arq);
}

void print_tour(Data* data, int* tr) {
  char name[Default];
  strcpy(name, "tour/");
  strcat(name, data->name);
  strcat(name, ".tour");
  FILE* arq = fopen(name, "w+");

  fprintf(arq, "NAME: %s\nTYPE: TOUR\nDIMENSION: %d\nTOUR_SECTION\n",
                      data->name, data->dimension);

  for (int i = 0; i < data->dimension; i++) {
    fprintf(arq, "%d\n", tr[i]);
  }
  fprintf(arq, "EOF\n");

  fclose(arq);
}

// int find(int n,int *x,int elem){
//     for(int i = 0; i < n && x[i] != 0; i++){
//         if(x[i] == elem) return 1;
//     }
//     return 0;
// }

//tour com as arestas ordenadas
int* tour(Edge* x, int n){
    Edge* m;    //Variável que receberá as arestas
    int *tr = malloc(sizeof(int)*(n+1)), index = 0, *find = calloc(n+1,sizeof(int));
    Stack* st = create_Empty_Stack();
    push(x,st); //Insere uma aresta arbitrária na pilha

     while(!is_Empty_Stack(st)){
        m = (Edge*)pop(st); //Pega a aresta analizada;
        m->check = 1;       //Coloca ela como checada;
        if(!find[m->x1]){
            tr[index++] = m->x1;
            find[m->x1] = 1;
        }
        if(!find[m->x2]){
            tr[index++] = m->x2;
            find[m->x2] = 1;
        }
        //printf("%d -- %d\n\n\n", m->x1, m->x2);
        for(int i = 0; i < n; i++){
            //printf("%d -- %d; check = %d\n",x[i].x1, x[i].x2, x[i].check);
            if(x[i].check == 0 && (m->x1 == x[i].x2 || m->x2 == x[i].x2 ||
                                 m->x1 == x[i].x1 || m->x2 == x[i].x1) ) {

                push(&x[i],st);
            }
        }
    }
    free(find);
    free_Stack(st);
    return tr;
}

void tour2(Edge* x, int n){
    Edge* m;      //Variável que receberá as arestas
    Stack* st = create_Empty_Stack();
    push(x,st);   //Insere a menor aresta na pilha
    x->check = 1; //Coloca ela como checada;
    int temp;     //int temporário, usado pra trocas;

    while(!is_Empty_Stack(st)){
        m = (Edge*)pop(st); //Pega a aresta analizada;
        printf("->%d->%d", m->x1, m->x2);
        for(int i = 0; i < n; i++){
            if(x[i].check == 0 && (m->x1 == x[i].x1 || m->x2 == x[i].x1)) {
                x[i].check = 1;
                push(&x[i],st);
            } else if(x[i].check == 0 && (m->x1 == x[i].x2 || m->x2 == x[i].x2)) {
                temp = x[i].x1;
                x[i].x1 = x[i].x2;
                x[i].x2 = temp;
                x[i].check = 1;
                push(&x[i],st);
            }
        }
    }
}


int main(int argc, char** argv){
    //Abre o arquivo e cria as estruturas necessárias inicialmente
    FILE* x = fopen(argv[1],"r");
    Data* y = read_data(x);

    fclose(x);

    Edge* b = make_edges(y);
    Edge* mst = malloc(sizeof(Edge)*(y->dimension-1));
    //Ordena o vetor de aresta 'b' crescentemente
    qsort(b,number_of_edges(y->dimension),sizeof(Edge),compar);

    UF_init(y->dimension);

    int index = 0;
    for(int i = 0; i < number_of_edges(y->dimension); i++){
        if(UF_union(b[i].x1, b[i].x2)){
            mst[index] = b[i];
            index++;
            if(index == (y->dimension-1)) break;
        }
    }
    free(b);
    quick_free();

    print_mst(y, mst);

    int *tr = tour(mst,y->dimension-1);
    print_tour(y,tr);


    //Libera toda a memória alocada no programa
    clear_data(y);
    free(tr);
    free(mst);

    return 0;
}
