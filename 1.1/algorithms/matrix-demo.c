/*see README for original credits */

#include "matrix.h"
#include <stdio.h>

int main(void) {
  matrix a,b,c;
  printf("enter first matrix\n");
  read_matrix(&a);
  print_matrix(&a);
  printf("enter second matrix\n");
  read_matrix(&b);
  print_matrix(&b);
  printf("matrix product\n");
  multiply(&a, &b, &c);
  print_matrix(&c);
  return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms$ ./matrix-demo 
enter first matrix
enter #rows #cols: 2 2
enter value: 1
enter value: 2
enter value: 3
enter value: 4
 1 2
 3 4

enter second matrix
enter #rows #cols: 2 2
enter value: 5
enter value: 6
enter value: 7
enter value: 8
 5 6
 7 8

matrix product
 19 22
 43 50
*/
