/*see README for original credits */

#include "bfs-dfs.h"
#include "bool.h"
#include "graph.h"
#include "queue.h"
#include<stdio.h>

static int reachable_ancestor[MAXV + 1]; /* earliest reachable ancestor of v */
static int tree_out_degree[MAXV + 1]; /* DFS tree outdegree of v */

void process_vertex_early(int v) {
  reachable_ancestor[v] = v;
}

void process_vertex_late(int v) {
  bool root; /* is a given vertex the root of the DFS tree? */
  int time_v; /* earliest reachable time for v */
  int time_parent; /* earliest reachable time for parent[v] */

  if(parent[v] < 1) { /* test if v is the root */
    if(tree_out_degree[v] > 1)
      printf("root articulation vertex: %d \n", v);
    return;
  }

  root = (parent[parent[v]] < 1); /* test if parent[v] is root */
  if((reachable_ancestor[v] == parent[v]) && (!root))
    printf("parent articulation vertex: %d \n", parent[v]);

  if(reachable_ancestor[v] == v) {
    printf("bridge articulation vertex: %d \n", parent[v]);

    if(tree_out_degree[v] > 0) /* test if v is not a leaf */
      printf("bridge articulation vertex: %d \n", v);
  }

  time_v = entry_time[reachable_ancestor[v]];
  time_parent = entry_time[ reachable_ancestor[parent[v]] ];

  if(time_v < time_parent)
    reachable_ancestor[parent[v]] = reachable_ancestor[v];
}

void process_edge(int x, int y) {
  int class; /* edge class */

  class = edge_classification(x, y);

  /*printf("(%d,%d) class %d tree_out_degree[%d]=%d\n", x,y,class,x,tree_out_degree[x]);*/
  if(class == TREE)
    tree_out_degree[x] = tree_out_degree[x] + 1;

  if((class == BACK) && (parent[x] != y)) 
    if(entry_time[y] < entry_time[ reachable_ancestor[x] ])
      reachable_ancestor[x] = y;
}

static void articulation_vertices(graph *g) {
  int i; 

  for(i = 1; i <= (g->nvertices); i++)
    tree_out_degree[i] = 0;

  initialize_search((const graph *)&g);

  for(i = 1; i <= (g->nvertices); i++)
    if(discovered[i] == FALSE) 
      dfs(g, i);
}

int main(void) {
  graph g;

  read_graph(&g, FALSE);
  print_graph(&g);
  articulation_vertices(&g);
  
  return 0;
}

/* test run 
see fig 5.12 pp 174 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./biconnected 
enter # vertices and # edges: 6 6
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 6 0
enter edge 3 (x, y, w): 2 3 0
enter edge 4 (x, y, w): 3 4 0
enter edge 5 (x, y, w): 4 5 0
enter edge 6 (x, y, w): 5 2 0
1:  6 2
2:  5 3 1
3:  4 2
4:  5 3
5:  2 4
6:  1
bridge articulation vertex: 1 
parent articulation vertex: 2 
bridge articulation vertex: 1 
bridge articulation vertex: 2 
root articulation vertex: 1 

osman@osman-desktop:~/src/algorithms$ ./biconnected 
enter # vertices and # edges: 3 2
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 3 0
1:  3 2
2:  1
3:  1
bridge articulation vertex: 1 
bridge articulation vertex: 1 
root articulation vertex: 1 

see fig 5.14 pp 178 "The Algorithm Design Manual" by Steve S. Skiena
(tree edges)
osman@osman-desktop:~/src/algorithms$ ./biconnected 
enter # vertices and # edges: 5 4
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 3 0
enter edge 3 (x, y, w): 2 4 0
enter edge 4 (x, y, w): 2 5 0
1:  3 2
2:  5 4 1
3:  1
4:  2
5:  2
bridge articulation vertex: 1 
bridge articulation vertex: 2 
bridge articulation vertex: 2 
bridge articulation vertex: 1 
bridge articulation vertex: 2 
root articulation vertex: 1 

see fig 5.14 pp 178 "The Algorithm Design Manual" by Steve S. Skiena
(back edge)
osman@osman-desktop:~/src/algorithms$ ./biconnected 
enter # vertices and # edges: 5 5
enter edge 1 (x, y, w): 1 2 0
enter edge 2 (x, y, w): 1 3 0
enter edge 3 (x, y, w): 2 4 0
enter edge 4 (x, y, w): 2 5 0
enter edge 5 (x, y, w): 5 1 0
1:  5 3 2
2:  5 4 1
3:  1
4:  2
5:  1 2
bridge articulation vertex: 2 
bridge articulation vertex: 1 
root articulation vertex: 1 

*/
