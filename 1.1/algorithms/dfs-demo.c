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
  insert_vertex(g, 1, &c, sizeof (char));
  c = 'b';
  insert_vertex(g, 2, &c, sizeof (char));
  insert_edge(g, 1, 2, 0);
  c = 'e';
  insert_vertex(g, 5, &c, sizeof (char));
  insert_edge(g, 1, 5, 0);
  insert_edge(g, 2, 5, 0);
  c = 'f';
  insert_vertex(g, 6, &c, sizeof (char));
  insert_edge(g, 1, 6, 0);
  c = 'c';
  insert_vertex(g, 3, &c, sizeof (char));
  insert_edge(g, 2, 3, 0);
  c = 'd';
  insert_vertex(g, 4, &c, sizeof (char));
  insert_edge(g, 5, 4, 0);
  insert_edge(g, 3, 4, 0);
  
  /*delete edge test  */
  insert_edge(g, 5, 6, 0);
  delete_edge(g, 5, 6);  
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
  graph g;

  init_graph(&g);
  print_graph(&g, print_item);
  printf("\n");

  initialize_search(&g);
  dfs(&g, 1);
  printf("\n");

  int i;

  for(i = 1; i <= g.nvertices; i++)
    printf(" %d", parent[i]);
  printf("\n");

  for(i = 1; i <= g.nvertices; i++)
    find_path(1, i, parent);
  printf("\n");

	clear_graph(&g);
  return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-dev:~/src/algorist/1.1/algorithms$ ./dfs-demo 
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

 -1 3 4 5 1 1

1
1 5 4 3 2
1 5 4 3
1 5 4
1 5
1 6

osman@osman-dev:~/src/algorist/1.1/algorithms$ make dfs-demo && valgrind --leak-check=yes ./dfs-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o dfs-demo.o dfs-demo.c
dfs-demo.c: In function ‘main’:
dfs-demo.c:72: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:44: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o dfs-demo bfs-dfs.o dfs-demo.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o 
==18799== Memcheck, a memory error detector
==18799== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==18799== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==18799== Command: ./dfs-demo
==18799== 
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

 -1 3 4 5 1 1

1
1 5 4 3 2
1 5 4 3
1 5 4
1 5
1 6
==18799== 
==18799== HEAP SUMMARY:
==18799==     in use at exit: 0 bytes in 0 blocks
==18799==   total heap usage: 22 allocs, 22 frees, 198 bytes allocated
==18799== 
==18799== All heap blocks were freed -- no leaks are possible
==18799== 
==18799== For counts of detected and suppressed errors, rerun with: -v
==18799== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

