#ifndef __STACK_H
#define __STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct stack Stack;

Stack* create_Empty_Stack();
void push(void*, Stack*);
void* pop(Stack*);
int is_Empty_Stack(Stack*);
void free_Stack(Stack* x);

#endif
