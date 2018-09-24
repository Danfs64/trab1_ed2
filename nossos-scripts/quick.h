#ifndef __QUICK_H
#define __QUICK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct uf UF;

UF* UF_init(int size);
int UF_find(int i, UF* x);
int UF_union(int p,int q,UF* x);
void free_UF(UF* x);

#endif
