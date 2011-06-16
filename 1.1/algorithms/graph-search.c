/*see README for original credits */

#include<stdlib.h>
#include"graph-search.h"
#include"graph-vertex.h"
#include"../ds/queue.h"

void articulation_vertices(graph* g, graph_search* gs, 
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y)) {

  int i; 
  for(i = 0; i < g->nvertices; i++)
    if(!gs->discovered[i]) 
      dfs(g, gs, i, process_vertex_early, process_vertex_late, process_edge);
}

void clear_search(graph_search* gs) {
	clear_stack(gs->strong);
	clear_stack(gs->top_sort);
  free(gs->color);
  free(gs->component);
  free(gs->discovered);
  free(gs->entry_time);
  free(gs->exit_time);
  free(gs->low);
  free(gs->parent);
  free(gs->path);
  free(gs->processed);
  free(gs->reachable_ancestor);
  free(gs->scc);
  free(gs->tree_out_degree);
}

/*bi-partite function*/
int complement(int color) {
/*a faster way might be to just negate the color 0 == -0?*/
	if(color == WHITE) 
	  return BLACK;
	if(color == BLACK) 
	  return WHITE;
	
	return UNCOLORED;
}

/*
BFS(G, s)
  for each vertex u ∈ V [G] − {s} do
    state[u] = “undiscovered”
    p[u] = nil, i.e. no parent is in the BFS tree

  state[s] = “discovered”
  p[s] = nil
  Q = {s}

  while Q = ∅ do
    u = dequeue[Q]
    process vertex u as desired

    for each v ∈ Adj[u] do
      process edge (u, v) as desired

      if state[v] = “undiscovered” then
        state[v] = “discovered”
        p[v] = u
        enqueue[Q, v]

    state[u] = “processed”
*/
/*void bfs(const graph* g, graph_search* gs, int start,*/
/*  void (*process_vertex_early)(graph_search* gs, int v)) {*/
void bfs(const graph* g, graph_search* gs, int start, 
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y)) {

	queue q;			/* queue of vertices to visit */
	init_queue(&q);
	en_queue(&q, &start, sizeof(int));

	gs->discovered[start] = true;
  
	while(!empty_queue(&q)) {
    int* ip = (int*)de_queue(&q);
    int v = NONE;
    
    if(ip != NULL) {
  		v = *ip;
	    free(ip);
    }

    if(process_vertex_early != NULL) 
  		process_vertex_early(gs, v);

		gs->processed[v] = true;
    gs->component[v] = start;
		
  	const vertex* vert = find_vertex(g, v);
		const edge_node* p = vert->edges;
		
		while(p != NULL) {
	    int y = p->y;

	    if(!gs->processed[y] || g->directed) {
        if(process_edge != NULL) 
      		process_edge(gs, v, y);
	    }
    		
	    if(!gs->discovered[y]) {
  			en_queue(&q, &y, sizeof(int));
  			gs->discovered[y] = true;
	  		gs->parent[y] = v;
      }

	    p = p->next;
		}

    if(process_vertex_late != NULL) 
  		process_vertex_late(gs, v);
	}
	
	clear_queue(&q);
}

void connected_components(graph* g, graph_search* gs, 
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y)) {

	int i; /* component number */
	for(i = 0; i < g->nvertices; i++)
		if(!gs->discovered[i]) 
			bfs(g, gs, i, process_vertex_early, process_vertex_late, process_edge);
}

