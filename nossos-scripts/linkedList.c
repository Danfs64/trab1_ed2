#include "linkedList.h"

struct node{
  void *info;
  struct node* next;
};

struct ll{
  Node* head;
  Node* tail;
};

Node* create_node(){
  Node* p =(Node*) malloc(sizeof(Node));

  p->info = NULL;
  p->next = NULL;

  return p;
}

linked_list* create_ll(){
  linked_list* p =(linked_list*) malloc(sizeof(linked_list));

  p->head = NULL;
  p->tail = NULL;

  return p;
}

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
  for(p ; p!=NULL ;p = p->next){
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
    for(p; p != NULL && p->info != data; p = p->next){
      ant = p;
    }
    ant->next = p->next;
    x = p->info;
    free(p);
  }
  return x;
}

// int length_ll(linked_list* x){
//     int b = 0;
//
//     for(Node* p = x->head; p != NULL; p = p->next){
//         b += 1;
//     }
//
//     return b;
// }
//
// Node* search_node(linked_list* b, int n){
//     node* p = b->head;
//
//     if(n > length_ll(b)){
//         return NULL;
//     }
//
//     if(n == 0){
//         return p;
//     }
//
//     for(int i = 0; i < n; i += 1){
//         p = p->next;
//     }
//     return p;
// }
//
// void insertion_Sort(linked_list *b, void* item, int (cb)(void*,void*)){
//     int length = length_ll(b);
//     Node* nova_Cel = create_node(),*aux;
//
//     nova_Cel->info = item;
//
//     if(length == 0){
//         b->head = nova_Cel;
//         return;
//     }
//
//
//     for(int i = 0; i<length ; i++){
//         aux = search_node(b,i);
//
//         if(cb(item,aux->info)){
//             if(i == 0){
//                 nova_Cel->next = b->head;
//                 b->head = nova_Cel;
//                 return;
//             }else{
//                 aux = search_node(b,i-1);
//                 nova_Cel->next = aux->next;
//                 aux->next = nova_Cel;
//                 return;
//             }
//         }else if(length -1 == i){
//             aux->next = nova_Cel;
//             return;
//         }
//     }
// }
