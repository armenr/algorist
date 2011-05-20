/*see README for original credits */

#include"graph-search.h"
#include"../ds/queue.h"
#include<stdlib.h>

static int complement(int color);

extern void process_edge(graph_search* gs, int x, int y);
extern void process_vertex_early(graph_search* gs, int v); 
extern void process_vertex_late(graph_search* gs, int v);

void articulation_vertices(graph* g, graph_search* gs) {
  int i; 
  for(i = 0; i < g->nvertices; i++)
    if(gs->discovered[i] == false) 
      dfs(g, gs, i);
}

void clear_search(graph_search* gs) {
  free(gs->color);
  free(gs->component);
  free(gs->discovered);
  free(gs->entry_time);
  free(gs->exit_time);
  free(gs->parent);
  free(gs->path);
  free(gs->processed);
  free(gs->reachable_ancestor);
  free(gs->tree_out_degree);
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
void bfs(const graph* g, graph_search* gs, int start) {
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

		process_vertex_early(gs, v);

		gs->processed[v] = true;
    gs->component[v] = start;
		
  	const vertex* vert = find_vertex(g, v);
		const edgenode* p = vert->edges;
		
		while(p != NULL) {
	    int y = p->y;

	    if(!gs->processed[y] || g->directed) {
	    
	      if(gs->color[v] == gs->color[y]) 
		      gs->bipartite = false;
	      gs->color[y] = complement(gs->color[v]);
	      
    		process_edge(gs, v, y);
	    }
    		
	    if(!gs->discovered[y]) {
  			en_queue(&q, &y, sizeof(int));
  			gs->discovered[y] = true;
	  		gs->parent[y] = v;
      }
      
	    p = p->next;
		}
		process_vertex_late(gs, v);
	}
	
	clear_queue(&q);
}

void connected_components(graph* g, graph_search* gs) {
	int i; /* component number */
	for(i = 0; i < g->nvertices; i++)
		if(!gs->discovered[i]) 
			bfs(g, gs, i);
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
void dfs(const graph* g, graph_search* gs, int v) {
	gs->discovered[v] = true;
  gs->entry_time[v] = gs->time;
  gs->time++;
	process_vertex_early(gs, v);

	const vertex* vert = find_vertex(g, v);
	const edgenode* p = vert->edges;
	
	while(p != NULL) {
		int y = p->y;

		if(!gs->discovered[y]) {
			gs->parent[y] = v;
			process_edge(gs, v, y);
			dfs(g, gs, y);

		} else if(!gs->processed[y] || g->directed)
			process_edge(gs, v, y);

		p = p->next;
	}

	process_vertex_late(gs, v);
  gs->exit_time[v] = gs->time;
  gs->time++;
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

  gs->color = malloc(g->nvertices * sizeof(int));
  gs->component = malloc(g->nvertices * sizeof(int));
  gs->discovered = malloc(g->nvertices * sizeof(bool));
  gs->entry_time = malloc(g->nvertices * sizeof(int));
  gs->exit_time = malloc(g->nvertices * sizeof(int));
  gs->parent = malloc(g->nvertices * sizeof(int));
  gs->path = malloc(g->nvertices * sizeof(int));
  gs->processed = malloc(g->nvertices * sizeof(bool));
  gs->reachable_ancestor = malloc(g->nvertices * sizeof(int));
  gs->tree_out_degree = malloc(g->nvertices * sizeof(int));

  int i;
  for(i = 0; i < g->nvertices; i++) {
		gs->color[i] = UNCOLORED;
    gs->processed[i] = gs->discovered[i] = false;
    gs->component[i] = gs->parent[i] = gs->path[i] = NONE;
    gs->tree_out_degree[i] = 0;
  }
}

void twocolor(graph *g, graph_search* gs) {
	gs->bipartite = true;

  int i; 
	for(i = 0; i < g->nvertices; i++)
		if(!gs->discovered[i]) {
			gs->color[i] = WHITE;
			bfs(g, gs, i);
		}
}

static int complement(int color) {
/*a faster way might be to just negate the color 0 == -0?*/
	if(color == WHITE) 
	  return BLACK;
	if(color == BLACK) 
	  return WHITE;
	
	return UNCOLORED;
}

