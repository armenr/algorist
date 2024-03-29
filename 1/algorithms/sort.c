/*see README for original credits */

#include "bool.h"
#include "priority_queue.h"
#include "queue.h"
#include "sort.h"
#include <stdlib.h>

static void merge(item_type s[], int low, int middle, int high);
static int partition(item_type s[], int l, int h);

int binary_search(const item_type s[], item_type key, int low, int high) {
	int middle;			/* index of middle element */

	if(low > high) return -1;	/* key not found */
	middle = (low + high)/2;
	if(s[middle] == key) return(middle);
	if(s[middle] > key) 
		return binary_search(s, key, low, middle - 1);
	else
		return binary_search(s, key, middle + 1, high);
}

void heapsort(item_type s[], int n) {
  int i;
  priority_queue q;	/* heap for heapsort */

  make_heap(&q, s, n);

  for(i = 0; i < n; i++)
    s[i] = extract_min(&q);
}

void insertion_sort(item_type s[], int n) {
	int i,j;

	for(i = 1; i < n; i++) {
	  j = i;
	  while((j > 0) && (s[j] < s[j-1])) {
		  swap(&s[j], &s[j-1]);
		  j = j-1;
	  }
	}
}

void mergesort(item_type s[], int low, int high) {
	int middle;		/* index of middle element */

	if(low < high) {
		middle = (low + high)/2;
		mergesort(s, low, middle);
		mergesort(s, middle + 1, high);

		merge(s, low, middle, high);
	}
}

void quicksort(item_type s[], int l, int h) {
	int p;			/* index of partition */

	if((h - l) > 0) {
		p = partition(s, l, h);
		quicksort(s, l,  p - 1);
		quicksort(s, p + 1, h);
	}
}

void selection_sort(item_type s[], int n) {
  int i,j;      
  int min;		

  for(i = 0; i < n; i++) {
    min = i;
    for(j = i + 1; j < n; j++) 
      if(s[j] < s[min]) min = j;
    swap(&s[i], &s[min]);
  }
}

static bool compare(item_type a, item_type b) {
	if(a < b) return(LESS_THAN);
	if(a > b) return(GREATER_THAN);
	return(EQUAL_TO);
}

static void merge(item_type s[], int low, int middle, int high) {
	int i;			/* counter */
	queue buffer1, buffer2; /* buffers to hold elements for merging */

	init_queue(&buffer1);
	init_queue(&buffer2);

	for(i = low; i <= middle; i++) enqueue(&buffer1, s[i]);
	for(i = middle + 1; i <= high; i++) enqueue(&buffer2, s[i]);

	i = low;
	while(!(empty_queue(&buffer1) || empty_queue(&buffer2))) {
		if(headq(&buffer1) <= headq(&buffer2))
			s[i++] = dequeue(&buffer1);
		else
			s[i++] = dequeue(&buffer2);
	}

	while(!empty_queue(&buffer1)) s[i++] = dequeue(&buffer1);
	while(!empty_queue(&buffer2)) s[i++] = dequeue(&buffer2);
}

/*	Swap the ith and jth elements of array s.	*/
static void newswap(item_type s[], int i, int j) {
	item_type tmp;		

	tmp = s[i]; s[i] = s[j]; s[j] = tmp;
}

static int partition(item_type s[], int l, int h) {
	int i;
	int p;			/* pivot element index */
	int firsthigh;		/* divider position for pivot element */

	p = h;
	firsthigh = l;
	for(i = l; i < h; i++) 
		if(s[i] < s[p]) {
			swap(&s[i], &s[firsthigh]);
			firsthigh ++;
		}
	swap(&s[p], &s[firsthigh]);

	return(firsthigh);
}


