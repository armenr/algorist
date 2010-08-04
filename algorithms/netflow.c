/*see README for original credits */

#include "bool.h"
#include "geometry.h"
#include "netflow.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void add_residual_edges(flow_graph *g) {
	int i;			/* counters */
	edgenode *p;                    /* temporary pointer */
	edgenode *find_edge();

	for(i = 1; i <= g->nvertices; i++) {
		p = g->edges[i];
		while(p != NULL) {
			if(find_edge(g, p->v, i) == NULL)
				insert_flow_edge(g, p->v, i, TRUE, 0);
			p = p->next;
		}
	}
}

void augment_path(const flow_graph *g, int start, int end, const int parents[], 
  int volume) {
	edgenode *e;			/* edge in question */
	edgenode *find_edge();

	if(start == end) return;

	e = find_edge(g, parents[end], end);
	e->flow += volume;
	e->residual -= volume;
	
	e = find_edge(g, end, parents[end]);
	e->residual += volume;

	augment_path(g, start, parents[end], parents, volume);
}

void bfs(const flow_graph *g, int start) {
  queue q;                        /* queue of vertices to visit */
  int v;                          /* current vertex */
  int y;                          /* successor vertex */
  edgenode *p;                    /* temporary pointer */

  init_queue(&q);
  enqueue(&q, start);
  discovered[start] = TRUE;

  while(empty_queue(&q) == FALSE) {

    v = dequeue(&q);
    process_vertex_early(v);
    processed[v] = TRUE;
    p = g->edges[v];

    while(p != NULL) {
      y = p->v;

      if(valid_edge(p) == TRUE) {

        if((processed[y] == FALSE) /*|| g->directed*/)
          process_edge(v, y);
          
        if(discovered[y] == FALSE) {
          enqueue(&q, y);
          discovered[y] = TRUE;
          parent[y] = v;
        }

      }
      p = p->next;
    }
    process_vertex_late(v);
  }
}

edgenode *find_edge(const flow_graph *g, int x, int y) {
	edgenode *p;                    /* temporary pointer */

	p = g->edges[x];

	while(p != NULL) {
		if(p->v == y) return(p);
		p = p->next;
	}

	return NULL;
}

void find_path(int start, int end, const int parents[]) {
	if(start == end || end == -1)
		printf("\n%d", start);
	else {
		find_path(start, parents[end], parents);
		printf(" %d", end);
	}
}

void initialize_graph(flow_graph *g) {
	int i;				

	g -> nvertices = 0;
	g -> nedges = 0;

	for(i = 0; i < MAXV; i++) g->degree[i] = 0;
	for(i = 0; i < MAXV; i++) g->edges[i] = NULL;

}

void initialize_search(const flow_graph *g) {
  int i; 

  for(i = 1; i <= g->nvertices; i++) {
    processed[i] = FALSE;
    discovered[i] = FALSE;
    parent[i] = -1;
  }
}

void insert_flow_edge(flow_graph *g, int x, int y, bool directed, int w) {
  edgenode *p;                    /* temporary pointer */

  p = malloc(sizeof(edgenode));   /* allocate storage for edgenode */

	p->v = y;
	p->capacity = w;
	p->flow = 0;
	p->residual = w;
	p->next = g->edges[x];

	g->edges[x] = p;                /* insert at head of list */
	g->degree[x] ++;

	if(directed == FALSE)
		insert_flow_edge(g, y, x, TRUE, w);
	else
		g->nedges ++;
}

void netflow(flow_graph *g, int source, int sink) {
	int volume;			/* weight of the augmenting path */

	add_residual_edges(g);
	initialize_search(g);
	bfs(g, source);

	volume = path_volume(g, source, sink, parent);

	while(volume > 0) {
		augment_path(g,source, sink, parent, volume);
		initialize_search(g);
		bfs(g, source);
		volume = path_volume(g, source, sink, parent);
	}
}

int path_volume(const flow_graph *g, int start, int end, const int parents[]) {
	edgenode *e;			/* edge in question */
	edgenode *find_edge();

	if(parents[end] == -1) return 0;

	e = find_edge(g,parents[end],end);

	if(start == parents[end])
		return(e->residual);
	else
		return( min(path_volume(g,start,parents[end],parents), e->residual) );
}

void print_flow_graph(const flow_graph *g) {
  int i;
  edgenode *p;                    /* temporary pointer */

  for(i = 1; i <= g->nvertices; i++) {
    printf("%d: ", i);
    p = g->edges[i];

    while(p != NULL) {
      printf(" %d(%d,% d, %d)", p->v, p->capacity, p->flow, p->residual);
      p = p->next;
    }

    printf("\n");
  }
}

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

void read_flow_graph(flow_graph *g, bool directed) {
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y, w;			/* placeholder for edge and weight */

	initialize_graph(g);

  printf("enter # vertices and # edges: ");
	scanf("%d %d", &(g->nvertices), &m);

	for(i = 1; i <= m; i++) {
	  printf("enter edge %d (x, y, w): ", i);	
		scanf("%d %d %d",&x, &y, &w);
		insert_flow_edge(g, x, y, directed, w);
	}
}

bool valid_edge(const edgenode *e) {
	if(e->residual > 0) 
	  return TRUE;
	else 
	  return FALSE;
}

