#include "linkedList.h"

//Struct nó da lista
struct node{
  void *info; //Contém a info do nó
  Node* next; //E a referência para o próximo elemento
};

//Struct lista encadeada
struct ll{
  Node* head; //Contém o primeiro elemento
  Node* tail; //E o último elemento
};

//Cria um nó vazio
Node* create_node(){
  Node* p =(Node*) malloc(sizeof(Node));

  p->info = NULL;
  p->next = NULL;

  return p;
}

//Cria uma lista encadeada vazia
linked_list* create_ll(){
  linked_list* p =(linked_list*) malloc(sizeof(linked_list));

  p->head = NULL;
  p->tail = NULL;

  return p;
}

//Libera toda a memória alocada pela lista encadeada
void free_ll(linked_list* p){
  if(p == NULL){
    return;
  }
  Node* x = p->head, *y;
  while(x != NULL){
    y = x->next;
    free(x);
    x = y;
  }
  free(p);
}

void add_data(linked_list* list, void* data){
  Node* m = create_node();

  m->info = data;

  if(is_Empty_List(list)){
      list->head = m;
      list->tail = m;
    return;
  }

  list->tail->next = m;
  list->tail = m;
}

int is_Empty_List(linked_list* list){
  return list->head == NULL;
}

void* traverse(linked_list *list, void*(*func)(void*,void*), void* generico){
  if(is_Empty_List(list)){
    return NULL;
  }
  Node* p = list->head;
  void* r = NULL;
  for( ; p!=NULL ;p = p->next){
    r=func(p->info,generico);
    if(r != NULL){
      return r;
    }
  }
  return NULL;
}

void* remove_data(linked_list* linked_list, void* data){
  Node* p = linked_list->head,*ant;
  void* x;

  if(data == NULL || p == NULL){
    return NULL;
  }

  if(data == p->info){
    linked_list->head = p->next;
    x = p->info;
    free(p);
  }else{
    for( ; p != NULL && p->info != data; p = p->next){
      ant = p;
    }
    ant->next = p->next;
    x = p->info;
    free(p);
  }
  return x;
}
