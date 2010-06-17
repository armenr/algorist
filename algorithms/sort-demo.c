/*see README for original credits */

#include "random.h"
#include "sort.h"
#include <stdio.h>

int main(void) {
	int s[NELEM + 2];
	int i;

	for(i = 0; i < NELEM; i++) s[i] = NELEM - i;
	random_permutation(s, NELEM);

	insertion_sort(s, NELEM);

  printf("\n\nInsertion sort: \n");
  for(i = 0; i < NELEM; i++) printf("%d ", s[i]);

  for(i = 0; i < NELEM; i++) s[i] = NELEM - i;
		random_permutation(s, NELEM);

  selection_sort(s, NELEM);

	printf("\n\nSelection sort: \n");
  for(i = 0; i < NELEM; i++) printf("%d ", s[i]);

  for(i = 0; i < NELEM; i++) s[i] = NELEM - i;
		random_permutation(s, NELEM);

	quicksort(s, 0, NELEM - 1);

	printf("\n\nQuicksort: \n");
  for(i = 0; i < NELEM; i++) printf("%d ", s[i]);

  for(i = 0; i < NELEM; i++) s[i] = NELEM - i;
	random_permutation(s, NELEM);

	heapsort(s, NELEM);

	printf("\n\nHeapsort sort: \n");
  for(i = 0; i < NELEM; i++) printf("%d ", s[i]);

  for(i = 0; i < NELEM; i++) s[i] = NELEM - i;
	random_permutation(s, NELEM);

  printf("\n");
  for(i = 0; i < NELEM; i++) printf("%d ", s[i]);
  printf("\n");

  mergesort(s, 0, NELEM - 1);
  printf("\n\nMergesort: \n");
  for(i=0; i<NELEM; i++) printf("%d ", s[i]);
  printf("\n");

	/* test binary search */
	for(i = 0; i < NELEM; i++) s[i] = 2 * (NELEM - i);
	random_permutation(s, NELEM);

	heapsort(s, NELEM);
	for(i = 0; i < 2 * NELEM + 1; i++)
		printf("%d found in %d\n", i, binary_search(s, i, 0, NELEM - 1));
		
  return 0;		
}

