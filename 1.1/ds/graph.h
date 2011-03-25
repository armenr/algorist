/*see README for original credits */

#ifndef GRAPH_H
#define GRAPH_H

#include"item.h"
#include<stdbool.h>
#include<stdlib.h>

#define	MAXV		100		/* maximum number of vertices */

/*	DFS edge types		*/

#define LOOP    -1  /* self loop */
#define TREE		0		/* tree edge */
#define BACK		1		/* back edge */
#define CROSS		2		/* cross edge */
#define FORWARD		3		/* forward edge */

typedef struct edgenode {
	int y;				/* adjancency info */
	int weight;			/* edge weight, if any */
	struct edgenode* next;		/* next edge in list */
} edgenode;

typedef struct {
	edgenode* edges;	/* adjacency info */
  item_type item; /* data item */
	int degree;		/* outdegree of each vertex */
} vertex;

typedef struct {
	vertex vertices[MAXV+1];	/* vertex info */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
	bool directed;			/* is the graph directed? */
} graph;

void clear_graph(graph* g);
void delete_edge(graph* g, int x, int y, bool directed);
void delete_vertex(graph* g, int x);
void initialize_graph(graph* g, bool directed);
void insert_edge(graph* g, int x, int y, int w, bool directed);
void insert_vertex(graph* g, int x, const item_type i, size_t n);
void print_graph(const graph* g, void (*print_item)(void*));
void read_graph(graph* g, bool directed);

#endif /* GRAPH_H */
