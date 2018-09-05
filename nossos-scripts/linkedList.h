#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct ll linked_list;


/*cria uma celula da linked_list generica
*inputs: nenhum
* outputs: celula criada
* pré-condicao: nenhuma
* pós-condicao: celula criada e alocada*/
Node* create_node();

/*cria a sentinela da linked_list generica
* inputs: nenhum
* outputs: sentinela da linked_list
* pré-condicao: nenhuma
* pós-condicao: sentinela criada e alocada*/
linked_list* create_ll();

/*libera todas as posições da linked_list generica (exceto o dado armazenad)
* inputs:sentinela da linked_list
* outputs: nenhum
* pré-condicao: nenhuma
* pós-condicao: memoria da linked_list liberada*/
void free_ll(linked_list*);

/*insere um dado na linked_list
* inputs: sentinela da linked_list e o elemento que seŕa inserido
* outputs: nenhum
* pré-condicao: sentinela da linked_list existe
* pós-condicao: informação inserida na linked_list*/
void add_data(linked_list*, void*);

/*verifica se a linked_list é vazia
* inputs:sentinela da linked_list
* outputs: 1 se a linked_list for vazia e 0 caso não seja
* pré-condicao: linked_list existe
* pós-condicao: nenhuma*/
int is_Empty_List(linked_list*);

/*percorre a linked_list e retorna um endereco
* inputs: sentinela da linked_list, função callback que será utiliazada e uma string
* outputs: endereco retornado pela funçao callback
* pré-condicao: sentinela da linked_list e função callback existem
* pós-condicao: nenhuma*/
void* traverse(linked_list*, void*(*)(void*,void*), void*);

/*retira um elemento da linked_list e libera a celula da linked_list que carregava o elemento
* inputs:sentinela da linked_list e dado que sera retirado
* outputs: dado que foi retirado da linked_list
* pré-condicao: sentinela da linked_list existe
* pós-condicao: dado retirado da linked_list e a linked_list continua consistente*/
void* remove_data(linked_list*, void*);

#endif
