/*see README for original credits */

#include"graph.h"
#include<stdio.h>
#include<string.h>

static void delete_vertex_entries(graph* g, int v);
static void insert_undirected_edge(graph* g, int x, int y, int w);
static void delete_undirected_edge(graph* g, int x, int y);

void clear_graph(graph* g) {
	int i;				
	for(i = 0; i < MAXV; i++) 
	  delete_vertex(g, i);
}

void initialize_graph(graph* g, bool directed) {
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	int i;				

	for(i = 0; i < MAXV; i++) {
	  g->vertices[i].degree = 0;
    g->vertices[i].edges = g->vertices[i].item = NULL;	
	} 
}

void print_graph(const graph* g, void (*print_item)(const void* item)) {
	int i;				
  void *p;
  
	for(i = 0; i < MAXV; i++) 
    if(g->vertices[i].item != NULL) {
		  printf("node: %d ", i);
		
		  p = g->vertices[i].item;
		  if(p != NULL)
		    print_item(p);
		
		  printf("edges: ");
		  p = g->vertices[i].edges;
		
		  while(p != NULL) {
			  printf("%d ", ((edgenode*)p)->y);
			  p = ((edgenode*)p)->next;
		  }
		  printf("\n");    
    }
}

void insert_vertex(graph* g, int v, const void* item, size_t sz) {
  g->vertices[v].item = malloc(sz);  
	memcpy(g->vertices[v].item, item, sz);
	g->nvertices++;
}

void delete_vertex(graph* g, int v) {
  void* p;
  edgenode* q;
	
  /*delete all neighboring edges for vertex x*/
  p = g->vertices[v].edges;
	while(p != NULL) {
	  q = (edgenode*)p;
	  p = q->next;
    free(q);
	}

  /*remove data item*/
  p = g->vertices[v].item;
  free(p);
    
  g->vertices[v].edges = g->vertices[v].item = NULL;    
  g->vertices[v].degree = 0;

  /*remove vertex from other adjacency lists*/
	if(!g->directed) 
    delete_vertex_entries(g, v);
}

void insert_edge(graph* g, int x, int y, int w) {
	insert_undirected_edge(g, x, y, w);
	g->nedges++;
	
	if(!g->directed) {
		insert_undirected_edge(g, y, x, w);
  	g->nedges++;
	}
}

void delete_edge(graph* g, int x, int y) {
	delete_undirected_edge(g, x, y);
	g->nedges--;
	
	if(!g->directed) {
		delete_undirected_edge(g, y, x);
  	g->nedges--;
	}
}

static void delete_undirected_edge(graph* g, int x, int y) {
	edgenode* p = g->vertices[x].edges;
	edgenode* q = NULL;

	while(p != NULL) 
		if(p->y == y) {
			g->vertices[x].degree--;
			
			if(q != NULL) 
				q->next = p->next;
			else
				g->vertices[x].edges = p->next;

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
	p->next = g->vertices[x].edges;

	g->vertices[x].edges = p;		/* insert at head of list */
	g->vertices[x].degree++;
}

static void delete_vertex_entries(graph* g, int v) {
  void* p;
  edgenode* q;

  int i;
  
	for(i = 0; i < MAXV; i++) {
	  if(i == v)  /* ignore vertex x (already processed)*/
	    continue;
	    
    edgenode* r = NULL;
    p = g->vertices[i].edges;
    
    while(p != NULL) {
      q = (edgenode*)p;
  	  p = q->next;
  	  
      if(q->y == v) {
        if(r != NULL)
	        r->next = p;
        else
  				g->vertices[i].edges = p;
          
        free(q);
        
        g->vertices[i].degree--;
        break;
      }
      r = q;
    }
	}
}

