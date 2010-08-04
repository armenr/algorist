/*see README for original credits */

#ifndef GRAPH_H
#define GRAPH_H

#define	MAXV		100		/* maximum number of vertices */
#define NULL		0		/* null pointer */

/*	DFS edge types		*/

#define LOOP    -1  /* self loop */
#define TREE		0		/* tree edge */
#define BACK		1		/* back edge */
#define CROSS		2		/* cross edge */
#define FORWARD		3		/* forward edge */

typedef struct edgenode {
	int y;				/* adjancency info */
	int weight;			/* edge weight, if any */
	struct edgenode *next;		/* next edge in list */
} edgenode;

typedef struct {
	edgenode *edges[MAXV+1];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
	int directed;			/* is the graph directed? */
} graph;

void delete_edge(graph *g, int x, int y, bool directed);
void initialize_graph(graph *g, bool directed);
void insert_edge(graph *g, int x, int y, bool directed, int w);
void print_graph(const graph *g);
void read_graph(graph *g, bool directed);

#endif /* GRAPH_H */
