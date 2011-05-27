/*see README for original credits */

#ifndef GRAPH_DATA
#define GRAPH_DATA

/*	DFS edge types		*/

#define LOOP    -1  /* self loop */
#define TREE		0		/* tree edge */
#define BACK		1		/* back edge */
#define CROSS		2		/* cross edge */
#define FORWARD		3		/* forward edge */

typedef struct edge_node {
	int y;				/* adjancency info */
	int weight;			/* edge weight, if any */
  void* item; /* data item */
	struct edge_node* next;		/* next edge in list */
} edge_node;

typedef struct vertex {
	edge_node* edges;	/* adjacency info */
  void* item; /* data item */
	int degree;		/* outdegree of each vertex */
} vertex;

#endif /* GRAPH_DATA */
