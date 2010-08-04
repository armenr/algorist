/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include <stdio.h>

void process_vertex(int v) {
  printf(" %d",v);
}
void process_vertex_early(int v) {
  printf(" %d",v);
}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

static void connected_components(graph *g) {
	int c;				/* component number */
	int i;				/* counter */

	initialize_search((const graph *)g);

	c = 0;
	for(i = 1; i <= g->nvertices; i++)
		if(discovered[i] == FALSE) {
			c++;
			printf("Component %d:",c);
			bfs(g, i);
			printf("\n");
		}
}

int main(void) {
	graph g;

	read_graph(&g,FALSE);
	print_graph(&g);
	connected_components(&g);
	
	return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./connected 
enter # vertices and # edges: 6 7
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 5 0
enter edge 3 (x, y, w): 1 6 0
enter edge 4 (x, y, w): 2 3 0
enter edge 5 (x, y, w): 2 5 0
enter edge 6 (x, y, w): 3 4 0
enter edge 7 (x, y, w): 5 4 0
1:  6 5 2
2:  5 3 1
3:  4 2
4:  5 3
5:  4 2 1
6:  1
Component 1: 1 6 5 2 4 3

plus a simple 3 node tree: 7-8, 7-9

osman@osman-desktop:~/src/algorithms$ ./connected 
enter # vertices and # edges: 9 9
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 5 0
enter edge 3 (x, y, w): 1 6 0
enter edge 4 (x, y, w): 2 5 0
enter edge 5 (x, y, w): 2 3 0
enter edge 6 (x, y, w): 3 4 0
enter edge 7 (x, y, w): 5 4 0
enter edge 8 (x, y, w): 7 8 0
enter edge 9 (x, y, w): 7 9 0
1:  6 5 2
2:  3 5 1
3:  4 2
4:  5 3
5:  4 2 1
6:  1
7:  9 8
8:  7
9:  7
Component 1: 1 6 5 2 4 3
Component 2: 7 9 8

*/
