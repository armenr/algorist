/*see README for original credits */

#include "bool.h"
#include "floyd.h"
#include <stdio.h>
#include <stdlib.h>

void initialize_adjacency_matrix(adjacency_matrix *g) {
	int i, j;			

	g -> nvertices = 0;

	for(i = 1; i <= MAXV; i++)
		for(j = 1; j <= MAXV; j++)
			g->weight[i][j] = MAXINT;
}

void read_adjacency_matrix(adjacency_matrix *g, bool directed) {
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y, w;			/* placeholder for edge and weight */

	initialize_adjacency_matrix(g);
  printf("enter # vertices and # edges: ");
	scanf("%d %d", &(g->nvertices), &m);

	for(i=1; i <= m; i++) {
	  printf("enter edge %d (x, y, w): ", i);	
		scanf("%d %d %d", &x, &y, &w);
		g->weight[x][y] = w;
		if(directed == FALSE) 
		  g->weight[y][x] = w;
	}
}

void print_graph(const adjacency_matrix *g) {
	int i,j;	

	for(i = 1; i <= g->nvertices; i++) {
		printf("%d: ", i);

		for(j = 1; j <= g->nvertices; j++)
			if(g->weight[i][j] < MAXINT)
				printf(" %d", j);
		printf("\n");
	}
}

void print_adjacency_matrix(const adjacency_matrix *g) {
  int i,j;  

  for(i = 1; i <= g->nvertices; i++) {
    printf("%3d: ", i);

    for(j = 1; j <= g->nvertices; j++)
      printf(" %3d", g->weight[i][j]);
    printf("\n");
  }
}

void floyd(adjacency_matrix *g) {
	int i,j;			/* dimension counters */
	int k;				/* intermediate vertex counter */
	int through_k;			/* distance through vertex k */

	for(k = 1; k <= g->nvertices; k++)
		for(i = 1; i <= g->nvertices; i++)
			for(j = 1; j <= g->nvertices; j++) {
				through_k = g->weight[i][k]+g->weight[k][j];
				if(through_k < g->weight[i][j])
					g->weight[i][j] = through_k;
			}
}

