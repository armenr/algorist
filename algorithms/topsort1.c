/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include "stack.h"
#include <stdio.h>

static stack sorted;			/* topological ordering of vertices */

void process_vertex_early(int v) {}
void process_vertex_late(int v) {
	push(&sorted, v);
}
void process_edge(int x, int y) {
  int class;              /* edge class */

  class = edge_classification(x, y);
  if(class == BACK) 
    printf("Warning: directed cycle found, not a DAG\n");
}

void topsort(graph *g) {
	int i;				/* counter */

	init_stack(&sorted);
  for(i = 1; i <= g->nvertices; i++)
    if(discovered[i] == FALSE) 
      dfs(g, i);

	print_stack(&sorted);		/* report topological order */
}


int main(void) {
	graph g;
	read_graph(&g, TRUE);
	print_graph(&g);
	topsort(&g);
  return 0;
}

/*
see fig 5.15 pp 179 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./topsort1
enter # vertices and # edges: 7 10
enter edge 1 (x, y, w): 7 1 0
enter edge 2 (x, y, w): 7 6 0
enter edge 3 (x, y, w): 1 3 0
enter edge 4 (x, y, w): 3 6 0
enter edge 5 (x, y, w): 1 2 0
enter edge 6 (x, y, w): 2 3 0
enter edge 7 (x, y, w): 3 5 0
enter edge 8 (x, y, w): 6 5 0
enter edge 9 (x, y, w): 2 4 0
enter edge 10 (x, y, w): 5 4 0
1:  2 3
2:  4 3
3:  5 6
4: 
5:  4
6:  5
7:  6 1
7 1 2 3 6 5 4 = G A B C F E D
*/

