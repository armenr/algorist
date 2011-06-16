/*see README for original credits */

#include<stdlib.h>
#include<stdio.h>
#include"../ds/queue.h"
#include"graph-search.h"
#include"netflow.h"

static void add_residual_edges(graph* g);
static void augment_path(const graph* g, int start, int end, const int* parents, 
  int volume);
static void bfs_flow(const graph* g, graph_search* gs, int start, 
  void (*process_vertex_early)(graph_search* gs, int v),
  void (*process_vertex_late)(graph_search* gs, int v),
  void (*process_edge)(graph_search* gs, int x, int y));
  
static int path_volume(const graph* g, int start, int end, const int* parents);
static bool valid_edge(const edge_node* e);

void netflow(graph* g, int source, int sink) {
	add_residual_edges(g);

  graph_search gs;
  init_search(g, &gs);
  bfs_flow(g, &gs, source, NULL, NULL, NULL);

	int volume = path_volume(g, source, sink, gs.parent);

	while(volume > 0) {
		augment_path(g,source, sink, gs.parent, volume);
    clear_search(&gs);
    init_search(g, &gs);
    bfs_flow(g, &gs, source, NULL, NULL, NULL);
	  volume = path_volume(g, source, sink, gs.parent);
	}
  clear_search(&gs);
}

void print_flow_graph(const graph* g, int source) {
  int i, flow = 0;

  for(i = 0; i < g->nvertices; i++) {
    printf("%d: ", i);
  	const vertex* v = find_vertex(g, i);
		const edge_node* p = v->edges;

    while(p != NULL) {
      const flow_node* f = (flow_node*)p->item;
      printf(" %d(%d, %d, %d)", p->y, p->weight, f->flow, f->residual);

      if(i == source)
    		flow += f->flow;

      p = p->next;
    }
    printf("\n");
  }

	printf("\ntotal flow = %d\n", flow);  
}

static void add_residual_edges(graph* g) {
	int i;
  flow_node f;
  f.flow = f.residual = 0;

	for(i = 0; i < g->nvertices; i++) {
  	const vertex* v = find_vertex(g, i);
		const edge_node* p = v->edges;

		while(p != NULL) {
			if(find_edge(g, p->y, i) == NULL) {
        add_graph_item(g, &f, sizeof(flow_node));
				insert_edge(g, p->y, i, 0);
			}
			p = p->next;
		}
	}
}

static void augment_path(const graph* g, int start, int end, const int* parents, 
  int volume) {
  
	if(start == end) 
	  return;

	const edge_node* e = find_edge(g, parents[end], end);
  flow_node* f = (flow_node*)e->item;

	f->flow += volume;
	f->residual -= volume;
	
	e = find_edge(g, end, parents[end]);
  f = (flow_node*)e->item;
	f->residual += volume;

	augment_path(g, start, parents[end], parents, volume);
}

static void bfs_flow(const graph* g, graph_search* gs, int start, 
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
		
  	const vertex* vert = find_vertex(g, v);
		const edge_node* p = vert->edges;
		
		while(p != NULL) {
	    int y = p->y;

      if(valid_edge(p)) {
	      if(!gs->processed[y]) {
          if(process_edge != NULL) 
        		process_edge(gs, v, y);
	      }
      		
	      if(!gs->discovered[y]) {
    			en_queue(&q, &y, sizeof(int));
    			gs->discovered[y] = true;
	    		gs->parent[y] = v;
        }
      }

	    p = p->next;
		}

    if(process_vertex_late != NULL) 
  		process_vertex_late(gs, v);
	}
	
	clear_queue(&q);
}

static int path_volume(const graph* g, int start, int end, const int* parents) {
	if(parents[end] == NONE) 
	  return 0;

	const edge_node* e = find_edge(g, parents[end], end);
  int r = ((flow_node*)e->item)->residual;

	if(start == parents[end]) 
		return r;
	else
		return min(path_volume(g, start, parents[end], parents), r);
}

static bool valid_edge(const edge_node* e) {
  int r = ((flow_node*)e->item)->residual;
	if(r > 0) 
	  return true;
	else 
	  return false;
}


