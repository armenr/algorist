/*see README for original credits */

#include "bool.h"
#include "backtrack.h"
#include <stdio.h>

void process_solution(const int a[], int k) {
	int i;				/* counter */

	for(i = 1; i <= k; i++) printf(" %d", a[i]);
	printf("\n");
}

bool is_a_solution(const int a[], int k, int n) {
	return (k == n);
}

void make_move(const int a[], int k, int n) {}
void unmake_move(const int a[], int k, int n){}


/*	What are possible elements of the next slot in the permutation?  */
void construct_candidates(const int a[], int k, int n, int c[], int *ncandidates) {
	int i;				/* counter */
	bool in_perm[NMAX];		/* what is now in the permutation? */

	for(i = 1; i < NMAX; i++) in_perm[i] = FALSE;
	for(i = 1; i < k; i++) in_perm[ a[i] ] = TRUE;

	*ncandidates = 0;
	for(i = 1; i <= n; i++) 
		if(in_perm[i] == FALSE) {
			c[*ncandidates] = i;
			(*ncandidates)++;
		}
}

int main(void) {
	int a[NMAX];			/* solution vector */
	back_track(a,0,0);	back_track(a,0,1);	back_track(a,0,2);	
	back_track(a,0,3);
	return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms$ ./permutations 

 1
 1 2
 2 1
 1 2 3
 1 3 2
 2 1 3
 2 3 1
 3 1 2
 3 2 1
*/
