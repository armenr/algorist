/*see README for original credits */

#include<stdio.h>
#include"graph-print.h"

static void print_stack_item(const int* item);

void print_colors(const graph* g, const graph_search* gs) {
  int i;
	for(i = 0; i < g->nvertices; i++)
    printf("vertex %d color %d\n", i, gs->color[i]);
  printf("\ngraph two colored is %s\n", (gs->bipartite) ? "TRUE" : "FALSE");    
}

void print_components(const graph* g, const graph_search* gs) {
  int i;
  for(i = 0; i < g->nvertices; i++)
    printf("vertex %d in component %d\n", i, gs->component[i]);
}

void print_fs(const graph* g, graph_search* gs) {
  int i;

  for(i = 0; i < g->nvertices; i++)
    printf("%d ", gs->parent[i]);
  printf("\n\n");

  for(i = 0; i < g->nvertices; i++) {
    find_path(g, gs, 0, i);

    int j;
    for(j = 0; j < g->nvertices; j++) {
      int v = gs->path[j];
      if(v == NONE)
        break;
      printf("%d ", v);
    }
    
    printf("\n");
  }
}

void print_item(const char* item) {
  printf(" value: %c ", *item);
}

void print_top_sort(const graph_search* gs) {
	print_stack(gs->top_sort, print_stack_item);		/* report topological order */
}

static void print_stack_item(const int* item) {
  printf("%d ", *item);
}
