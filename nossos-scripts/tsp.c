#include "tsp.h"

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
};

//Estrutura de adjacencias de cada cidade
typedef struct{
    int id,color;
    linked_list* adjacencies;
}Adj;
//Calculo das distancias entre cidades
static int distance(City* v1, City* v2){
    int x = pow((v2->x - v1->x),2);
    int y = pow((v2->y - v1->y),2);

    return round(sqrt(x+y));
}
//Criação do vetor de adjacencias
Adj* make_Adj(int n){
    Adj* x = malloc(sizeof(Adj)*n);
    for(int i = 0; i < n; i++){
        x[i].id = i+1;
        x[i].color = 0;
        x[i].adjacencies = create_ll();
    }
    return x;
}
//Liberação do vetor de adjacencias
void free_Adj(Adj* x, int n){
    for(int i = 0; i < n;i++){
        free_ll(x[i].adjacencies);
    }
    free(x);
}
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
            y[index++].dist = distance(x->node_coord_section[i],x->node_coord_section[j]);
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
//Cria um arquivo de saída com o Tour
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
//Função usada de callback para empilhar as cidades adjacentes de uma determinada cidade
void* visit(void* data,void* stack){
    if(((Adj*)data)->color == 0){
        push(data,(Stack*)stack);
    }
    return NULL;
}
//Tour baseado em busca em profundidade em grafos
int* tour(Adj* x, int n){
    int* tr = malloc(sizeof(int)*n);
    Stack* st = create_Empty_Stack();
    push(x,st);
    int index = 0;

    while (!is_Empty_Stack(st)) {
        Adj* m = (Adj*)pop(st);
        m->color = 1;
        //printf("%d\n",index);
        tr[index++] = m->id;
        traverse(m->adjacencies,visit,st);
    }

    free_Stack(st);
    return tr;
}

int main(int argc, char** argv){
    //Abre o arquivo e cria as estruturas necessárias inicialmente
    FILE* x = fopen(argv[1],"r");
    Data* y = read_data(x);
    //Fecha o arquivo de entrada
    fclose(x);

    //Cria os vetores necessários pra geração da mst
    Edge* b = make_edges(y);
    Edge* mst = malloc(sizeof(Edge)*(y->dimension-1));
    //Ordena o vetor de aresta 'b' crescentemente
    qsort(b,number_of_edges(y->dimension),sizeof(Edge),compar);

    //Estrutura do Union-Find
    UF* d = UF_init(y->dimension);
    //Vetor de Estrutura de adjacencias
    Adj* m = make_Adj(y->dimension);
    //Indice do vetor de arcos que geram a mst
    int index = 0;

    //Abaixo a MST é formada
    //O if é satisfeito quando as duas cidades daquele arco foram conectadas
    //Para cada vez que o if é satisfeito o arco é adicionado no vetor da mst e cada cidade tem sua adjacente acrescentada a lista
    for(int i = 0; i < number_of_edges(y->dimension) && index < (y->dimension-1); i++){
        if(UF_union(b[i].x1, b[i].x2,d)){
            add_data(m[b[i].x1 - 1].adjacencies, &m[b[i].x2 - 1]);
            add_data(m[b[i].x2 - 1].adjacencies, &m[b[i].x1 - 1]);
            mst[index++] = b[i];
        }
    }

    //Libera (a maior) parte da memória alocada no programa, que não é mais necessária
    free(b);
    free_UF(d);
    //Gera o arquivo de saída de mst
    print_mst(y, mst);
    //Gera o vetor do tour e gera o arquivo de saida do tour
    int *tr = tour(m,y->dimension);
    print_tour(y,tr);

    //Libera todo o resto da memória alocada no programa
    free_Adj(m,y->dimension);
    clear_data(y);
    free(tr);
    free(mst);

    return 0;
}
