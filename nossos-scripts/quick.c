#include "quick.h"

struct uf{
    int* id;
    int* sz;
};

//Inicializa a estrutura usada no Union_Find
UF* UF_init(int size) {
    //São alocados os vetores utilizados e a estrutura que irá armazenar ambos
    UF* x = malloc(sizeof(UF));
    x->id = malloc(sizeof(int)*(size+1));
    x->sz = malloc(sizeof(int)*(size+1));

    for(int i = 0; i <= size; i++) {
        x->id[i] = i; //Cada objeto comeca na sua propria componente
        x->sz[i] = 1; //Cada objeto comeca com peso 1
    }

    return x;
}

//Encontra a raiz do conjunto em que o elemento está
int UF_find(int i, UF* x) {
    //Sobe até o pai para achar, e então retornar, a raiz
    while(i != x->id[i]) i = x->id[i];

    return i;
}

//Tenta fazer a união dos elementos 'p' e 'q'
int UF_union(int p,int q, UF* x) {
    int i = UF_find(p,x);
    int j = UF_find(q,x);

    //Se ambos já estão no mesmo conjunto, não é feita a união
    if(i == j) return 0;

    //Se são de conjuntos diferentes, faz a união, baleanceando a árvore
    if(x->sz[i] < x->sz[j]) { x->id[i] = j; x->sz[j] += x->sz[i]; }
    else                    { x->id[j] = i; x->sz[i] += x->sz[j]; }
    return 1;
}

//Libera a memória ocupada pela estrutura de Union_Find
void free_UF(UF* x){
    free(x->id);
    free(x->sz);
    free(x);
}
