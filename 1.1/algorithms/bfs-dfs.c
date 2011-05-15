/*see README for original credits */

#include"bfs-dfs.h"
#include"../ds/queue.h"
#include<stdio.h>
#include<stdlib.h>

extern void process_edge(int x, int y);
extern void process_vertex_early(int v); 
extern void process_vertex_late(int v);

void clear_search(void) {
  free(processed);
  free(discovered);
  free(parent);
  free(entry_time);
  free(exit_time);
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
void bfs(const graph *g, int start) {
	queue q;			/* queue of vertices to visit */
	init_queue(&q);
	en_queue(&q, &start, sizeof(int));

	discovered[start] = true;

	while(!empty_queue(&q)) {
    int* ip = (int*)de_queue(&q);
    int v = -1;
    
    if(ip != NULL) {
  		v = *ip;
	    free(ip);
    }

		process_vertex_early(v);
		processed[v] = true;
		
  	const vertex* vert = find_vertex(g, v);
		edgenode* p = vert->edges;
		
		while(p != NULL) {
	    int y = p->y;

	    if(!processed[y] || g->directed)
    		process_edge(v, y);
    		
	    if(!discovered[y]) {
  			en_queue(&q, &y, sizeof(int));
  			discovered[y] = true;
	  		parent[y] = v;
      }
      
	    p = p->next;
		}
		process_vertex_late(v);
	}
	
	clear_queue(&q);
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
void dfs(const graph *g, int v) {
	discovered[v] = true;
  entry_time[v] = time;
  time++;
	process_vertex_early(v);

	const vertex* vert = find_vertex(g, v);
	edgenode* p = vert->edges;
	
	while(p != NULL) {
		int y = p->y;

		if(!discovered[y]) {
			parent[y] = v;
			process_edge(v, y);
			dfs(g, y);

		} else if(!processed[y] || g->directed)
			process_edge(v, y);

		p = p->next;
	}

	process_vertex_late(v);
  exit_time[v] = time;
  time++;
	processed[v] = true;
}


int edge_classification(int x, int y) {
  if(parent[y] == x) 
    return TREE;
    
  if(processed[y]) {
    if(entry_time[y] > entry_time[x]) 
      return FORWARD;
    else if(entry_time[y] < entry_time[x]) 
      return CROSS;

  } else {  /*not processed*/
    if(discovered[y]) 
      return BACK;
  }

  printf("Warning: self loop (%d,%d)\n", x ,y);
  return LOOP;
}

void find_path(int start, int end, const int parents[]) {
	if((start == end) || (end == -1))
		printf("\n%d", start);
	else {
		find_path(start, parents[end], parents);
		printf(" %d", end);
	}
}

void initialize_search(const graph *g) {
	time = 0;

  processed = malloc(g->nvertices * sizeof(bool));
  discovered = malloc(g->nvertices * sizeof(bool));
  parent = malloc(g->nvertices * sizeof(int));
  entry_time = malloc(g->nvertices * sizeof(int));
  exit_time = malloc(g->nvertices * sizeof(int));

  int i;

  for (i = 0; i < g->nvertices; i++) {
    processed[i] = discovered[i] = false;
    parent[i] = -1;
  }
}
