/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include "stack.h"
#include <stdio.h>

static int low[MAXV+1];		/* oldest vertex surely in component of v */
static int scc[MAXV+1];		/* strong component number for each vertex */

static stack active;			/* active vertices of unassigned component */
static int components_found;		/* number of strong components identified */

void pop_component(int v) {
  int t;                  /* vertex placeholder */

	components_found = components_found + 1;
	printf("%d is in component %d \n", v, components_found);

	scc[ v ] = components_found;
	while((t = pop(&active)) != v) {
		scc[ t ] = components_found;
		printf("%d is in component %d with %d \n", t, components_found, v);
	}
}

void process_vertex_early(int v) {
	/*printf("entered vertex %d at time %d\n",v, entry_time[v]);*/
	push(&active, v);
}

void process_vertex_late(int v) {
  /*printf("exit vertex %d at time %d\n",v, exit_time[v]);*/

	if(low[v] == v) { 		/* edge (parent[v],v) cuts off scc */
/*printf("strong commonent started backtracking from %d\n",v);*/
		pop_component(v);
	}

	if(entry_time[low[v]] < entry_time[low[parent[v]]])
		low[parent[v]] = low[v];
}

void process_edge(int x, int y) {
	int class;		/* edge class */

	class = edge_classification(x, y);
/*printf("(%d,%d) class %d\n", x,y,class);*/

	if(class == BACK) {
		if(entry_time[y] < entry_time[ low[x] ] )
			low[x] = y;
/*printf("process BACK (%d,%d) low[%d]=%d  low[%d]=%d\n",x,y,x,low[x],y,low[y]);*/
	}

	if(class == CROSS) {
		if(scc[y] == -1)	/* component not yet assigned */
			if(entry_time[y] < entry_time[ low[x] ] )
      	low[x] = y;
/*printf("process CROSS (%d,%d) low[%d]=%d  low[%d]=%d\n",x,y,x,low[x],y,low[y]);*/
	}
}

void strong_components(graph *g) {
	int i;				/* counter */

	for(i = 1; i <= (g->nvertices); i++) {
		low[i] = i;
		scc[i] = -1;
	}

	components_found = 0;
	init_stack(&active);
	initialize_search((const graph *)&g);

	for(i = 1; i <= (g->nvertices); i++)
		if(discovered[i] == FALSE) {
			dfs(g, i);
			/*pop_component(i);*/
		}
}

int main(void) {
	graph g;

	read_graph(&g, TRUE);
	print_graph(&g);
	strong_components(&g);
	return 0;
}

/* test run
see fig 5.16 pp 182 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./strong
enter # vertices and # edges: 8 12
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 2 3 0
enter edge 3 (x, y, w): 2 4 0
enter edge 4 (x, y, w): 4 6 0
enter edge 5 (x, y, w): 4 8 0
enter edge 6 (x, y, w): 8 6 0
enter edge 7 (x, y, w): 6 7 0
enter edge 8 (x, y, w): 7 5 0
enter edge 9 (x, y, w): 5 6 0
enter edge 10 (x, y, w): 2 5 0
enter edge 11 (x, y, w): 4 1 0
enter edge 12 (x, y, w): 3 1 0
1:  2
2:  5 4 3
3:  1
4:  1 8 6
5:  6
6:  7
7:  5
8:  6
5 is in component 1 
7 is in component 1 with 5 
6 is in component 1 with 5 
8 is in component 2 
1 is in component 3 
3 is in component 3 with 1 
4 is in component 3 with 1 
2 is in component 3 with 1
*/
