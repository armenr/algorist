/*see README for original credits */

#include"kruskal.h"
#include"set-union.h"
#include<stdlib.h>
#include<stdio.h>

static void to_edge_array(const graph *g, edge_pair e[]) {
  int i, m;			
  edgenode *p;			/* temporary pointer */

  m = 0;
  for(i = 1; i <= g->nvertices; i++) {
    p = g->vertices[i].edges;

    while(p != NULL) {

      if(p->y > i) {
        e[m].x = i;
        e[m].y = p->y;
        e[m].weight = p->weight;
        m = m+1;
      }

      p = p->next;
    }
  }
}

static int weight_compare(const edge_pair *x, const edge_pair *y) {
	if(x->weight < y->weight) 
	  return -1;
	if(x->weight > y->weight) 
	  return 1;

	return 0;
}

void kruskal(const graph *g) {
	int i;
	set_union s;			/* set union data structure */
	edge_pair e[MAXV+1];		/* array of edges data structure */

	set_union_init(&s, g->nvertices);
	to_edge_array(g, e);
	qsort(&e, g->nedges, sizeof(edge_pair), weight_compare);

	for(i = 0; i < g->nedges; i++) {
		print_set_union(&s);
		if(!same_component(&s, e[i].x, e[i].y)) {
			printf("edge (%d, %d) of weight %d in MST\n", e[i].x, e[i].y,e[i].weight);
			union_sets(&s, e[i].x, e[i].y);
		}
	}
}


