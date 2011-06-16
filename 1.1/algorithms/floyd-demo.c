/*see README for original credits */

#include<stdbool.h>
#include "floyd.h"

int main(void) {
	adjacency_matrix g;
	read_adjacency_matrix(&g, false);
	print_graph(&g);
	floyd(&g);
	print_adjacency_matrix(&g);
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

osman@osman-desktop:~/src/algorithms$ ./floyd 
enter # vertices and # edges: 7 12
enter edge 1 (x, y, w): 1 2 12
enter edge 2 (x, y, w): 1 5 5
enter edge 3 (x, y, w): 1 6 7
enter edge 4 (x, y, w): 2 3 7
enter edge 5 (x, y, w): 2 6 4
enter edge 6 (x, y, w): 3 4 2
enter edge 7 (x, y, w): 3 6 3
enter edge 8 (x, y, w): 3 7 2
enter edge 9 (x, y, w): 4 5 7
enter edge 10 (x, y, w): 4 6 4
enter edge 11 (x, y, w): 4 7 5
enter edge 12 (x, y, w): 5 6 9
1:  2 5 6
2:  1 3 6
3:  2 4 6 7
4:  3 5 6 7
5:  1 4 6
6:  1 2 3 4 5
7:  3 4
  1:   10  11  10  11   5   7  12
  2:   11   8   7   8  13   4   9
  3:   10   7   4   2   9   3   2
  4:   11   8   2   4   7   4   4
  5:    5  13   9   7  10   9  11
  6:    7   4   3   4   9   6   5
  7:   12   9   2   4  11   5   4

*/ 
