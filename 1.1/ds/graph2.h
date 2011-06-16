/*see README for original credits */

#ifndef GRAPH2_H
#define GRAPH2_H

#include<stdbool.h>
#include"graph-data.h"

#define	MAXV		4		/* maximum number of vertices */

typedef struct graph {
	vertex** vertices;	/* vertex info */
	int v_sz; /*max size before resize called*/
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
	bool directed;			/* is the graph directed? */
	void* item; /* for copying auxilliary data for vertices and edges */
	int item_sz;
} graph;

#include"graph-ops.h"

#endif /* GRAPH2_H */
