/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include <stdio.h>

static bool finished = FALSE;

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}

void process_edge(int x, int y) {
	if(parent[x] != y) {	/* found back edge! */
		printf("Cycle from %d to %d:", y, x);
		find_path(y, x, parent);
		printf("\n\n");
		finished = TRUE;
	}
}


int main(void) {
	graph g;

	read_graph(&g, FALSE);
	print_graph(&g);
	initialize_search(&g);
	dfs(&g, 1);
	return 0;
}

/* test run
see fig 5.12 pp 174 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./findcycle 
enter # vertices and # edges: 6 6
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 6 0
enter edge 3 (x, y, w): 2 3 0
enter edge 4 (x, y, w): 3 4 0
enter edge 5 (x, y, w): 4 5 0
enter edge 6 (x, y, w): 5 2 0
1:  6 2
2:  5 3 1
3:  4 2
4:  5 3
5:  2 4
6:  1
Cycle from 6 to 1:
6 1

Cycle from 2 to 1:
2 1

Cycle from 5 to 2:
5 1 2

Cycle from 4 to 5:
4 1 2 5

Cycle from 3 to 4:
3 1 2 5 4

Cycle from 2 to 3:
2 5 4 3

*/
