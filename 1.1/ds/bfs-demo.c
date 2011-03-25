/*see README for original credits */

#include"bfs-dfs.h"
#include<stdio.h>

void process_vertex_early(int v) {
  printf("processed vertex %d\n", v);
}

void process_vertex_late(int v) {
}

void process_edge(int x, int y) {
  printf("processed edge (%d,%d)\n", x, y);
}

static void init_graph(graph* g) {
  char c;
  initialize_graph(g, false);

  c = 'a';
  insert_vertex(g, 1, &c, sizeof (char));
  c = 'b';
  insert_vertex(g, 2, &c, sizeof (char));
  insert_edge(g, 1, 2, 0, false);
  c = 'e';
  insert_vertex(g, 5, &c, sizeof (char));
  insert_edge(g, 1, 5, 0, false);
  c = 'f';
  insert_vertex(g, 6, &c, sizeof (char));
  insert_edge(g, 1, 6, 0, false);
  insert_edge(g, 2, 5, 0, false);
  c = 'c';
  insert_vertex(g, 3, &c, sizeof (char));
  insert_edge(g, 2, 3, 0, false);
  c = 'd';
  insert_vertex(g, 4, &c, sizeof (char));
  insert_edge(g, 5, 4, 0, false);
  insert_edge(g, 3, 4, 0, false);
}

static void print_item(char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
    graph g;

    init_graph(&g);
    print_graph(&g, print_item);
    printf("\n");

    initialize_search(&g);
    bfs(&g, 1);
    printf("\n");

    int i;

    for (i = 1; i <= g.nvertices; i++)
        printf(" %d", parent[i]);
    printf("\n");

    for (i = 1; i <= g.nvertices; i++)
        find_path(1, i, parent);
    printf("\n");

    clear_graph(&g);
    return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

6 vertices, 7 edges

 *
              (1)
                        
              
 *       *      *
       (2)     (5)    (6)
                
        
 *        *
      (3)      (4)
         
osman@osman-vbox-l32:~/src/ds$ ./bfs-demo 
node: 1  value: a edges: 6 5 2 
node: 2  value: b edges: 3 5 1 
node: 3  value: c edges: 4 2 
node: 4  value: d edges: 3 5 
node: 5  value: e edges: 4 2 1 
node: 6  value: f edges: 1 

processed vertex 1
processed edge (1,6)
processed edge (1,5)
processed edge (1,2)
processed vertex 6
processed vertex 5
processed edge (5,4)
processed edge (5,2)
processed vertex 2
processed edge (2,3)
processed vertex 4
processed edge (4,3)
processed vertex 3

 -1 1 2 5 1 1

1
1 2
1 2 3
1 5 4
1 5
1 6
 */

