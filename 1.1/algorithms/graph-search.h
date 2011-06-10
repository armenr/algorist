/*see README for original credits */

#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include<stdbool.h>
#include"../ds/graph1.h"
#include"../ds/stack.h"

#define NONE -1
#define UNCOLORED	0	/* vertex not yet colored */
#define WHITE		1	/* white vertex */
#define BLACK		2	/* black vertex */

typedef struct graph_search {
  /*searches*/
  bool* processed;	  /* which vertices have been processed */
  bool* discovered;  /* which vertices have been found */
  int* parent;	      /* discovery relation */

  int* entry_time;    /* time of vertex entry */
  int* exit_time;     /* time of vertex exit */
  int time;           /* current event time */

  bool dfs_finished;  /* terminate dfs search early, e.g. finding cycles*/
  
  /*bi-connections  */
  int* reachable_ancestor; /* earliest reachable ancestor of v */
  int* tree_out_degree; /* DFS tree outdegree of v */

  /*connected components  */
  int* component; 

  /*find path  */
  int* path; 

  /*two coloring  */
  int* color; /* assigned color of v */
  bool bipartite; /* is the graph bipartite? */
  
  /*topological sort*/
  stack top_sort;			/* topological ordering of vertices */
  
  /* strong components */
  int* low;		/* oldest vertex surely in component of v */
  int* scc;		/* strong component number for each vertex */

  stack strong;			/* active vertices of unassigned component */
  int components_found;		/* number of strong components identified */
  
} graph_search;

void articulation_vertices(graph* g, graph_search* gs,
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y));

void bfs(const graph* g, graph_search* gs, int start,
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y));

void clear_search(graph_search* gs);
int complement(int color);  /*bi-partite function*/

void connected_components(graph* g, graph_search* gs,
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y));

void dfs(const graph* g, graph_search* gs, int v,
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y));

int edge_classification(const graph_search* gs, int x, int y);
void find_path(const graph* g, graph_search* gs, int start, int end);
void init_search(const graph* g, graph_search* gs);

void strong_components(const graph *g, graph_search* gs);
void top_sort(const graph *g, graph_search* gs);

void two_color(graph *g, graph_search* gs,
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y));

#endif /* GRAPH_SEARCH_H */
