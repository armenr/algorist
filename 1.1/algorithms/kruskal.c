/*see README for original credits */

#include<stdlib.h>
#include"kruskal.h"
#include"../ds/set-union.h"

static void to_edge_array(const graph *g, edge_pair* e);
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
void kruskal(const graph *g, mst* m) {
	set_union s;
  edge_pair ep[m->ep_sz];
  
  /*Put the edges in a priority queue ordered by weight.*/
	init_set_union(&s, m->ep_sz);
	to_edge_array(g, ep);
	qsort(&ep, m->ep_sz, sizeof(edge_pair), weight_compare);

	int i;
  /*create mst	*/
	for(i = 0; i < m->ep_sz; i++) {
		int* r1 = malloc(sizeof(int));
		int* r2 = malloc(sizeof(int));
		edge_pair e = ep[i];

    /*cost function*/
		if(!same_comp_set_union(&s, e.x, e.y, r1, r2)) {
			m->edge_pairs[i] = e;	  
	    m->nedges++;
      m->cost += e.weight;

			merge_set_union(&s, *r1, *r2);
		}
		free(r1);
		free(r2);
	}
  m->nedges++;
  
  clear_set_union(&s);
}

static void to_edge_array(const graph *g, edge_pair* e) {
  int i, j = 0;

  for(i = 0; i < g->nvertices; i++) {
  	const vertex* vert = find_vertex(g, i);
		const edge_node* p = vert->edges;

    while(p != NULL) {
      if(p->y > i) {  /*select all unique edges*/
        e[j].x = i;
        e[j].y = p->y;
        e[j].weight = p->weight;
        j++;
      }
      p = p->next;
    }
  }
}

static int weight_compare(const edge_pair *x, const edge_pair *y) {
  if(x == NULL && y == NULL)
    return 0;
  if(x == NULL)
    return -1;
  if(y == NULL)
    return 1;
      
	return x->weight - y->weight;
}

