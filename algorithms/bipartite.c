/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include "queue.h"
#include<stdio.h>

#define UNCOLORED	0	/* vertex not yet colored */
#define WHITE		1	/* white vertex */
#define BLACK		2	/* black vertex */

static int color[MAXV+1];		/* assigned color of v */
static bool bipartite;			/* is the graph bipartite? */

static int complement(int color);

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {
	if(color[x] == color[y]) {
		bipartite = FALSE;
		printf("Warning: graph not bipartite, due to (%d,%d)\n",x, y);
	}	
	color[y] = complement(color[x]);
}

static int complement(int color) {
	if(color == WHITE) return(BLACK);
	if(color == BLACK) return(WHITE);
	
	return(UNCOLORED);
}

static void twocolor(graph *g) {
	int i;				

	for(i = 1; i <= (g->nvertices); i++) 
		color[i] = UNCOLORED;

	bipartite = TRUE;
 
	initialize_search((const graph *)&g);

	for(i = 1; i <= (g->nvertices); i++)
		if(discovered[i] == FALSE) {
			color[i] = WHITE;
			bfs(g, i);
		}
}

int main(void) {
	graph g;
	int i;

	read_graph(&g, FALSE);
	print_graph(&g);
	twocolor(&g);

	for(i = 1; i <= (g.nvertices); i++)
		printf(" %d", color[i]);
	printf("\n");
	
	return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./bipartite 
enter # vertices and # edges: 6 7
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 5 0
enter edge 3 (x, y, w): 1 6 0
enter edge 4 (x, y, w): 2 5 0
enter edge 5 (x, y, w): 2 3 0
enter edge 6 (x, y, w): 3 4 0
enter edge 7 (x, y, w): 5 4 0
1:  6 5 2
2:  3 5 1
3:  4 2
4:  5 3
5:  4 2 1
6:  1
Warning: graph not bipartite, due to (5,2)
 1 1 2 1 2 2

osman@osman-desktop:~/src/algorithms$ ./bipartite 
enter # vertices and # edges: 3 2
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 3 0
1:  3 2
2:  1
3:  1
 1 2 2

*/
