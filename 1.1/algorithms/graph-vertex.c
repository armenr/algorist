/*see README for original credits */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include"../ds/stack.h"
#include"graph-vertex.h"

static void pop_strong(graph_search* gs, int v);

void bi_conn_early(graph_search* gs, int v) {
  gs->reachable_ancestor[v] = v;
}

void bi_conn_late(graph_search* gs, int v) {
  if(gs->parent[v] < 1) { /* test if v is the root */
    if(gs->tree_out_degree[v] > 1)
      printf("root articulation vertex: %d \n", v);
    return;
  }

  /* is a given vertex the root of the DFS tree? */
  bool root = gs->parent[gs->parent[v]] < 1; /* test if parent[v] is root */
  if(gs->reachable_ancestor[v] == gs->parent[v] && root)
    printf("parent articulation vertex: %d \n", gs->parent[v]);

  if(gs->reachable_ancestor[v] == v) {
    printf("bridge articulation vertex: %d \n", gs->parent[v]);

    if(gs->tree_out_degree[v] > 0) /* test if v is not a leaf */
      printf("bridge articulation vertex: %d \n", v);
  }

  /* earliest reachable time for v */
  int time_v = gs->entry_time[gs->reachable_ancestor[v]];
  /* earliest reachable time for parent[v] */
  int time_parent = gs->entry_time[gs->reachable_ancestor[gs->parent[v]]];

  if(time_v < time_parent)
    gs->reachable_ancestor[gs->parent[v]] = gs->reachable_ancestor[v];
}

void bi_conn_edge(graph_search* gs, int x, int y) {
  int class = edge_classification(gs, x, y);

  if(class == TREE)
    gs->tree_out_degree[x]++;

  if(class == BACK && gs->parent[x] != y) 
    if(gs->entry_time[y] < gs->entry_time[gs->reachable_ancestor[x]])
      gs->reachable_ancestor[x] = y;
}

void bi_part_edge(graph_search* gs, int x, int y) {
  if(gs->color[x] == gs->color[y]) 
    gs->bipartite = false;
  gs->color[y] = complement(gs->color[x]);
}

void bfs_early(graph_search* gs, int v) {
  printf("processed vertex %d\n", v);
}

void bfs_edge(graph_search* gs, int x, int y) {
  printf("processed edge (%d,%d)\n", x, y);
}

/*void cycle_edge(graph_search* gs, int x, int y) {*/
/*printf("%d %d %d %d\n", x, y, gs->parent[x], gs->parent[y]);*/
/*	if(!(gs->parent[x] == y || gs->parent[y] == x || gs->parent[x] == NONE)) {	*/
/*		printf("Cycle from %d to %d\n", y, x);*/
/*		gs->dfs_finished = true;*/
/*	}*/
/*}*/

void dfs_early(graph_search* gs, int v) {
	gs->entry_time[v] = gs->time++;
	printf("entered vertex %d at time %d\n", v, gs->entry_time[v]);
}

void dfs_late(graph_search* gs, int v) {
	gs->exit_time[v] = gs->time++;
  printf("left vertex %d at time %d\n", v, gs->exit_time[v]);
}

void dfs_edge(graph_search* gs, int x, int y) {
	int class = edge_classification(gs, x, y);

	switch(class) {
	  case BACK:
  	  printf("back edge (%d, %d)\n", x, y);
	    break;
	  case TREE:
	  printf("tree edge (%d,%d)\n", x, y);
	    break;
	  case FORWARD:
  	  printf("forward edge (%d,%d)\n", x, y);
	    break;
	  case CROSS:
  	  printf("cross edge (%d,%d)\n", x, y);
	    break;
	  default:
  	  printf("edge (%d,%d)\n not in valid class=%d", x, y, class);
	}  
}

void strong_early(graph_search* gs, int v) {
	gs->entry_time[v] = gs->time++;
	push_stack(&(gs->strong), &v, sizeof(int));
}

void strong_late(graph_search* gs, int v) {
	gs->exit_time[v] = gs->time++;

	if(gs->low[v] == v) /* edge (parent[v],v) cuts off scc */
		pop_strong(gs, v);

  if(gs->parent[v] != NONE) {
	  if(gs->entry_time[gs->low[v]] < gs->entry_time[gs->low[gs->parent[v]]])
		  gs->low[gs->parent[v]] = gs->low[v];
  } 
}

void strong_edge(graph_search* gs, int x, int y) {
	int class = edge_classification(gs, x, y);

	if(class == BACK) {
		if(gs->entry_time[y] < gs->entry_time[gs->low[x]])
			gs->low[x] = y;
	}

	if(class == CROSS) {
		if(gs->scc[y] == NONE)	/* component not yet assigned */
			if(gs->entry_time[y] < gs->entry_time[gs->low[x]] )
      	gs->low[x] = y;
	}
}

void top_sort_late(graph_search* gs, int v) {
	push_stack(&(gs->top_sort), &v, sizeof(int));
}

void top_sort_edge(graph_search* gs, int x, int y) {
  int class = edge_classification(gs, x, y);
  if(class == BACK) 
    printf("Warning: directed cycle found, not a DAG\n");
}

static void pop_strong(graph_search* gs, int v) {
  gs->components_found++;
	printf("%d is in component %d \n", v, gs->components_found);
	gs->scc[v] = gs->components_found;
	
  int* ip = (int*)pop_stack(&(gs->strong));
  int t = (ip != NULL ? *ip : NONE);
  free(ip);	  

	while(!(t == v || empty_stack(gs->strong))) {
		gs->scc[t] = gs->components_found;
		printf("%d is in component %d with %d \n", t, gs->components_found, v);

    ip = (int*)pop_stack(&(gs->strong));
    t = (ip != NULL ? *ip : NONE);

    free(ip);	  
	}
}

