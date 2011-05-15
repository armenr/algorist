/*see README for original credits */

#include"graph2.h"
#include<stdio.h>
#include<string.h>

static void clear_vertex(graph* g, int v);
static void delete_adj_entries(graph* g, int v);
static void delete_adj_entry(graph* g, int v);
static void delete_undirected_edge(graph* g, int x, int y);
static void insert_undirected_edge(graph* g, int x, int y, int w);
static void resize_vertices(graph* g);

void clear_graph(graph* g) {
	int i;
	for(i = 0; i < g->nvertices; i++) 
	  clear_vertex(g, i);

  free(g->vertices);	  
}

void delete_vertex(graph* g, int v) {
  /*delete all neighboring edges for vertex v*/
  clear_vertex(g, v);

  /*remove vertex from other adjacency lists*/
	if(!g->directed) 
    delete_adj_entries(g, v);
}

void delete_edge(graph* g, int x, int y) {
	delete_undirected_edge(g, x, y);
	g->nedges--;
	
	if(!g->directed) {
		delete_undirected_edge(g, y, x);
  	g->nedges--;
	}
}

void initialize_graph(graph* g, bool directed) {
	g->nvertices = g->nedges = 0;
	g->v_sz = (int)MAXV;
	g->directed = directed;
  g->vertices = calloc(MAXV, sizeof(vertex*));
}

int insert_vertex(graph* g, const void* item, size_t sz) {
  if(g->nvertices == g->v_sz)
    resize_vertices(g);

  vertex* v = malloc(sizeof(vertex));    
  v->item = malloc(sz);  
	memcpy(v->item, item, sz);
	v->degree = 0;
	v->edges = NULL;

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

	  printf("node: %d ", i);
	
	  void* p = g->vertices[i]->item;
	  if(p != NULL)
	    print_item(p);
	
	  edgenode* q = g->vertices[i]->edges;
    if(q == NULL)
	    continue;
    
	  printf("edges: ");
	
	  while(q != NULL) {
		  printf("%d ", q->y);
		  q = q->next;
	  }
	  printf("\n");    
	}
}

static void clear_vertex(graph* g, int v) {
  if(g->vertices[v] == NULL)
    return;
    
	edgenode* p = g->vertices[v]->edges;

  while(p != NULL) {
    edgenode* q = p;
	  p = p->next;
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
  edgenode* p = g->vertices[v]->edges;
  edgenode* q, *r = NULL;
  
  while(p != NULL) {
    q = p;
	  p = q->next;
	  
    if(q->y == v) {
      if(r != NULL)
        r->next = p;
      else
				g->vertices[v]->edges = p;
        
      free(q);
      g->vertices[v]->degree--;
      break;
    }
    r = q;
  }
}

static void delete_undirected_edge(graph* g, int x, int y) {
	edgenode* p = g->vertices[x]->edges;
	edgenode* q = NULL;

	while(p != NULL) 
		if(p->y == y) {
			g->vertices[x]->degree--;
			
			if(q != NULL) 
				q->next = p->next;
			else
				g->vertices[x]->edges = p->next;

			free(p);
			return;
			
		}	else {  /* check next entry*/
    	q = p;
			p = p->next;
		}
}

static void insert_undirected_edge(graph* g, int x, int y, int w) {
	edgenode *p  = malloc(sizeof(edgenode));	
	p->weight = w;
	p->y = y;
	p->next = g->vertices[x]->edges;

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
