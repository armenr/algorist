/*see README for original credits */

#ifndef MST_H
#define MST_H

#include"../ds/list.h"

typedef struct edge_pair {
  int x, y; /* adjacency info */
  int weight; /* edge weight, if any */
} edge_pair;

typedef struct mst {
  int cost; /*total cost*/
  int nedges; /*total no of edges*/
  list* edge_pairs;  
} mst;  /*minimum spanning tree*/

#endif /* MST_H */


