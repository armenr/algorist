/*see README for original credits */

#include"skip-list.h"
#include"graph.h"
#include<stdio.h>
#include<string.h>

static void clear_vertex(vertex *v);
static int compare_vertices(const int* key1, const int* key2);
static void delete_adj_entries(graph* g, int v);
static void delete_adj_entry(vertex* d, int v);
static void delete_undirected_edge(graph* g, int x, int y);
static void insert_undirected_edge(graph* g, int x, int y, int w);

void clear_graph(graph* g) {
  skipnode* s = g->vertices->header->next[0];
  
  while(s != NULL) {
    clear_vertex((vertex*)s->item);
    s = s->next[0];
  }    
  
  clear_skipset(g->vertices);
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
}

void delete_edge(graph* g, int x, int y) {
	delete_undirected_edge(g, x, y);
	g->nedges--;
	
	if(!g->directed) {
		delete_undirected_edge(g, y, x);
  	g->nedges--;
	}
}

const vertex* find_vertex(const graph* g, int v) {
  skipnode* s = contains_skipnode(g->vertices, &v, compare_vertices);
  if(s == NULL)
    return NULL;

  return (vertex*)s->item;
}

void initialize_graph(graph* g, bool directed) {
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
  init_skipset(&(g->vertices));
}

int insert_vertex(graph* g, const void* item, size_t sz) {
  vertex* v = malloc(sizeof(vertex));
  v->edges = NULL;
  v->degree = 0;
  v->item = malloc(sz);  
	memcpy(v->item, item, sz);

  int i = g->nvertices++;
  insert_skipnode(g->vertices, &i, sizeof(i), v, sizeof(*v), compare_vertices);
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
    vertex* v = (vertex*)s->item;
	  void* p = v->item;
	  
    if(p != NULL) {
		  printf("node: %d ", *(int*)s->key);
	    print_item(p);
		
		  printf("edges: ");
		  edgenode* e = v->edges;
		
		  while(e != NULL) {
			  printf("%d ", e->y);
			  e = e->next;
		  }
		  printf("\n");    
    }
    
    s = s->next[0];
  }    
}

static void clear_vertex(vertex* v) {
  edgenode* e = v->edges;

  while(e != NULL) {
    edgenode* f = e;
	  e = e->next;
	  free(f);
  }
  free(v->item);
}

static int compare_vertices(const int* key1, const int* key2) {
  if(key1 == NULL && key2 == NULL)
    return 0;
  else if(key1 == NULL)
    return -1;
  else if(key2 == NULL)
    return 1;

  int k1 = *key1, k2 = *key2;

  if(k1 == k2)
    return 0;

  return k1 - k2;
}

static void delete_adj_entries(graph* g, int v) {
  skipnode* s = g->vertices->header->next[0];
  
  while(s != NULL) {
    delete_adj_entry((vertex*)s->item, v);
    s = s->next[0];
  }    
}

static void delete_adj_entry(vertex* d, int v) {
  edgenode* p = d->edges;
  edgenode* q, *r = NULL;

  while(p != NULL) {
    q = p;
	  p = q->next;
	  
    if(q->y == v) {
      if(r != NULL)
        r->next = p;
      else
				d->edges = p;
        
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
	edgenode* p = v->edges;
	edgenode* q = NULL;

	while(p != NULL) 
		if(p->y == y) {
			v->degree--;
			
			if(q != NULL) 
				q->next = p->next;
			else
				v->edges = p->next;

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

	edgenode *p  = malloc(sizeof(edgenode));	
	p->weight = w;
	p->y = y;

  vertex* v = (vertex*)s->item;
	p->next = v->edges;
	v->edges = p;		/* insert at head of list */
	v->degree++;
}

