/*see README for original credits */

#include"kruskal.h"
#include"../ds/set-union.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

static void to_edge_array(const graph *g, edge_pair e[]);
static int weight_compare(const edge_pair *x, const edge_pair *y);

/*
Kruskal-MST(G)
Put the edges in a priority queue ordered by weight.
  count = 0
  while (count < (# of edges) − 1) do
    get next edge (v, w)
    if (component (v) != component(w))
      add to Tkruskal
      merge component(v) and component(w)
*/
void kruskal(const graph *g) {
	set_union s;
	edge_pair e[MAXV+1];
  memset(&e, 0, (MAXV+1) * sizeof(edge_pair)); /*initialize*/
  
  /*Put the edges in a priority queue ordered by weight.*/
	init_set_union(&s, g->nvertices);
	to_edge_array(g, e);
	qsort(&e, g->nedges, sizeof(edge_pair), weight_compare);

	int i, n = 1;

	for(i = 1; i < g->nedges; i++) {
/*		print_set_union(&s);*/
		
		int* r1 = malloc(sizeof(int));
		int* r2 = malloc(sizeof(int));
		
		if(!same_comp_set_union(&s, e[i].x, e[i].y, r1, r2)) {
			printf("#%d edge: (%d, %d) of weight %d in MST\n", n++, e[i].x, 
			  e[i].y,e[i].weight);
			merge_set_union(&s, *r1, *r2);
		}
		
		free(r1);
		free(r2);
	}
}

static void to_edge_array(const graph *g, edge_pair e[]) {
  int i, m = 0;
  edgenode *p;

  for(i = 1; i <= g->nvertices; i++) {
    p = g->vertices[i].edges;

    while(p != NULL) {
      if(p->y > i) {  /*select all unique edges*/
        e[m].x = i;
        e[m].y = p->y;
        e[m].weight = p->weight;
        m++;
      }

      p = p->next;
    }
  }
}

static int weight_compare(const edge_pair *x, const edge_pair *y) {
	if(x->weight < y->weight) 
	  return -1;
	else if(x->weight > y->weight) 
	  return 1;

	return 0;
}

