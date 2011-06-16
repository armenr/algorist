/*see README for original credits */

#ifndef MST_H
#define MST_H

#define NO_PARENT -1

typedef struct edge_pair {
  int x, y; /* adjacency info */
  int weight; /* edge weight, if any */
} edge_pair;

typedef struct mst {
  int cost; /*total cost*/
  int nedges; /*total no of edges*/
  edge_pair* edge_pairs;
  int ep_sz; /*no of edge_pairs*/  
  int* parent; /* discovery relation */
  
} mst;  /*minimum spanning tree*/

void clear_mst(mst* m);
void init_mst(mst* m, int sz);
void print_mst(const mst* m);
void print_sp(const mst* m, int s);

#endif /* MST_H */
