/*see README for original credits */

#ifndef GRAPH1_H
#define GRAPH1_H

#include<stdbool.h>
#include"graph-data.h"
#include"skip-list.h"

typedef struct graph {
	skipset* vertices;	/* vertex info */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
	bool directed;			/* is the graph directed? */
	void* item; /* for copying auxilliary data for vertices and edges */
	int item_sz;
} graph;

#include"graph-ops.h"

#endif /* GRAPH1_H */
