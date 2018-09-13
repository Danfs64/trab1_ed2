#include "stack.h"

struct node{
    void* info;
    struct node* next;
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
    void* x = y->head->info;
    Node* z = y->head;
    y->head = y->head->next;
    free(z);
    return x;
}

int is_Empty_Stack(Stack* x){
    return x->head == NULL;
}

void free_Stack(Stack* x){
    if(is_Empty_Stack(x)){
        free(x);
    }else{
        while(!is_Empty_Stack(x)){
            pop(x);
        }
        free(x);
    }
}
