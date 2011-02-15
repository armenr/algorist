/*see README for original credits */

#include "bool.h"
#include <stdio.h>

#define MAXCANDIDATES   100		/* max possible next extensions */
#define NMAX            100		/* maximum solution size */

static int ncandidates = 2;                /* next position candidate count */

static void process_solution(const int a[], int k) {
	int i;				
	
	printf("{");
	for(i = 1; i <= k; i++)
		if(a[i] == TRUE) 
		  printf(" %d",i);

	printf(" }\n");
}

static bool is_a_solution(int k, int n) {
	return (k == n);
}

/*	What are possible elements of the next slot in the permutation?  */
static void construct_candidates(int c[]) {
	c[0] = TRUE; c[1] = FALSE; 
}

void back_track(int a[], int k, int input) {
  int c[MAXCANDIDATES];           /* candidates for next position */
  int i;                          /* counter */

  if(is_a_solution(k, input))
    process_solution(a, k);
  else {
    k++;
    construct_candidates(c);

    for(i = 0; i < ncandidates; i++) {   
      a[k] = c[i];
/*printf("k = %d, i = %d, a[%d] = %d\n", k, i, k, a[k]);    */
/*printf("back_track k %d input %d\n", k, input);      */
      back_track(a, k, input);
    }
  }
}

int main(void) {
	int a[NMAX];			/* solution vector */
	back_track(a, 0, 3);
	return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms$ ./subsets
{ 1 2 3 }
{ 1 2 }
{ 1 3 }
{ 1 }
{ 2 3 }
{ 2 }
{ 3 }
{ }
*/
