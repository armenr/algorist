/*see README for original credits */

#include "bool.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void initialize_graph(graph *g, bool directed) {
	int i;				

	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;

	for(i = 1; i <= MAXV; i++) g->degree[i] = 0;
	for(i = 1; i <= MAXV; i++) g->edges[i] = NULL;
}

void read_graph(graph *g, bool directed) {
	int i;				
	int m;				/* number of edges */
	int x, y, w;			/* vertices in edge (x,y) and weught*/

	initialize_graph(g, directed);

  printf("enter # vertices and # edges: ");
	scanf("%d %d", &(g->nvertices), &m);

	for(i = 1; i <= m; i++) {
	  printf("enter edge %d (x, y, w): ", i);	
		scanf("%d %d %d",&x, &y, &w);
		insert_edge(g, x, y, directed, w);
	}
}

void insert_edge(graph *g, int x, int y, bool directed, int w) {
	edgenode *p;			/* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = w;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;		/* insert at head of list */
	g->degree[x] ++;

	if(directed == FALSE)
		insert_edge(g, y, x, TRUE, w);
	else
		g->nedges ++;
}

void delete_edge(graph *g, int x, int y, bool directed) {
	edgenode *p, *p_back;		/* temporary pointers */

	p = g->edges[x];
	p_back = NULL;

	while (p != NULL) 
		if(p->y == y) {
			g->degree[x] --;
			if(p_back != NULL) 
				p_back->next = p->next;
			else
				g->edges[x] = p->next;

			free(p);

			if(directed == FALSE)
				delete_edge(g,y,x,TRUE);
			else
				g->nedges --;

			return;
		}
		else
			p = p->next;

	printf("Warning: deletion(%d,%d) not found in g.\n",x,y);
}

void print_graph(const graph *g) {
	int i;				
	edgenode *p;			/* temporary pointer */

	for(i = 1; i <= g->nvertices; i++) {
		printf("%d: ", i);
		p = g->edges[i];
		while(p != NULL) {
			printf(" %d", p->y);
			p = p->next;
		}
		printf("\n");
	}
}
