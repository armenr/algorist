/*see README for original credits */

#include"bfs-dfs.h"
#include"prim.h"
#include<stdio.h>

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

static void init_graph(graph* g) {
  initialize_graph(g, false);

  /*should check for return values of insert vertex*/
  char c = 'a';
  insert_vertex(g, &c, sizeof(char)); /*0*/
  c = 'b';
  insert_vertex(g, &c, sizeof(char)); /*1*/
  c = 'c';
  insert_vertex(g, &c, sizeof(char)); /*2*/
  c = 'd';
  insert_vertex(g, &c, sizeof(char)); /*3*/
  c = 'e';
  insert_vertex(g, &c, sizeof(char)); /*4*/
  c = 'f';
  insert_vertex(g, &c, sizeof(char)); /*5*/
  c = 'g';
  insert_vertex(g, &c, sizeof(char)); /*6*/
  
  insert_edge(g, 0, 1, 12);
  insert_edge(g, 0, 4, 5);
  insert_edge(g, 0, 5, 7);
  insert_edge(g, 1, 2, 7);
  insert_edge(g, 1, 5, 4);
  insert_edge(g, 2, 3, 2);
  insert_edge(g, 2, 5, 3);
  insert_edge(g, 2, 6, 2);
  insert_edge(g, 3, 4, 7);
  insert_edge(g, 3, 5, 4);
  insert_edge(g, 3, 6, 5);
  insert_edge(g, 4, 5, 9);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
	graph g;
  init_graph(&g);    
	print_graph(&g, print_item);
	prim(&g, 0);
	clear_graph(&g);
  return 0;
/*  printf("total cost is %d\n", cost);*/
}

/* test run 
see fig 6.3 pp 196 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 12 edges

                 *(3)
                          *(6)
                                                                        
                
       (4)*       *(5)    *(2)

                
        
            *         *                          
           (0)        (1)

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
