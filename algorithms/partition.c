/*see README for original credits */

#include "partition.h"
#include <stdio.h>

void read_partition(int s[], int *n, int *k) {
	int i;
  
  printf("enter range and # partitions: ");
	scanf("%d %d", n, k);
	for(i = 1; i <= *n; i++) {
	  printf("enter size of partition %d: ", i);
		scanf("%d", &(s[i]));
	}
}

void print_books(const int s[], int start, int end) {
	int i;

	printf("\{");
	for(i = start; i <= end; i++) 
	  printf(" %d ", s[i]);
	printf("}\n");
}

void print_matrix(const int m[MAXN+1][MAXK+1], int n, int k) {
	int i, j;	


	printf("\n");
	for(i = 1; i <= n; i++) 
		for(j = 1; j <= k; j++) 
			printf(" %d ", m[i][j]);
		printf("\n");
}

void reconstruct_partition(const int s[], int d[MAXN+1][MAXK+1], int n, 
  int k) {
	if(k == 1)
		print_books(s, 1, n);
	else {
		reconstruct_partition(s, d, d[n][k], k-1);
		print_books(s, d[n][k]+1, n);
	}
}

void partition(const int s[], int n, int k) {
	int p[MAXN+1];				/* prefix sums array */
	int m[MAXN+1][MAXK+1];			/* DP table for values */
	int d[MAXN+1][MAXK+1];			/* DP table for dividers */
	int cost;				/* test split cost */
	int i,j,x;				/* counters */

	p[0] = 0;				/* construct prefix sums */
	for(i = 1; i <= n; i++) 
	p[i] = p[i-1] + s[i];

	for(i = 1; i <= n; i++) 
	  m[i][1] = p[i];	/* initialize boundaries */
	for(j = 1; j <= k; j++) 
	  m[1][j] = s[1];

	for(i = 2; i <= n; i++)			/* evaluate main recurrence */
		for(j = 2; j <= k; j++) {
			m[i][j] = MAXINT;
			
			for(x = 1; x <= (i-1); x++) {
				cost = max(m[x][j-1], p[i]-p[x]);
				if(m[i][j] > cost) {
					m[i][j] = cost;
					d[i][j] = x;
				}
			}
		}

	reconstruct_partition((const int *)s, d, n, k);		/* print book partition */
}



int main(void) {
	int s[MAXN+1];			/* book thicknesses to partition */
	int n;				/* how many books? */
	int k;				/* how many partitions? */

	read_partition(s, &n, &k);
	partition((const int *)s, n, k);
  return 0;
}

/* test runs
osman@osman-desktop:~/src/algorithms$ ./partition 
enter range and # partitions: 9 3
enter size of partition 1: 1
enter size of partition 2: 1
enter size of partition 3: 1
enter size of partition 4: 1
enter size of partition 5: 1
enter size of partition 6: 1
enter size of partition 7: 1
enter size of partition 8: 1
enter size of partition 9: 1
{ 1  1  1 }
{ 1  1  1 }
{ 1  1  1 }
osman@osman-desktop:~/src/algorithms$ ./partition 
enter range and # partitions: 3 2
enter size of partition 1: 2
enter size of partition 2: 4
enter size of partition 3: 6
{ 2  4 }
{ 6 }
osman@osman-desktop:~/src/algorithms$ ./partition 
enter range and # partitions: 4 3
enter size of partition 1: 10
enter size of partition 2: 8
enter size of partition 3: 20
enter size of partition 4: 4
{ 10  8 }
{ 20 }
{ 4 }
*/
