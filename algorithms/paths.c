/*see README for original credits */

#include "backtrack.h"
#include "bool.h"
#include "graph.h"
#include <stdio.h>

static int solution_count;			/* how many solutions are there? */
static graph g;				/* graph to traverse */

void process_solution(int a[], int k) {
	int i;				/* counter */

  solution_count ++;
  printf("{");
  for(i = 1; i <= k; i++)
    printf(" %d", a[i]);
  printf(" }\n");
}

int is_a_solution(const int a[], int k, int t) {
	return (a[k] == t);
}

void make_move(const int a[], int k, int n) {}
void unmake_move(const int a[], int k, int n) {}

/*	What are possible elements of the next slot in the path
*/

void construct_candidates(const int a[], int k, int n, int c[], int *ncandidates) {
	int i;				/* counters */
	bool in_sol[NMAX];		/* what's already in the solution? */
	edgenode *p;			/* temporary pointer */
	int last;			/* last vertex on current path */

  for(i = 1; i < NMAX; i++) 
    in_sol[i] = FALSE;
  for(i = 1; i < k; i++) 
    in_sol[ a[i] ] = TRUE;

  if(k==1) {			/* always start from vertex 1 */
    c[0] = 1;
    *ncandidates = 1;
  } else	{
    *ncandidates = 0;
    last = a[k-1];
    p = g.edges[last];

    while(p != NULL) {
      if(!in_sol[ p->y ]) {
        c[*ncandidates] = p->y;
        *(ncandidates)++;
      }
      p = p->next;
    }
  }
}

int main(void) {
	int a[NMAX];			/* solution vector */
	int i;				/* counter */

  read_graph(&g, FALSE);
  print_graph(&g);

	for(i = 1; i <= g.nvertices; i++) {
		printf("\nPaths from 1 to %d:\n", i);
		back_track(a, 0, i);
	}
  return 0;
}

/* test run 
see fig 5.12 pp 174 "The Algorithm Design Manual" by Steve S. Skiena

osman@osman-desktop:~/src/algorithms$ ./paths
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

Paths from 1 to 1:
{ 1 }

Paths from 1 to 2:

Paths from 1 to 3:

Paths from 1 to 4:

Paths from 1 to 5:

Paths from 1 to 6:
*/
