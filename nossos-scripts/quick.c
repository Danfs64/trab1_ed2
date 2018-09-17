#include "quick.h"

static int* id;
static int N;
static int* sz;

void UF_init(int size) {
    N = size;
    //printf("%d\n",N);

    id = malloc(sizeof(int)*(size+1));
    sz = malloc(sizeof(int)*(size+1));

    for(int i = 0; i <= N; i++) {
        id[i] = i;
        sz[i] = 1;
        // Cada objeto comeca na sua propria componente.
        }
    // N acessos ao array.
}

int UF_find(int i) {
    //i -= 1;
    while(i != id[i]) i = id[i];
    // Buscar o pai ate a raiz.
    return i;
    // Profundidade de i acessos.
}

int UF_union(int p,int q) {
    int i = UF_find(p);
    // Pendure a arvore menor sob a maior.
    int j = UF_find(q);
    // Profundidade de ? acessos.
    if(i == j) return 0;
    
    if(sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
    else              { id[j] = i; sz[i] += sz[j]; }
    return 1;
}

void quick_free(){
    free(id);
    free(sz);
}
