/*see README for original credits */

#include"random.h"
#include"sort.h"
#include<stdio.h>

static void randomizeArray(int s[]) {
	int i;
	for(i = 0; i < NELEM; i++) 
		s[i] = NELEM - i;
	random_permutation(s, NELEM);
}

static void printArray(int s[]) {
	int i;
  for(i = 0; i < NELEM; i++) 
  	printf("%d ", s[i]);
}

int main(void) {
	int s[NELEM + 2];
	
  printf("\n\nRandomized array from 1 to %d: \n", NELEM);
	randomizeArray(s);
  printArray(s);
	insertion_sort(s, NELEM);
  printf("\n\nInsertion sort: \n");
  printArray(s);
  
  printf("\n\nRandomized array from 1 to %d: \n", NELEM);
	randomizeArray(s);
  printArray(s);
  selection_sort(s, NELEM);
	printf("\n\nSelection sort: \n");
  printArray(s);

  printf("\n\nRandomized array from 1 to %d: \n", NELEM);
	randomizeArray(s);
  printArray(s);
	quick_sort(s, 0, NELEM - 1);
	printf("\n\nQuick sort: \n");
  printArray(s);

  printf("\n\nRandomized array from 1 to %d: \n", NELEM);
	randomizeArray(s);
  printArray(s);
	heap_sort(s, NELEM);
	printf("\n\nHeap sort: \n");
  printArray(s);


  printf("\n\nRandomized array from 1 to %d: \n", NELEM);
	randomizeArray(s);
  printArray(s);
  merge_sort(s, 0, NELEM - 1);
	printf("\n\nMerge sort: \n");
  printArray(s);

/*	/* test binary search */
/*	for(i = 0; i < NELEM; i++) s[i] = 2 * (NELEM - i);*/
/*	random_permutation(s, NELEM);*/

/*	heap_sort(s, NELEM);*/
/*	for(i = 0; i < 2 * NELEM + 1; i++)*/
/*		printf("%d found in %d\n", i, binary_search(s, i, 0, NELEM - 1));*/

	printf("\n");		
  return 0;		
}

