/*see README for original credits */

#include<limits.h>
#include<stdbool.h>
#include<stdlib.h>
#include"prim.h"

void prim(const graph *g, int start, mst* m, 
  void (*cost_function)(const edge_node* p, int v, int* distance, 
    int* parent, ...)) {
  
	bool intree[g->nvertices];		/* is the vertex in the tree yet? */
	int distance[g->nvertices];		/* cost of adding to tree */

	int i;

	for(i = 0; i < g->nvertices; i++) {
		intree[i] = false;
		distance[i] = INT_MAX;
		m->parent[i] = NO_PARENT;
	}

	distance[start] = 0;
	int v = start;  /* current vertex to process */

	while(!intree[v]) {
		intree[v] = true;

  	const vertex* vert = find_vertex(g, v);
		const edge_node* p = vert->edges;

    /*update cost for non-tree vertices (p->y) neighboring v*/
		while(p != NULL) { 
      /*plug in extra cost variables as required		*/
      cost_function(p, v, distance, m->parent, intree[p->y]);
			p = p->next;
		}

		v = 1;
		int dist = INT_MAX;
		
    /*find cheapest non-tree vertex to search from next*/
		for(i = 0; i < g->nvertices; i++) 
			if(!intree[i] && dist > distance[i]) {
				dist = distance[i];
				v = i;
			}
	}
	
  /*create mst	*/
	for(i = 0; i < g->nvertices; i++) 
	  if(intree[i] && m->parent[i] != NO_PARENT) {
	    edge_pair e;
	    e.x = m->parent[i];
	    e.y = i;
	    e.weight = distance[i];

			m->edge_pairs[i] = e;	  
      m->nedges++;
	    m->cost += distance[i];
	  }
}

/*
Prim-MST(G)
  Select an arbitrary vertex s to start the tree from.
  While (there are still nontree vertices)
    Select the edge of minimum weight between a tree and nontree vertex
    Add the selected edge and vertex to the tree Tprim .
*/
void prim_cost(const edge_node* p, int v, int* distance, int* parent, ...) {
  va_list ap;
  va_start(ap, parent); 
  int intree = va_arg(ap, int);

	if((distance[p->y] > p->weight) && !intree) {
		distance[p->y] = p->weight; /*lower cost */
		parent[p->y] = v; /*(p->y, v) pair describe this edge */
	}
  va_end(ap);
}

/*
ShortestPath-Dijkstra(G, s, t)
  known = {s}
  for i = 1 to n
    dist[i] = ∞
  for each edge (s, v)
    dist[v] = w(s, v)
  
  last = s

  while (last != t)
    select vnext , the unknown vertex minimizing dist[v]

    for each edge (vnext, x), 
      dist[x] = min[dist[x], dist[vnext ] + w(vnext , x)]

    last = vnext
    known = known ∪  {vnext}
*/
void sp_cost(const edge_node* p, int v, int* distance, int* parent, ...) {
  int d = distance[v] + p->weight;

	if(distance[p->y] > d) {
		distance[p->y] = d; /*shortest distance */
		parent[p->y] = v; /*(p->y, v) pair describe this edge */
	}
}

