/*see README for original credits */

#ifndef NETFLOW_H
#define NETFLOW_H

#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

typedef struct edgenode {
	int v;				/* neighboring vertex */
	int capacity;			/* capacity of edge */
	int flow;			/* flow through edge */
	int residual;			/* residual capacity of edge */
	struct edgenode *next;          /* next edge in list */
} edgenode;

typedef struct {
	edgenode *edges[MAXV+1];		/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} flow_graph;

bool processed[MAXV+1];		/* which vertices have been processed */
bool discovered[MAXV+1];        /* which vertices have been found */
int parent[MAXV+1];		/* discovery relation */

void add_residual_edges(flow_graph *g);
void augment_path(const flow_graph *g, int start, int end, const int parents[], 
  int volume);
void bfs(const flow_graph *g, int start);
edgenode *find_edge(const flow_graph *g, int x, int y);
void find_path(int start, int end, const int parents[]);
void insert_flow_edge(flow_graph *g, int x, int y, bool directed, int w);
void initialize_graph(flow_graph *g);
void initialize_search(const flow_graph *g);
void netflow(flow_graph *g, int source, int sink);
int path_volume(const flow_graph *g, int start, int end, const int parents[]);
void print_flow_graph(const flow_graph *g);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int x, int y);
void read_flow_graph(flow_graph *g, bool directed);
bool valid_edge(const edgenode *e);

#endif /* NETFLOW_H */

