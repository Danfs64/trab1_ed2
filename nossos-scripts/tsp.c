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
struct adj{
    int id,color;
    linked_list* adjacencies;
};

//Calculo das distancias entre cidades
static int distance(City* v1, City* v2){
    float x = pow((v2->x - v1->x),2);
    float y = pow((v2->y - v1->y),2);

    return round(sqrt(x+y));
}
//Função de comparação para o quicksort
static int compar(const void* x1, const void* x2){
    return ((Edge*)x1)->dist > ((Edge*)x2)->dist? 1:0;
}

int main(int argc, char** argv){
    //Abre o arquivo e cria as estruturas necessárias inicialmente
    FILE* input = fopen(argv[1],"r");
    Data* y = read_data(input);
    //Fecha o arquivo de entrada
    fclose(input);

    //Cria os vetores necessários pra geração da mst
    Edge* edges = make_edges(y);                          //Vetor de todas as arestas
    Edge* mst = malloc(sizeof(Edge)*(y->dimension-1));  //Vetor das arestas da mst
    //Ordena o vetor de aresta 'all' crescentemente
    qsort(edges,number_of_edges(y->dimension),sizeof(Edge),compar);

    UF* d = UF_init(y->dimension);  //Estrutura do Union-Find
    Adj* m = make_Adj(y->dimension);//Vetor de Estrutura de adjacencias
    int index = 0;                  //Indice do vetor de arcos que geram a mst

    //Abaixo a MST é formada
    //O for irá rodar até ele finalizar: ou o vetor da mst, ou o vetor de todas as arestas existentes
    //O if é satisfeito quando as duas cidades daquele arco foram conectadas
    //Para cada vez que o if é satisfeito cada cidade tem sua adjacente acrescentada a lista e o arco é adicionado no vetor da mst
    for(int i = 0; i < number_of_edges(y->dimension) && index < (y->dimension-1); i++){
        if(UF_union(edges[i].x1, edges[i].x2,d)){
            add_data(m[edges[i].x1 - 1].adjacencies, &m[edges[i].x2 - 1]);
            add_data(m[edges[i].x2 - 1].adjacencies, &m[edges[i].x1 - 1]);
            mst[index++] = edges[i];
        }
    }

    //Libera (a maior) parte da memória alocada no programa, que não é mais necessária
    free(edges);  //Vetor de todas as arestas
    free_UF(d); //Vetores usados no Union_Find

    //Gera o arquivo de saída de mst
    print_mst(y, mst);
    //Tamanho do tour gerado pela MST
    int dist;
    //Gera o vetor do tour e gera o arquivo de saida do tour
    int *tr = tour(m,y->dimension,y->node_coord_section,&dist);
    print_tour(y,tr);
    printf("Tamanho do Tour: %d\n",dist);

    //Libera todo o resto da memória alocada no programa
    free_Adj(m,y->dimension);   //Vetor de listas de adjacência
    clear_data(y);              //Vetor de informações do problema
    free(mst);                  //Vetor da mst
    free(tr);                   //Vetor do tour

    return 0;
}

Adj* make_Adj(int n){
    Adj* x = malloc(sizeof(Adj)*n);
    for(int i = 0; i < n; i++){
        x[i].id = i+1;
        x[i].color = 0;
        x[i].adjacencies = create_ll();
    }
    return x;
}

void free_Adj(Adj* x, int n){
    for(int i = 0; i < n;i++){
        free_ll(x[i].adjacencies);
    }
    free(x);
}

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

Data* create_data(char* name, char* type, char* edge, int dimension, City** cities){
    Data* x = malloc(sizeof(*x));

    x->name = strdup(name);
    strcpy(x->type, type);
    x->dimension = dimension;
    strcpy(x->edge_weight_dimension, edge);
    x->node_coord_section = cities;

    return x;
}

City* create_city(int x, int y){
    City* b = malloc(sizeof(*b));

    b->x = x;
    b->y = y;

    return b;
}

Data* clear_data(Data* data) {
    for (int i = 0; i < data->dimension; i++) {
        free(data->node_coord_section[i]);
    }
    free(data->node_coord_section);
    free(data->name);
    free(data);

    return NULL;
}

void print_mst(Data* data, Edge* mst) {
    char name[Default];
    strcpy(name, "mst/");
    strcat(name, data->name);
    strcat(name, ".mst");
    FILE* arq = fopen(name, "w+");

    fprintf(arq, "NAME: %s\nTYPE: MST\nDIMENSION: %d\nMST_SECTION\n",
            data->name, data->dimension);

    for (int i = 0; i < data->dimension-1; i++) {
        fprintf(arq, "%d %d\n", mst[i].x1, mst[i].x2);
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

void* visit(void* data,void* stack){
    if(((Adj*)data)->color == 0){
        push(data,(Stack*)stack);
    }
    return NULL;
}

int* tour(Adj* x, int n, City** b, int* dist){
    int* tr = malloc(sizeof(int)*n);
    Stack* st = create_Empty_Stack();
    push(x,st);
    int lastVisited = x->id;
    int index = 0;
    *dist = 0;

    while (!is_Empty_Stack(st)) {
        Adj* m = (Adj*)pop(st);
        m->color = 1;
        tr[index++] = m->id;
        *dist += distance(b[lastVisited-1],b[m->id-1]);
        lastVisited = m->id;
        traverse(m->adjacencies,visit,st);
    }

    free_Stack(st);
    return tr;
}
