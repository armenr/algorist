/*see README for original credits */

#include "bool.h"
#include "graph.h"
#include "queue.h"
#include <stdio.h>

void compute_indegrees(const graph *g, int in[]) {
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */

	for(i = 1; i <= g->nvertices; i++) 
	  in[i] = 0;

	for(i = 1; i <= g->nvertices; i++) {
		p = g->edges[i];
		while(p != NULL) {
			in[ p->y ] ++;
			p = p->next;
		}
	}
}
		

void topsort(const graph *g, int sorted[]) {
	int indegree[MAXV+1];		/* indegree of each vertex */
	queue zeroin;			/* vertices of indegree 0 */
	int x, y;			/* current and next vertex */
	int i, j;			/* counters */
	edgenode *p;			/* temporary pointer */

	compute_indegrees(g,indegree);
	init_queue(&zeroin);

	for(i =1 ; i <= g->nvertices; i++)
		if (indegree[i] == 0) enqueue(&zeroin,i);

	j = 0;
	
	while(empty_queue(&zeroin) == FALSE) {
		j++;
		x = dequeue(&zeroin);
		sorted[j] = x;
		p = g->edges[x];
		
		while (p != NULL) {
			y = p->y;
			indegree[y] --;
			if (indegree[y] == 0) enqueue(&zeroin,y);
			p = p->next;
		}
	}

	if (j != g->nvertices)
		printf("Not a DAG -- only %d vertices found\n",j);
}


int main(void) {
	graph g;
	int out[MAXV+1];
	int i;

	read_graph(&g,TRUE);
	print_graph(&g);
	topsort(&g,out);

	for(i = 1; i <= g.nvertices; i++)
		printf(" %d",out[i]);
	printf("\n");
	
  return 0;
}

/*
see fig 5.15 pp 179 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./topsort
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

