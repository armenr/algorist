/*see README for original credits */

#include"graph.h"
#include<stdio.h>
#include<string.h>

void clear_graph(graph* g) {
	int i;				
	for(i = 0; i < g->nvertices; i++) 
	  delete_vertex(g, i);
}

void initialize_graph(graph* g, bool directed) {
	int i;				

	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(i = 0; i < MAXV; i++) {
	  g->vertices[i].degree = 0;
    g->vertices[i].edges = g->vertices[i].item = NULL;	
	} 
}

void read_graph(graph* g, bool directed) {
	int i;				
	int m;				/* number of edges */
	int x, y, w;			/* vertices in edge (x,y) and weught*/
  
	initialize_graph(g, directed);

  printf("enter # vertices and # edges: ");
	scanf("%d %d", &(g->nvertices), &m);

	for(i = 0; i < m; i++) {
	  printf("enter edge %d (x, y, weight): ", i);	
		scanf("%d %d %d",&x, &y, &w);
		insert_edge(g, x, y, w, directed);
	}
}

void print_graph(const graph* g, void (*print_item)(void*)) {
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

void insert_vertex(graph* g, int x, const item_type i, size_t n) {
  g->vertices[x].item = malloc(n);  
	memcpy(g->vertices[x].item, i, n);
	g->nvertices++;
}

void delete_vertex(graph* g, int x) {
  void* p;
  edgenode* q;
	
  p = g->vertices[x].edges;
	while(p != NULL) {
	  q = (edgenode*)p;
	  p = q->next;
    free(q);
	}

  /*remove entry x in other adjacency lists for undirected graphs*/
	if(!g->directed) { 
	  int i;
    
  	for(i = 0; i < g->nvertices; i++) {
      edgenode* r = NULL;
      p = g->vertices[i].edges;
      
	    while(p != NULL) {
	      q = (edgenode*)p;
    	  p = q->next;
    	  
	      if(q->y == x) {
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
	
  p = g->vertices[x].item;
  if(p != NULL)
    free(p);
    
  g->vertices[x].edges = g->vertices[x].item = NULL;    
  g->vertices[x].degree = 0;
}

void insert_edge(graph* g, int x, int y, int w, bool directed) {
  if(g->vertices[x].item == NULL || g->vertices[y].item == NULL) {
  	printf("Error: vertex %d and/or vertex %d not found in g.\n", x, y);
    return;
  }
  
	edgenode *p  = malloc(sizeof(edgenode));	/* allocate storage for edgenode */
	p->weight = w;
	p->y = y;
	p->next = g->vertices[x].edges;

	g->vertices[x].edges = p;		/* insert at head of list */
	g->vertices[x].degree++;

	if(!directed)
		insert_edge(g, y, x, w, true);
	else
		g->nedges ++;
}

void delete_edge(graph* g, int x, int y, bool directed) {
	edgenode *p, *p_back;		/* temporary pointers */

	p = g->vertices[x].edges;
	p_back = NULL;

	while (p != NULL) 
		if(p->y == y) {
			g->vertices[x].degree --;
			
			if(p_back != NULL) 
				p_back->next = p->next;
			else
				g->vertices[x].edges = p->next;

			free(p);

  	if(!directed)
				delete_edge(g, y, x, true);
			else
				g->nedges --;

			return;
		}
		else {
    	p_back = p;
			p = p->next;
		}

	printf("Warning: deletion(%d,%d) not found in g.\n", x, y);
}
