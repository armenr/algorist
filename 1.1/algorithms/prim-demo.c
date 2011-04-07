/*see README for original credits */

#include"bfs-dfs.h"
#include"prim.h"
#include<stdio.h>

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

static void init_graph(graph* g) {
  char c;
  initialize_graph(g, false);

  c = 'a';
  insert_vertex(g, 1, &c, sizeof(char));
  c = 'b';
  insert_vertex(g, 2, &c, sizeof(char));
  c = 'c';
  insert_vertex(g, 3, &c, sizeof(char));
  c = 'd';
  insert_vertex(g, 4, &c, sizeof(char));
  c = 'e';
  insert_vertex(g, 5, &c, sizeof(char));
  c = 'f';
  insert_vertex(g, 6, &c, sizeof(char));
  c = 'g';
  insert_vertex(g, 7, &c, sizeof(char));
  
  insert_edge(g, 1, 2, 12, false);
  insert_edge(g, 1, 5, 5, false);
  insert_edge(g, 1, 6, 7, false);
  insert_edge(g, 2, 3, 7, false);
  insert_edge(g, 2, 6, 4, false);
  insert_edge(g, 3, 4, 2, false);
  insert_edge(g, 3, 6, 3, false);
  insert_edge(g, 3, 7, 2, false);
  insert_edge(g, 4, 5, 7, false);
  insert_edge(g, 4, 6, 4, false);
  insert_edge(g, 4, 7, 5, false);
  insert_edge(g, 5, 6, 9, false);
}

int main(void) {
	graph g;

  init_graph(&g);    
	print_graph(&g);
	
	prim(&g, 1);

	int i;

  for(i = 1; i <= g.nvertices; i++) 
    find_path(1, i, parent);
  printf("\n");
  
	clear_graph(&g);
  return 0;
}

/* test run 
see fig 6.3 pp 196 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 12 edges

               *(4)
                        *(7)
                                                                        
              
     (5)*       *(6)    *(3)

                
        
          *         *                          
         (1)        (2)

osman@osman-dev:~/src/algorithms$ ./prim-demo 
node: 1  value: a edges: 6 5 2 
node: 2  value: b edges: 6 3 1 
node: 3  value: c edges: 7 6 4 2 
node: 4  value: d edges: 7 6 5 3 
node: 5  value: e edges: 6 4 1 
node: 6  value: f edges: 5 4 3 2 1 
node: 7  value: g edges: 4 3 

1
1 5 4 3 6 2
1 5 4 3
1 5 4
1 5
1 5 4 3 6
1 5 4 3 7
*/
