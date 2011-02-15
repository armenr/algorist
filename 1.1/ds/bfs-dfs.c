/*see README for original credits */

#include"bfs-dfs.h"
#include"../ds/queue.h"
#include<stdio.h>

extern void process_edge(int x, int y);
extern void process_vertex_early(int v); 
extern void process_vertex_late(int v);

static bool finished = false;	/* if true, cut off search immediately */

void bfs(const graph *g, int start) {
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int y;				/* successor vertex */
	edgenode *p;			/* temporary pointer */

	q = init_queue();
	en_queue(&q, &start, sizeof(int));
	discovered[start] = true;

	while(!empty_queue(q)) {

    int* ip = (int*)de_queue(&q);
    if(ip != NULL) {
  		v = *ip;
	    free(ip);	  
    }
		process_vertex_early(v);
		processed[v] = true;
		p = g->vertices[v].edges;
		
		while(p != NULL) {
	    y = p->y;

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

void dfs(const graph *g, int v) {
	edgenode *p;			/* temporary pointer */
	int y;				/* successor vertex */

	if(finished) return;		/* allow for search termination */

	discovered[v] = true;
  time++;
  entry_time[v] = time;
  /*printf("entered vertex %d at time %d\n",v, entry_time[v]);*/

	process_vertex_early(v);
	p = g->vertices[v].edges;
	
	while(p != NULL) {
		y = p->y;

		if(!discovered[y]) {
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

	processed[v] = true;
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
    processed[i] = discovered[i] = false;
    parent[i] = -1;
  }
}
