#include "beta.h"

#define Default 30

struct data{
    char* name;
    char type[4];
    int dimension;
    char edge_weight_dimension[7];
    City** node_coord_section;
};

struct city_node{
    int id;
    float x, y;
};

struct edge{
    City* x1, *x2;
    int dist;
};

int number_of_edges(int dimension){
    int amount = 0;
    for(int i = 1; i < dimension; i++){
        amount += i;
    }
    return amount;
}

Edge* make_edges(Data* x){
    int index = 0, h = number_of_edges(x->dimension);
    Edge* y = malloc(sizeof(Edge)*h);

    for(int i = 0; i < x->dimension -1; i++){
        for(int j = i+1; j < x->dimension; j++){
            y[index].dist = distance(x->node_coord_section[i],x->node_coord_section[j]);

            y[index].x1 = x->node_coord_section[i];

            y[index].x2 = x->node_coord_section[j];
            index++;
        }
    }

    return y;
}

int compar(const void* x1, const void* x2){
    return ((Edge*)x1)->dist > ((Edge*)x2)->dist? 1:0;
}

Data* create_data(char* name, char* type,char* edge,int dimension, City** cities){
    Data* x = malloc(sizeof(*x));

    x->name = strdup(name);
    strcpy(x->type, type);
    x->dimension = dimension;
    x->node_coord_section = cities;
    strcpy(x->edge_weight_dimension, edge);

    return x;
}

City* create_city(int id, int x, int y){
    City* b = malloc(sizeof(*b));

    b->id = id;
    b->x = x;
    b->y = y;

    return b;
}

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
    c = malloc(sizeof(City*)*dimension);

    fscanf(archive, "%s %s\n", trash,edge);
    fscanf(archive, "%s\n",trash);

    for(int i = 0; i < dimension; i++){
        fscanf(archive, "%d %f %f\n", &id, &x, &y);
        c[i] = create_city(id,x,y);
        //printf("%d %.2f %.2f\n",c[i]->id,c[i]->x,c[i]->y);
    }

    Data* a = create_data(name,type,edge,dimension,c);

    return a;
}

// os pesos são as distancias entre nós

int main(int argc, char** argv){
    FILE* x = fopen(argv[1],"r");
    Data* y = read_data(x);
    Edge* b = make_edges(y);

    qsort(b,number_of_edges(y->dimension),sizeof(Edge),compar);
    for(int i = 0; i < 500; i++){
      printf("%d \n",b[i].dist);
    }
}
