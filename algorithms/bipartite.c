/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include "queue.h"
#include<stdio.h>

#define UNCOLORED	0	/* vertex not yet colored */
#define WHITE		1	/* white vertex */
#define BLACK		2	/* black vertex */

int color[MAXV+1];		/* assigned color of v */
bool bipartite;			/* is the graph bipartite? */

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}

int complement(int color) {
	if(color == WHITE) return(BLACK);
	if(color == BLACK) return(WHITE);
	
	return(UNCOLORED);
}

void process_edge(int x, int y) {
	if(color[x] == color[y]) {
		bipartite = FALSE;
		printf("Warning: graph not bipartite, due to (%d,%d)\n",x, y);
	}	
	color[y] = complement(color[x]);
}

void twocolor(graph *g) {
	int i;				

	for(i = 1; i <= (g->nvertices); i++) 
		color[i] = UNCOLORED;

	bipartite = TRUE;
 
	initialize_search((const graph *)&g);

	for(i = 1; i <= (g->nvertices); i++)
		if(discovered[i] == FALSE) {
			color[i] = WHITE;
			bfs(g,i);
		}
}

int main(void) {
	graph g;
	int i;

	read_graph(&g,FALSE);
	print_graph(&g);

	twocolor(&g);

	for(i = 1; i <= (g.nvertices); i++)
		printf(" %d",color[i]);
	printf("\n");
	
	return 0;
}
