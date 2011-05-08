/*see README for original credits */

#ifndef GRAPH_H
#define GRAPH_H

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
  void* item; /* data item */
	int degree;		/* outdegree of each vertex */
} vertex;

typedef struct {
	vertex vertices[MAXV];	/* vertex info */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
	bool directed;			/* is the graph directed? */
} graph;

void clear_graph(graph* g);
void delete_edge(graph* g, int x, int y);
void delete_vertex(graph* g, int v);
void initialize_graph(graph* g, bool directed);
void insert_edge(graph* g, int x, int y, int w);
void insert_vertex(graph* g, int v, const void* item, size_t sz);
void print_graph(const graph* g, void (*print_item)(const void* item));

#endif /* GRAPH_H */
