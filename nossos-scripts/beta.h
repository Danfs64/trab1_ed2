#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linkedList.h"

#define distance(v1,v2) round(sqrt(pow((v2->x - v1->x),2) + pow((v2->y - v1->y),2)))

typedef struct data Data;
typedef struct city_node City;
typedef struct edge Edge;
