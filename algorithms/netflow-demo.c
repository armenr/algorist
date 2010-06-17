/*see README for original credits */

#include "bool.h"
#include "netflow.h"
#include <stdio.h>

int main(void) {
	flow_graph g;			/* graph to analyze */
	int source, sink;		/* source and sink vertices */
	int flow;			/* total flow */
	edgenode *p;			/* temporary pointer */

  printf("source sink: ");
	scanf("%d %d", &source, &sink);
	read_flow_graph(&g, TRUE);
	netflow(&g, source, sink);
	print_flow_graph(&g);

	flow = 0;
	p = g.edges[source];

	while (p != NULL) {
		flow += p->flow;
		p = p->next;
	}

	printf("total flow = %d\n", flow);
	return 0;
}

/* test run
see fig 6.13 pp 219 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 10 edges

               *(4)
                        *(7)
                                                                        
              
     (2)*       *(5)    *(6)

                
        
          *         *                          
         (1)        (3)

osman@osman-desktop:~/src/algorithms$ ./netflow-demo 
source sink: 1 7
enter # vertices and # edges: 7 10
enter edge 1 (x, y, w): 1 2 5
enter edge 2 (x, y, w): 1 3 12
enter edge 3 (x, y, w): 2 4 7
enter edge 4 (x, y, w): 2 5 9
enter edge 5 (x, y, w): 3 5 4
enter edge 6 (x, y, w): 3 6 7
enter edge 7 (x, y, w): 4 5 3
enter edge 8 (x, y, w): 4 7 5
enter edge 9 (x, y, w): 5 6 3
enter edge 10 (x, y, w): 6 7 2
1:  3(12, 2, 10) 2(5, 5, 0)
2:  1(0, 0, 5) 5(9, 0, 9) 4(7, 5, 2)
3:  1(0, 0, 2) 6(7, 2, 5) 5(4, 0, 4)
4:  2(0, 0, 5) 7(5, 5, 0) 5(3, 0, 3)
5:  4(0, 0, 0) 3(0, 0, 0) 2(0, 0, 0) 6(3, 0, 3)
6:  5(0, 0, 0) 3(0, 0, 2) 7(2, 2, 0)
7:  6(0, 0, 2) 4(0, 0, 5)
total flow = 7
*/
