/*see README for original credits */

#include"bfs-dfs.h"
#include<stdio.h>

void process_vertex_early(int v) {
	time++;
	entry_time[v] = time;
	printf("entered vertex %d at time %d\n", v, entry_time[v]);
}

void process_vertex_late(int v) {
	time++;
	exit_time[v] = time;
  printf("exit vertex %d at time %d\n", v, exit_time[v]);
}

void process_edge(int x, int y) {
	int class;		/* edge class */

	class = edge_classification(x, y);

	if(class == BACK) 
	  printf("back edge (%d, %d)\n", x, y);
	else if(class == TREE) 
	  printf("tree edge (%d,%d)\n", x, y);
	else if(class == FORWARD) 
	  printf("forward edge (%d,%d)\n", x, y);
	else if(class == CROSS) 
	  printf("cross edge (%d,%d)\n", x, y);
	else 
	  printf("edge (%d,%d)\n not in valid class=%d", x, y, class);
}

static void init_graph(graph* g) {
  char c;
  initialize_graph(g, false);
  
  c = 'a';
  insert_vertex(g, 1, &c, sizeof(char));
  c = 'b';
  insert_vertex(g, 2, &c, sizeof(char));
  insert_edge(g, 1, 2, false, 0);
  c = 'e';
  insert_vertex(g, 5, &c, sizeof(char));
  insert_edge(g,1, 5, false, 0);
  c = 'f';
  insert_vertex(g, 6, &c, sizeof(char));
  insert_edge(g,1, 6, false, 0);
  insert_edge(g,2, 5, false, 0);
  c = 'c';
  insert_vertex(g, 3, &c, sizeof(char));
  insert_edge(g,2, 3, false, 0);
  c = 'd';
  insert_vertex(g, 4, &c, sizeof(char));
  insert_edge(g,5, 4, false, 0);
  insert_edge(g,3, 4, false, 0);
}

int main(void) {
	graph g;

  init_graph(&g);    
	print_graph(&g);

	initialize_search(&g);
	dfs(&g, 1);

	int i;

  for (i=1; i<=g.nvertices; i++)
    find_path(1, i, parent);
  printf("\n");
  
	clear_graph(&g);
  return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-dev:~/src/algorithms$ ./dfs-demo 
node: 1  value: a edges: 6 5 2 
node: 2  value: b edges: 3 5 1 
node: 3  value: c edges: 4 2 
node: 4  value: d edges: 3 5 
node: 5  value: e edges: 4 2 1 
node: 6  value: f edges: 1 
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

