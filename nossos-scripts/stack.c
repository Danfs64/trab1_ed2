#include "stack.h"

//Struct nó da pilha
struct node{
    void* info; //Contém a info do nó
    Node* next; //E a referência pro próximo elemento
};

//Struct pilha
struct stack{
    Node* head; //Contém o elemento do topo da pilha
};

//Cria uma pilha vazia
Stack* create_Empty_Stack(){
    Stack* x = malloc(sizeof(Stack));
    x->head = NULL;

    return x;
}

//Insere um elemento void* no topo da pilha
void push(void* x, Stack* y){
    //Inicializa o nó com a informação
    Node* m = malloc(sizeof(Node));
    m->info = x;
    m->next = y->head;  //Coloca o antigo topo da pilha como seu próximo

    y->head = m;        //Ajusta a pilha para o novo ser o topo
}

//Retira e retorna o elemento do topo da pilha
void* pop(Stack* y){
    //Se a pilha for vazia, o pop falha e retorna um ponteiro NULL
    if(is_Empty_Stack(y)){
        return NULL;
    }
    Node* z = y->head;  //guarda o nó do topo
    void* x = z->info;  //armazena a info do topo
    y->head = z->next;  //ajusta a pilha, removendo o topo
    free(z);            //libera o nó removido
    return x;           //retorna a info
}

//Confere se a pilha está vazia
int is_Empty_Stack(Stack* x){
    return x->head == NULL;
}

//Libera toda a memória ocupada pela pilha
void free_Stack(Stack* x){
    //Libera todos os nós ainda presentes na pilha
    //Obs.: parte-se do pressuposto de que não é preciso liberar o conteúdo do nó
    while(!is_Empty_Stack(x)){
        pop(x);
    }
    //E então, libera a pilha
    free(x);
}
