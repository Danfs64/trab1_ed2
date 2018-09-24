#include "quick.h"

struct uf{
    int* id;
    int* sz;
};

UF* UF_init(int size) {
    UF* x = malloc(sizeof(UF));
    x->id = malloc(sizeof(int)*(size+1));
    x->sz = malloc(sizeof(int)*(size+1));

    for(int i = 0; i <= size; i++) {
        x->id[i] = i;
        x->sz[i] = 1;
        // Cada objeto comeca na sua propria componente.
        }
    // N acessos ao array.
    return x;
}

int UF_find(int i, UF* x) {
    //i -= 1;
    while(i != x->id[i]) i = x->id[i];
    // Buscar o pai ate a raiz.
    return i;
    // Profundidade de i acessos.
}

int UF_union(int p,int q, UF* x) {
    int i = UF_find(p,x);
    // Pendure a arvore menor sob a maior.
    int j = UF_find(q,x);
    // Profundidade de ? acessos.
    if(i == j) return 0;

    if(x->sz[i] < x->sz[j]) { x->id[i] = j; x->sz[j] += x->sz[i]; }
    else                    { x->id[j] = i; x->sz[i] += x->sz[j]; }
    return 1;
}

void free_UF(UF* x){
    free(x->id);
    free(x->sz);
    free(x);
}
