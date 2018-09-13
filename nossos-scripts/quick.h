#ifndef __QUICK_H
#define __QUICK_H

#include <stdlib.h>
#include <stdio.h>

void UF_init(int size);
int UF_find(int i);
int UF_union(int p,int q);

#endif
