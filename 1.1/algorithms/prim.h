/*see README for original credits */

#ifndef PRIM_H
#define PRIM_H

#include<stdarg.h>
#include"../ds/graph1.h"
#include"../ds/mst.h"

void prim(const graph *g, int start, mst* m, 
  void (*cost_function)(const edge_node* p, int v,
    int* distance, int* parent, ...));
void prim_cost(const edge_node* p, int v, int* distance, int* parent, ...);
void sp_cost(const edge_node* p, int v, int* distance, int* parent, ...);

#endif /* PRIM_H */
