/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include <stdio.h>

void process_vertex_early(int v) {
	printf("processed vertex %d\n", v);
}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {
  printf("processed edge (%d,%d)\n", x, y);
}

int main(void) {
	graph g;
	int i;

	read_graph(&g, FALSE);
	print_graph(&g);
	initialize_search(&g);
	bfs(&g, 1);

	for(i = 1; i <= g.nvertices; i++)
		printf(" %d", parent[i]);

	printf("\n");

	for(i = 1; i <= g.nvertices; i++) 
		find_path(1, i, parent);

	printf("\n");
	
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
         
osman@osman-desktop:~/src/algorithms$ ./bfs-demo 
enter # vertices and # edges: 6 7
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 5 0
enter edge 3 (x, y, w): 1 6 0
enter edge 4 (x, y, w): 2 5 0
enter edge 5 (x, y, w): 2 3 0
enter edge 6 (x, y, w): 5 4 0
enter edge 7 (x, y, w): 3 4 0
1:  6 5 2
2:  3 5 1
3:  4 2
4:  3 5
5:  4 2 1
6:  1
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

