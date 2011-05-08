/*see README for original credits */

#include"bfs-dfs.h"
#include"prim.h"
#include<limits.h>
#include<stdbool.h>
#include<stdio.h>

/*
Prim-MST(G)
  Select an arbitrary vertex s to start the tree from.
  While (there are still nontree vertices)
    Select the edge of minimum weight between a tree and nontree vertex
    Add the selected edge and vertex to the tree Tprim .
*/
void prim(const graph *g, int start) {
	int i;

	bool intree[MAXV];		/* is the vertex in the tree yet? */
	int distance[MAXV];		/* cost of adding to tree */

	for(i = 0; i < MAXV; i++) {
		intree[i] = false;
		distance[i] = INT_MAX;
		parent[i] = -1;
	}

	distance[start] = 0;
	int v = start;  /* current vertex to process */

	while(!intree[v]) {
		intree[v] = true;
		edgenode* p = g->vertices[v].edges;

    /*update cost for non-tree vertices (p->y) neighboring v*/
		while(p != NULL) { 
			if((distance[p->y] > p->weight) && !intree[p->y]) {
				distance[p->y] = p->weight; /*lower cost */
				parent[p->y] = v; /*(p->y, v) pair describe this edge */
			}
			p = p->next;
		}

		v = 1;
		int dist = INT_MAX;
		
    /*find cheapest non-tree vertex to search from next*/
		for(i = 0; i < MAXV; i++) 
			if(!intree[i] && dist > distance[i]) {
				dist = distance[i];
				v = i;
			}
	}
	
	int n = 1, cost = 0;
	
	for(i = 0; i < MAXV; i++) 
	  if(intree[i] && parent[i] != -1) {
			printf("#%d edge: (%d, %d) of weight %d in MST\n", n++, i, parent[i],
			  distance[i]);
	    cost += distance[i];
	  }
  printf("total cost is %d\n", cost);
}