/*
DFS(G, u)
  state[u] = “discovered”
  process vertex u if desired
  entry[u] = time
  time = time + 1

  for each v ∈ Adj[u] do
    process edge (u, v) if desired

    if state[v] = “undiscovered” then
      p[v] = u
      DFS(G, v)

  state[u] = “processed”
  exit[u] = time
  time = time + 1
*/
void dfs(const graph* g, graph_search* gs, int v, 
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y)) {

	if(gs->dfs_finished) 
	  return;		/* allow for search termination */
  
	gs->discovered[v] = true;
	
  if(process_vertex_early != NULL) 
  	process_vertex_early(gs, v);

	const vertex* vert = find_vertex(g, v);
	const edge_node* p = vert->edges;
	
	while(p != NULL) {
		int y = p->y;

		if(!gs->discovered[y]) {
			gs->parent[y] = v;

      if(process_edge != NULL) 
  			process_edge(gs, v, y);

			dfs(g, gs, y, process_vertex_early, process_vertex_late, process_edge);

		} else if(!gs->processed[y] || g->directed) {
      if(process_edge != NULL) 
  			process_edge(gs, v, y);
		}

	  if(gs->dfs_finished) 
	    return;		/* allow for search termination */

		p = p->next;
	}

  if(process_vertex_late != NULL) 
  	process_vertex_late(gs, v);
  	
	gs->processed[v] = true;
}


int edge_classification(const graph_search* gs, int x, int y) {
  if(gs->parent[y] == x) 
    return TREE;
    
  if(gs->processed[y]) {
    if(gs->entry_time[y] > gs->entry_time[x]) 
      return FORWARD;
    else if(gs->entry_time[y] < gs->entry_time[x]) 
      return CROSS;

  } else {  /*not processed*/
    if(gs->discovered[y]) 
      return BACK;
  }

  return LOOP;
}

void find_path(const graph* g, graph_search* gs, int start, int end) {
  static int i = 0;
  
	if((start == end) || (end == NONE)) {
    int j;
    for(j = 0; j < g->nvertices; j++) 
      gs->path[j] = NONE;

    i = 0;
	  gs->path[i++] = start;
  
  }	else {
		find_path(g, gs, start, gs->parent[end]);
	  gs->path[i++] = end;
	}
}

void init_search(const graph* g, graph_search* gs) {
	gs->time = 0;
  gs->dfs_finished = false;
	init_stack(&(gs->top_sort));

	gs->components_found = 0;
	init_stack(&(gs->strong));

  gs->color = malloc(g->nvertices * sizeof(int));
  gs->component = malloc(g->nvertices * sizeof(int));
  gs->discovered = malloc(g->nvertices * sizeof(bool));
  gs->entry_time = malloc(g->nvertices * sizeof(int));
  gs->exit_time = malloc(g->nvertices * sizeof(int));
  gs->low = malloc(g->nvertices * sizeof(int));
  gs->parent = malloc(g->nvertices * sizeof(int));
  gs->path = malloc(g->nvertices * sizeof(int));
  gs->processed = malloc(g->nvertices * sizeof(bool));
  gs->reachable_ancestor = malloc(g->nvertices * sizeof(int));
  gs->scc = malloc(g->nvertices * sizeof(int));
  gs->tree_out_degree = malloc(g->nvertices * sizeof(int));

  int i;
  for(i = 0; i < g->nvertices; i++) {
		gs->color[i] = UNCOLORED;
    gs->component[i] = gs->parent[i] = gs->path[i] = gs->scc[i] = NONE;
    gs->entry_time[i] = gs->exit_time[i] = gs->tree_out_degree[i] = 0;
	  gs->low[i] = i;
    gs->processed[i] = gs->discovered[i] = false;
  }
}

void strong_components(const graph *g, graph_search* gs) {
	int i;
  for(i = 0; i < g->nvertices; i++)
    if(!gs->discovered[i]) 
      dfs(g, gs, i, strong_early, strong_late, strong_edge);
}
  
void top_sort(const graph *g, graph_search* gs) {
	int i;
  for(i = 0; i < g->nvertices; i++)
    if(!gs->discovered[i]) 
      dfs(g, gs, i, NULL, top_sort_late, top_sort_edge);
}

void two_color(graph *g, graph_search* gs,
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y)) {
  
	gs->bipartite = true;

  int i; 
	for(i = 0; i < g->nvertices; i++)
		if(!gs->discovered[i]) {
			gs->color[i] = WHITE;
			bfs(g, gs, i, process_vertex_early, process_vertex_late, process_edge);
		}
}

