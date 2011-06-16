/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"graph1.h"
#include"util.h"

static void clear_graph_item(graph* g);
static void clear_vertex(vertex *v);
static int compare_vertices(const int* key1, const int* key2);
static void delete_adj_entries(graph* g, int v);
static void delete_adj_entry(vertex* d, int v);
static void delete_undirected_edge(graph* g, int x, int y);
static void insert_undirected_edge(graph* g, int x, int y, int w);

void add_graph_item(graph* g, const void* item, int sz) {
  clear_graph_item(g);
  g->item = malloc(sz);
  memcpy(g->item, item, sz);
  g->item_sz = sz;
}

void clear_graph(graph* g) {
  skipnode* s = g->vertices->header->next[0];
  
  while(s != NULL) {
    clear_vertex((vertex*)s->item);
    s = s->next[0];
  }    
  
  clear_skipset(g->vertices);
  clear_graph_item(g);
}

void delete_vertex(graph* g, int v) {
  skipnode* s = contains_skipnode(g->vertices, &v, compare_vertices);
  if(s == NULL)
    return;
    
  /*delete all neighboring edges for vertex v*/
  clear_vertex((vertex*)s->item);
  delete_skipnode2(g->vertices, s);
  
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
	const vertex* v = find_vertex(g, x);
	const edge_node* p = v->edges;

	while(p != NULL) {
		if(p->y == y) 
		  return p;
		p = p->next;
	}

	return NULL;
}

const vertex* find_vertex(const graph* g, int v) {
  skipnode* s = contains_skipnode(g->vertices, &v, compare_vertices);
  if(s == NULL)
    return NULL;

  return (vertex*)s->item;
}

void init_graph(graph* g, bool directed) {
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
  g->item = NULL;
  init_skipset(&(g->vertices));
}

int insert_vertex(graph* g) {
  vertex* v = malloc(sizeof(vertex));
  v->edges = NULL;
  v->degree = 0;
  v->item = NULL;
  
  if(g->item != NULL) {
    v->item = malloc(g->item_sz);  
	  memcpy(v->item, g->item, g->item_sz);
	  clear_graph_item(g);
  }

  int i = g->nvertices++;
  add_skipset_item(g->vertices, v, sizeof(*v));
  insert_skipnode(g->vertices, &i, sizeof(i), compare_vertices);
  free(v);

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
  skipnode* s = g->vertices->header->next[0];
  
  while(s != NULL) {
	  printf("vertex: %d ", *(int*)s->key);

    const vertex* v = (vertex*)s->item;
	  void* p = v->item;
	  
    if(p != NULL) 
	    print_item(p);
		
	  printf("edges: ");
	  const edge_node* e = v->edges;
	
	  while(e != NULL) {
		  printf("%d ", e->y);
		  e = e->next;
	  }
	  printf("\n");    
    
    s = s->next[0];
  }    
}

static void clear_graph_item(graph* g) {
  if(g->item != NULL) 
    free(g->item);

  g->item_sz = -1;
  g->item = NULL;
}

static void clear_vertex(vertex* v) {
  edge_node* e = v->edges;

  while(e != NULL) {
    edge_node* f = e;
	  e = e->next;
	  free(f->item);
	  free(f);
  }
  free(v->item);
}

static int compare_vertices(const int* key1, const int* key2) {
  return compare_keys_int(key1, key2);
}

static void delete_adj_entries(graph* g, int v) {
  skipnode* s = g->vertices->header->next[0];
  
  while(s != NULL) {
    delete_adj_entry((vertex*)s->item, v);
    s = s->next[0];
  }    
}

static void delete_adj_entry(vertex* d, int v) {
  edge_node* p = d->edges;
  edge_node* q, *r = NULL;

  while(p != NULL) {
    q = p;
	  p = q->next;
	  
    if(q->y == v) {
      if(r != NULL)
        r->next = p;
      else
				d->edges = p;
        
      free(q->item);
      free(q);
      
      d->degree--;
      break;
    }
    
    r = q;
  }
}

static void delete_undirected_edge(graph* g, int x, int y) {
  skipnode* s = contains_skipnode(g->vertices, &x, compare_vertices);
  if(s == NULL)
    return;

  vertex* v = (vertex*)s->item;
	edge_node* p = v->edges;
	edge_node* q = NULL;

	while(p != NULL) 
		if(p->y == y) {
			v->degree--;
			
			if(q != NULL) 
				q->next = p->next;
			else
				v->edges = p->next;

			free(p->item);
			free(p);
			return;
			
		}	else {  /* check next entry*/
    	q = p;
			p = p->next;
		}
}

static void insert_undirected_edge(graph* g, int x, int y, int w) {
  skipnode* s = contains_skipnode(g->vertices, &x, compare_vertices);
  if(s == NULL)
    return;

	edge_node *p  = malloc(sizeof(edge_node));	
	p->weight = w;
	p->y = y;
  p->item = NULL;
  
  if(g->item != NULL) {
    p->item = malloc(g->item_sz);  
	  memcpy(p->item, g->item, g->item_sz);
	  clear_graph_item(g);
  }

  vertex* v = (vertex*)s->item;
	p->next = v->edges;
	v->edges = p;		/* insert at head of list */
	v->degree++;
}

