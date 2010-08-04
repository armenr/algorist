/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include <stdio.h>

#define MAXINT	100007

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

void prim(const graph *g, int start) {
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */
	bool intree[MAXV+1];		/* is the vertex in the tree yet? */
	int distance[MAXV+1];		/* cost of adding to tree */
	int v;				/* current vertex to process */
	int w;				/* candidate next vertex */
	int weight;			/* edge weight */
	int dist;			/* best current distance from start */

	for(i = 1; i <= g->nvertices; i++) {
		intree[i] = FALSE;
		distance[i] = MAXINT;
		parent[i] = -1;
	}

	distance[start] = 0;
	v = start;

	while(intree[v] == FALSE) {

		intree[v] = TRUE;
		p = g->edges[v];

		while(p != NULL) {

			w = p->y;
			weight = p->weight;

			if((distance[w] > weight) && (intree[w] == FALSE)) {
				distance[w] = weight;
				parent[w] = v;
			}
			p = p->next;
		}

		v = 1;
		dist = MAXINT;

		for(i = 1; i <= g->nvertices; i++) 
			if((intree[i] == FALSE) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	}
}

int main(void) {
	graph g;
	int i;

	read_graph(&g, FALSE);
	print_graph(&g);
	prim(&g, 1);

  for(i = 1; i <= g.nvertices; i++) {
    /*printf(" %d parent=%d\n",i,parent[i]);*/
    find_path(1, i, parent);
  }
  printf("\n");
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

osman@osman-desktop:~/src/algorithms$ ./prim
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

1
1 5 4 3 6 2
1 5 4 3
1 5 4
1 5
1 5 4 3 6
1 5 4 3 7
*/
