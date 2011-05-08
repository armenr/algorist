/*see README for original credits */

#ifndef KRUSKAL_H
#define KRUSKAL_H

#include"../ds/graph.h"

typedef struct {
  int x, y; /* adjacency info */
  int weight; /* edge weight, if any */
} edge_pair;

void kruskal(const graph *g);

#endif /* KRUSKAL_H */


