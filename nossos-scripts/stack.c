#include "stack.h"

struct node{
    void* info;
    Node* next;
};

struct stack{
    Node* head;
};

Stack* create_Empty_Stack(){
    Stack* x = malloc(sizeof(x));
    x->head = NULL;

    return x;
}

void push(void* x, Stack* y){
    Node* m = malloc(sizeof(m));
    m->info = x;
    m->next = y->head;

    y->head = m;
}

void* pop(Stack* y){
    if(is_Empty_Stack(y)){
        return NULL;
    }
    Node* z = y->head;  //guarda o nó do topo
    void* x = z->info;  //armazena a info
    y->head = z->next;  //ajusta a pilha
    free(z);            //libera o nó removido
    return x;           //retorna a info
}

int is_Empty_Stack(Stack* x){
    return x->head == NULL;
}

//provavelmente precisará de callback, dependendo do o que for o *info
void free_Stack(Stack* x){
    //Libera todos os nós ainda presentes na pilha
    while(!is_Empty_Stack(x)){
        pop(x);
    }
    //E então, libera a pilha
    free(x);
}
