/*see README for original credits */

#ifndef PRIM_H
#define PRIM_H

#include"../ds/graph.h"
#include"../ds/mst.h"
#include<stdarg.h>

void prim(const graph *g, int start, mst* m, 
  void (*cost_function)(const edgenode* p, int v,
    int* distance, int* parent, ...));
void prim_cost(const edgenode* p, int v, int* distance, int* parent, ...);
void sp_cost(const edgenode* p, int v, int* distance, int* parent, ...);

#endif /* PRIM_H */
