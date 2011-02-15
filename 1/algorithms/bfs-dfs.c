#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include "queue.h"
#include <stdio.h>

static bool finished = FALSE;	/* if true, cut off search immediately */

void bfs(const graph *g, int start) {
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int y;				/* successor vertex */
	edgenode *p;			/* temporary pointer */

	init_queue(&q);
	enqueue(&q, start);
	discovered[start] = TRUE;

	while(empty_queue(&q) == FALSE) {

		v = dequeue(&q);
		process_vertex_early(v);
		processed[v] = TRUE;
		p = g->edges[v];
		
		while(p != NULL) {
	    y = p->y;

	    if((processed[y] == FALSE) || g->directed)
    		process_edge(v, y);
	    if(discovered[y] == FALSE) {
  			enqueue(&q, y); 			
  			discovered[y] = TRUE;
	  		parent[y] = v;
      }
		    p = p->next;
		}
		
		process_vertex_late(v);
	}
}

void dfs(const graph *g, int v) {
	edgenode *p;			/* temporary pointer */
	int y;				/* successor vertex */

	if(finished) return;		/* allow for search termination */

	discovered[v] = TRUE;
  time++;
  entry_time[v] = time;
  /*printf("entered vertex %d at time %d\n",v, entry_time[v]);*/

	process_vertex_early(v);
	p = g->edges[v];
	
	while(p != NULL) {
		y = p->y;

		if(discovered[y] == FALSE) {
			parent[y] = v;
			process_edge(v,y);
			dfs(g, y);

		} else if((!processed[y]) || (g->directed))
			process_edge(v, y);

		if(finished) return;

		p = p->next;
	}

	process_vertex_late(v);

  time = time + 1;
  exit_time[v] = time;
  /*printf("exit vertex %d at time %d\n",v, exit_time[v]);*/

	processed[v] = TRUE;
}


int edge_classification(int x, int y) {
  if(parent[y] == x) 
    return TREE;
  if(discovered[y] && !processed[y]) 
    return BACK;
  if(processed[y] && (entry_time[y]>entry_time[x])) 
    return FORWARD;
  if(processed[y] && (entry_time[y]<entry_time[x])) 
    return CROSS;

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
  int i;          

	time = 0;

  for (i = 0; i <= g->nvertices; i++) {
    processed[i] = discovered[i] = FALSE;
    parent[i] = -1;
  }
}


