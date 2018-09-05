#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linkedList.h"

#define distance(x1,y1,x2,y2) round(sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)))
typedef struct data Data;
typedef struct city_node City;
