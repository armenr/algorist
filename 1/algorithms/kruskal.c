/*see README for original credits */

#include "bool.h"
#include "graph.h"
#include "kruskal.h"
#include "set_union.h"
#include <stdlib.h>
#include <stdio.h>

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

static void to_edge_array(const graph *g, edge_pair e[]) {
  int i, m;			
  edgenode *p;			/* temporary pointer */

  m = 0;
  for(i = 1; i <= g->nvertices; i++) {
    p = g->edges[i];

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

static bool weight_compare(const edge_pair *x, const edge_pair *y) {
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

int main(void) {
	graph g;
	read_graph(&g, FALSE);
	print_graph(&g);
	kruskal(&g);
  return 0;  
}

/* test run 
see fig 6.3 pp 196 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 12 edges

               *(4)
                        *(7)
                                                                        
              
     (5)*       *(6)    *(3)

                
        
          *         *                          
         (1)        (2)

osman@osman-desktop:~/src/algorithms$ ./kruskal
enter # vertices and # edges: 7 12
enter edge 1 (x, y, w): 1 2 12
enter edge 2 (x, y, w): 1 5 5
enter edge 3 (x, y, w): 1 6 7
enter edge 4 (x, y, w): 2 3 7
enter edge 5 (x, y, w): 2 6 4
enter edge 6 (x, y, w): 3 4 2
enter edge 7 (x, y, w): 3 6 3
enter edge 8 (x, y, w): 3 7 2
enter edge 9 (x, y, w): 4 5 7
enter edge 10 (x, y, w): 4 6 4
enter edge 11 (x, y, w): 4 7 5
enter edge 12 (x, y, w): 5 6 9
1:  6 5 2
2:  6 3 1
3:  7 6 4 2
4:  7 6 5 3
5:  6 4 1
6:  5 4 3 2 1
7:  4 3

1  set=1 size=1 
2  set=2 size=1 
3  set=3 size=1 
4  set=4 size=1 
5  set=5 size=1 
6  set=6 size=1 
7  set=7 size=1 

edge (3, 7) of weight 2 in MST
s1=3 r1=3 s2=7 r2=7
1  set=1 size=1 
2  set=2 size=1 
3  set=3 size=2 
4  set=4 size=1 
5  set=5 size=1 
6  set=6 size=1 
7  set=3 size=1 

edge (3, 4) of weight 2 in MST
s1=3 r1=3 s2=4 r2=4
1  set=1 size=1 
2  set=2 size=1 
3  set=3 size=3 
4  set=3 size=1 
5  set=5 size=1 
6  set=6 size=1 
7  set=3 size=1 

edge (3, 6) of weight 3 in MST
s1=3 r1=3 s2=6 r2=6
1  set=1 size=1 
2  set=2 size=1 
3  set=3 size=4 
4  set=3 size=1 
5  set=5 size=1 
6  set=3 size=1 
7  set=3 size=1 

edge (2, 6) of weight 4 in MST
s1=2 r1=2 s2=6 r2=3
1  set=1 size=1 
2  set=3 size=1 
3  set=3 size=5 
4  set=3 size=1 
5  set=5 size=1 
6  set=3 size=1 
7  set=3 size=1 

1  set=1 size=1 
2  set=3 size=1 
3  set=3 size=5 
4  set=3 size=1 
5  set=5 size=1 
6  set=3 size=1 
7  set=3 size=1 

edge (1, 5) of weight 5 in MST
s1=1 r1=1 s2=5 r2=5
1  set=1 size=2 
2  set=3 size=1 
3  set=3 size=5 
4  set=3 size=1 
5  set=1 size=1 
6  set=3 size=1 
7  set=3 size=1 

1  set=1 size=2 
2  set=3 size=1 
3  set=3 size=5 
4  set=3 size=1 
5  set=1 size=1 
6  set=3 size=1 
7  set=3 size=1 

** ALTERNATE EDGE edge (4, 5) of weight 7 in MST shown in book **
edge (1, 6) of weight 7 in MST
s1=1 r1=1 s2=6 r2=3
1  set=3 size=2 
2  set=3 size=1 
3  set=3 size=7 
4  set=3 size=1 
5  set=1 size=1 
6  set=3 size=1 
7  set=3 size=1 

1  set=3 size=2 
2  set=3 size=1 
3  set=3 size=7 
4  set=3 size=1 
5  set=1 size=1 
6  set=3 size=1 
7  set=3 size=1 

1  set=3 size=2 
2  set=3 size=1 
3  set=3 size=7 
4  set=3 size=1 
5  set=1 size=1 
6  set=3 size=1 
7  set=3 size=1 

1  set=3 size=2 
2  set=3 size=1 
3  set=3 size=7 
4  set=3 size=1 
5  set=1 size=1 
6  set=3 size=1 
7  set=3 size=1 

*/
