/*see README for original credits */

#ifndef FLOYD_H
#define FLOYD_H

#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

#define MAXINT	100007

typedef struct {
	int v;				/* neighboring vertex */
	int weight;			/* edge weight */
	bool in;			/* is the edge "in" the solution? */
} edge;

typedef struct {
	edge edges[MAXV+1][MAXDEGREE];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;

typedef struct {
  int weight[MAXV+1][MAXV+1];    	/* adjacency/weight info */
  int nvertices;                  /* number of vertices in the graph */
} adjacency_matrix;

void initialize_adjacency_matrix(adjacency_matrix *g);
void floyd(adjacency_matrix *g);
void read_adjacency_matrix(adjacency_matrix *g, bool directed);
void print_graph(const adjacency_matrix *g);
void print_adjacency_matrix(const adjacency_matrix *g);

#endif /* FLOYD_H */


