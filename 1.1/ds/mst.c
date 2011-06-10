/*see README for original credits */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mst.h"

void clear_mst(mst* m) {
  free(m->edge_pairs);
  free(m->parent);
}

void init_mst(mst* m, int sz) {
  int l = sz * sizeof(edge_pair);
  m->ep_sz = sz;

  m->edge_pairs = malloc(l);
  memset(m->edge_pairs, 0, l);
  
  m->parent = malloc(sz * sizeof(int));
  m->cost = 0;
  m->nedges = 0;
}

void print_mst(const mst* m) {
  int i;
  for(i = 0; i < m->nedges+1; i++) {
    edge_pair e = m->edge_pairs[i];
    if(e.weight > 0) 
    	printf("#%d edge: (%d, %d) of weight %d in MST\n", i, e.x, e.y, e.weight);
  }

  printf("no edges: %d\n", m->nedges);
  printf("total cost: %d\n", m->cost);
}

void print_sp(const mst* m, int s) {
  int i;
  ;
  for(i = 0; i < m->nedges+1; i++) {
    edge_pair e = m->edge_pairs[i];
    if(e.weight > 0) 
    	printf("#%d path: (%d, %d) of cost %d\n", i, s, e.y, e.weight);
  }
}

