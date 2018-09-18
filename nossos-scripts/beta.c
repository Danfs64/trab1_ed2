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
    int id;
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
            y[index].x1 = x->node_coord_section[i]->id;
            y[index].x2 = x->node_coord_section[j]->id;
            y[index].dist = distance(x->node_coord_section[i],x->node_coord_section[j]);

            y[index].check = 0;
            index++;
        }
    }

    return y;
}
//Cria um struct de cidade
City* create_city(int id, int x, int y){
  City* b = malloc(sizeof(*b));

  b->id = id;
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
    int dimension, id;
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
        c[i] = create_city(id,x,y);
        //printf("%d %.2f %.2f\n",c[i]->id,c[i]->x,c[i]->y);
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

int verified(Edge* x, int n){
    for(int i = 0; i < n; i++){
        if(x[i].check == 0){
            return 0;
        }
    }
    return 1;
}

void tour(Edge* x, int n){
    Edge* m;    //Variável que receberá as arestas
    // int id;     //Variável que armazenará a cidade "atual"
    Stack* st = create_Empty_Stack();
    push(x,st); //Insere uma aresta arbitrária na pilha

    while(!is_Empty_Stack(st)){
        m = (Edge*)pop(st); //Pega a aresta analizada;
        m->check = 1;       //Coloca ela como checada;
        // id = m->x2;         //Cidade "atual" é o x2 da aresta;
        printf("%d -- %d\n\n\n", m->x1, m->x2);
        for(int i = 0; i < n; i++){
            printf("%d -- %d; check = %d\n",x[i].x1, x[i].x2, x[i].check);
            if(m->check == 0 && (m->x1 == x[i].x2 || m->x2 == x[i].x2 ||
                                 m->x1 == x[i].x1 || m->x2 == x[i].x1) ) {
                // if (x[i].x1 == id) {
                //     id = x[i].x2;
                //     x[i].x2 = x[i].x1;
                //     x[i].x1 = id;
                // }
                push(&x[i],st);
            }
        }
    }
}

//versao alternativa da função de tour
//só fiz separada pra não alterar a ideia tu estava colocando em pratica acima
//obs: dps de printar até a cidade 161 corretamente erra mizeravelmente a prox. cidade antes de entrar em loop
void tr(Edge* x, int n){
    Edge* m;    //Variável que receberá as arestas
    // int id;     //Variável que armazenará a cidade "atual"
    Stack* st = create_Empty_Stack();
    printf("%d\n",x[0].x1);
    push(x,st); //Insere uma aresta arbitrária na
    int last = x[0].x1;
    int d = 0;
    
    while(!verified(x,n)){
        int reverse = 1;
        if(!is_Empty_Stack(st)){
            m = (Edge*)pop(st);
            m->check = 1;
            if(last == m->x1){
                printf("%d\n",m->x2);
                last = m->x2;
            }else{
                printf("%d\n",m->x1);
                last = m->x1;
            }
        }

        //alimenta a pilha com arestas cuja coordenada x1 é igual a ultima cidade visitada e que já não foram visitadas
        for(int i = 0; i < n; i++){
            if(last == x[i].x1 && x[0].check == 0){
                push(&x[i],st);
                reverse = 0;
            }
        }

        //alimenta a pilha com arestas cuja coordenada x2 é igual a ultima cidade visitada
        if(reverse){
            for(int i = 0; i < n; i++){
                //caso a aresta ainda nao tenha sido visitada coloque na pilha,
                //do contrario diga que a ultima cidade visitada é a cidade x1 da aresta que está sendo observada
                if(last == x[i].x2 && x[i].check == 0){
                    push(&x[i],st);
                }else if(last == x[i].x2 && x[i].check == 1){
                    last = x[i].x1;
                    i = 0;
                }
            }
        }
        // if(d == 10){
        //     break;
        // }
        // d++;
    }

}
// os pesos são as distancias entre nós

int main(int argc, char** argv){
    //Abre o arquivo e cria as estruturas necessárias inicialmente
    FILE* x = fopen(argv[1],"r");
    Data* y = read_data(x);
    Edge* b = make_edges(y);
    Edge* mst = malloc(sizeof(Edge)*(y->dimension-1));
    //Ordena o vetor de aresta 'b' não-decrescentemente
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

    print_mst(y, mst);

    //tour(mst,y->dimension-1);
    tr(mst,y->dimension-1);

    //Libera toda a memória alocada no programa
    clear_data(y);
    quick_free();
    free(b);
    free(mst);
    fclose(x);


    return 0;
}
