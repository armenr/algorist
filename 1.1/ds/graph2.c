/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"graph2.h"

static void clear_graph_item(graph* g);
static void clear_vertex(graph* g, int v);
static void delete_adj_entries(graph* g, int v);
static void delete_adj_entry(graph* g, int v);
static void delete_undirected_edge(graph* g, int x, int y);
static void insert_undirected_edge(graph* g, int x, int y, int w);
static void resize_vertices(graph* g);

void add_graph_item(graph* g, const void* item, int sz) {
  clear_graph_item(g);
  g->item = malloc(sz);
  memcpy(g->item, item, sz);
  g->item_sz = sz;
}

void clear_graph(graph* g) {
	int i;
	for(i = 0; i < g->nvertices; i++) 
	  clear_vertex(g, i);

  free(g->vertices);	
  clear_graph_item(g);
}

void delete_vertex(graph* g, int v) {
  /*delete all neighboring edges for vertex v*/
  clear_vertex(g, v);

  /*remove vertex from other adjacency lists*/
	if(!g->directed) 
    delete_adj_entries(g, v);

  g->nvertices--;
}

void delete_edge(graph* g, int x, int y) {
	delete_undirected_edge(g, x, y);
	g->nedges--;
	
	if(!g->directed) {
		delete_undirected_edge(g, y, x);
  	g->nedges--;
	}
}

const edge_node* find_edge(const graph* g, int x, int y) {
	const edge_node* p = g->vertices[x]->edges;

	while(p != NULL) {
		if(p->y == y) 
		  return p;
		p = p->next;
	}

	return NULL;
}

const vertex* find_vertex(const graph* g, int v) {
  return g->vertices[v];
}

void init_graph(graph* g, bool directed) {
	g->nvertices = g->nedges = 0;
	g->v_sz = (int)MAXV;
	g->directed = directed;
  g->vertices = calloc(MAXV, sizeof(vertex*));
  g->item = NULL;
}

int insert_vertex(graph* g) {
  if(g->nvertices == g->v_sz)
    resize_vertices(g);

  vertex* v = malloc(sizeof(vertex));    
	v->degree = 0;
	v->edges = NULL;
  v->item = NULL;
  
  if(g->item != NULL) {
    v->item = malloc(g->item_sz);  
	  memcpy(v->item, g->item, g->item_sz);
	  clear_graph_item(g);
  }

  int i = g->nvertices++;
	g->vertices[i] = v;
	
	return i;
}

void insert_edge(graph* g, int x, int y, int w) {
	insert_undirected_edge(g, x, y, w);
	g->nedges++;
	
	if(!g->directed) {
		insert_undirected_edge(g, y, x, w);
  	g->nedges++;
	}
}

void print_graph(const graph* g, void (*print_item)(const void* item)) {
	int i;
  
	for(i = 0; i < g->nvertices; i++) {
	  if(g->vertices[i] == NULL)
	    continue;

	  printf("vertex: %d ", i);
	
	  const vertex* p = g->vertices[i]->item;
	  if(p != NULL)
	    print_item(p);
	
	  const edge_node* q = g->vertices[i]->edges;
	  printf("edges: ");
	
	  while(q != NULL) {
		  printf("%d ", q->y);
		  q = q->next;
	  }
	  printf("\n");    
	}
}

static void clear_graph_item(graph* g) {
  if(g->item != NULL) 
    free(g->item);

  g->item_sz = -1;
  g->item = NULL;
}

static void clear_vertex(graph* g, int v) {
  if(g->vertices[v] == NULL)
    return;
    
	edge_node* p = g->vertices[v]->edges;

  while(p != NULL) {
    edge_node* q = p;
	  p = p->next;

	  free(q->item);
	  free(q);
  }
  
  free(g->vertices[v]->item);
  free(g->vertices[v]);
  
  g->vertices[v] = NULL;
}

static void delete_adj_entries(graph* g, int v) {
  int i;
  
	for(i = 0; i < g->nvertices; i++) 
	  if(i != v)  /* ignore vertex x (already processed)*/
	    delete_adj_entry(g, i);
}

static void delete_adj_entry(graph* g, int v) {
  edge_node* p = g->vertices[v]->edges;
  edge_node* q, *r = NULL;
  
  while(p != NULL) {
    q = p;
	  p = q->next;
	  
    if(q->y == v) {
      if(r != NULL)
        r->next = p;
      else
				g->vertices[v]->edges = p;
        
      free(q->item);
      free(q);

      g->vertices[v]->degree--;
      break;
    }
    r = q;
  }
}

static void delete_undirected_edge(graph* g, int x, int y) {
	edge_node* p = g->vertices[x]->edges;
	edge_node* q = NULL;

	while(p != NULL) 
		if(p->y == y) {
			g->vertices[x]->degree--;
			
			if(q != NULL) 
				q->next = p->next;
			else
				g->vertices[x]->edges = p->next;

			free(p->item);
			free(p);
			
			return;
			
		}	else {  /* check next entry*/
    	q = p;
			p = p->next;
		}
}

static void insert_undirected_edge(graph* g, int x, int y, int w) {
	edge_node *p  = malloc(sizeof(edge_node));	
	p->weight = w;
	p->y = y;
	p->next = g->vertices[x]->edges;
  p->item = NULL;
  
  if(g->item != NULL) {
    p->item = malloc(g->item_sz);  
	  memcpy(p->item, g->item, g->item_sz);
    clear_graph_item(g);
 }

	g->vertices[x]->edges = p;		/* insert at head of list */
	g->vertices[x]->degree++;
}

static void resize_vertices(graph* g) {
  /*double up*/
  int sz = 2 * g->nvertices;
  vertex** t = realloc(g->vertices, sz * sizeof(vertex*));
  if(t != NULL) 
     g->vertices = t; 
  g->v_sz = sz;
}
