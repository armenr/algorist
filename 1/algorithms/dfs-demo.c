#include "bool.h"
#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include <stdio.h>

void process_vertex_early(int v) {
	time = time + 1;
	entry_time[v] = time;
	printf("entered vertex %d at time %d\n", v, entry_time[v]);
}

void process_vertex_late(int v) {
	time = time + 1;
	exit_time[v] = time;
  printf("exit vertex %d at time %d\n", v, exit_time[v]);
}

void process_edge(int x, int y) {
	int class;		/* edge class */

	class = edge_classification(x, y);

	if(class == BACK) printf("back edge (%d, %d)\n", x, y);
	else if(class == TREE) printf("tree edge (%d,%d)\n", x, y);
	else if(class == FORWARD) printf("forward edge (%d,%d)\n", x, y);
	else if(class == CROSS) printf("cross edge (%d,%d)\n", x, y);
	else printf("edge (%d,%d)\n not in valid class=%d", x, y, class);

}


int main(void) {
	graph g;
	int i;

	read_graph(&g, FALSE);
	print_graph(&g);

	initialize_search(&g);
	dfs(&g, 1);

  for (i=1; i<=g.nvertices; i++)
    find_path(1, i, parent);
  printf("\n");
  
  return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./dfs-demo 
enter # vertices and # edges: 1 2 0
enter edge 1 (x, y, w): 1 5 0^C
osman@osman-desktop:~/src/algorithms$ ./dfs-demo 
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
entered vertex 1 at time 2
tree edge (1,6)
entered vertex 6 at time 4
back edge (6, 1)
exit vertex 6 at time 5
tree edge (1,5)
entered vertex 5 at time 8
tree edge (5,4)
entered vertex 4 at time 10
tree edge (4,3)
entered vertex 3 at time 12
back edge (3, 4)
tree edge (3,2)
entered vertex 2 at time 14
back edge (2, 3)
back edge (2, 5)
back edge (2, 1)
exit vertex 2 at time 15
exit vertex 3 at time 17
back edge (4, 5)
exit vertex 4 at time 19
back edge (5, 1)
exit vertex 5 at time 21
exit vertex 1 at time 23

1
1 5 4 3 2
1 5 4 3
1 5 4
1 5
1 6

*/

