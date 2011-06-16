/*see README for original credits */

#include <stdio.h>

/*	Comparison macros 	*/

#define	max(A, B)		((A) > (B) ? (A) : (B))
#define min(A, B)		((A) < (B) ? (A) : (B))


void process(int i, int j) {
	printf("(%d,%d)\n", i, j);
}

void row_major(int n, int m) {
	int i,j;	

	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			process(i, j);
}

void column_major(int n, int m) {
	int i, j;	

	for(j = 1; j <= m; j++)
		for(i = 1; i <= n; i++)
			process(i, j);
}


void snake_order(int n, int m) {
	int i, j;	

	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			process(i, j + (m+1-2*j) * ((i+1) % 2));
}

void diagonal_order(int n, int m) {
	int d, j;	/* diagonal and point counters */
	int pcount;	/* points on diagonal */
	int height;	/* row of lowest point */

	for(d = 1; d <= (m+n-1); d++) {
		height = 1 + max(0, d-m);
		pcount = min(d, (n-height+1));
		
		for(j = 0; j < pcount; j++)
			process(min(m, d)-j, height+j);
	}
}

int main(void) {
  printf("row_major\n");
  row_major(5, 5);

  printf("\ncolumn_major\n");
  column_major(3, 3);

  printf("\nsnake_order\n");
  snake_order(5, 5);

  printf("\ndiagonal_order\n");
  diagonal_order(3, 4);

  printf("\ndiagonal_order\n");
  diagonal_order(4, 3);

  return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms$ ./order
row_major
(1,1)
(1,2)
(1,3)
(1,4)
(1,5)
(2,1)
(2,2)
(2,3)
(2,4)
(2,5)
(3,1)
(3,2)
(3,3)
(3,4)
(3,5)
(4,1)
(4,2)
(4,3)
(4,4)
(4,5)
(5,1)
(5,2)
(5,3)
(5,4)
(5,5)

column_major
(1,1)
(2,1)
(3,1)
(1,2)
(2,2)
(3,2)
(1,3)
(2,3)
(3,3)

snake_order
(1,1)
(1,2)
(1,3)
(1,4)
(1,5)
(2,5)
(2,4)
(2,3)
(2,2)
(2,1)
(3,1)
(3,2)
(3,3)
(3,4)
(3,5)
(4,5)
(4,4)
(4,3)
(4,2)
(4,1)
(5,1)
(5,2)
(5,3)
(5,4)
(5,5)

diagonal_order
(1,1)
(2,1)
(1,2)
(3,1)
(2,2)
(1,3)
(4,1)
(3,2)
(2,3)
(4,2)
(3,3)
(4,3)

diagonal_order
(1,1)
(2,1)
(1,2)
(3,1)
(2,2)
(1,3)
(3,2)
(2,3)
(1,4)
(3,3)
(2,4)
(3,4)
*/
