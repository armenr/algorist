/*see README for original credits */

#ifndef PARTITION_H
#define PARTITION_H

#define	MAXN	45		/* largest number of books */
#define MAXK	10		/* largest number of dividers */
#define MAXINT	100000		/* infinity */

/*	Comparison macros 	*/
#define	max(A, B)		((A) > (B) ? (A) : (B))
#define min(A, B)		((A) < (B) ? (A) : (B))

void read_partition(int s[], int *n, int *k);
void print_books(const int s[], int start, int end);
void print_matrix(const int m[MAXN+1][MAXK+1], int n, int k);
void reconstruct_partition(const int s[], int d[MAXN+1][MAXK+1], int n, int k);
void partition(const int s[], int n, int k);

#endif /* PARTITION_H */
