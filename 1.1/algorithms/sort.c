/*see README for original credits */

#include"../ds/priority-queue.h"
#include"../ds/queue.h"
#include"sort.h"
#include<limits.h>
#include<stdbool.h>
#include<stdlib.h>

static void merge(int s[], int low, int middle, int high);
static int partition(int s[], int l, int h);

int binary_search(const int s[], int key, int low, int high) {
	int middle;			/* index of middle element */

	if(low > high) return -1;	/* key not found */
	middle = (low + high)/2;
	if(s[middle] == key) return(middle);
	if(s[middle] > key) 
		return binary_search(s, key, low, middle - 1);
	else
		return binary_search(s, key, middle + 1, high);
}

void heap_sort(int s[], int n) {
  int i;
  priority_queue q;	/* heap for heapsort */

  make_heap(&q, s, n);

  for(i = 0; i < n; i++)
    s[i] = extract_min(&q);
}

void insertion_sort(int s[], int n) {
	int i,j;

	for(i = 1; i < n; i++) {
	  j = i;
	  while((j > 0) && (s[j] < s[j-1])) {
		  swap(&s[j], &s[j-1]);
		  j--;
	  }
	}
}

void merge_sort(int s[], int low, int high) {
	int middle;		

	if(low < high) {
		middle = (low + high)/2;
		merge_sort(s, low, middle);
		merge_sort(s, middle + 1, high);

		merge(s, low, middle, high);
	}
}

void quick_sort(int s[], int l, int h) {
	int p;			/* index of partition */

	if((h - l) > 0) {
		p = partition(s, l, h);
		quick_sort(s, l,  p - 1);
		quick_sort(s, p + 1, h);
	}
}

void selection_sort(int s[], int n) {
  int i,j;      
  int min;		

  for(i = 0; i < n; i++) {
    min = i;
    
    for(j = i + 1; j < n; j++) 
      if(s[j] < s[min]) 
      	min = j;
      	
    swap(&s[i], &s[min]);
  }
}

static bool compare(int a, int b) {
	if(a < b) return(LESS_THAN);
	if(a > b) return(GREATER_THAN);
	return(EQUAL_TO);
}

static int deq_buffer(queue* q) {
  int* ip = (int*)de_queue(q);
  if(ip != NULL) {
	  int i = *ip;
	  free(ip);	  
  	return i;
  } else
  	return INT_MIN;
}

static void merge(int s[], int low, int middle, int high) {
/*	int i;			*/
/*	queue buffer1, buffer2; // buffers to hold elements for merging */

/*	buffer1 = init_queue();*/
/*	buffer2 = init_queue();*/

/*	for(i = low; i <= middle; i++) */
/*		en_queue(&buffer1, &s[i], sizeof(s[i]));*/
/*	for(i = middle + 1; i <= high; i++) */
/*		en_queue(&buffer2, &s[i], sizeof(s[i]));*/

/*	i = low;*/
/*	while(!(empty_queue(buffer1) || empty_queue(buffer2))) {*/
/*		if(headq(&buffer1) <= headq(&buffer2))*/
/*			s[i++] = deq_buffer(&buffer1);*/
/*		else*/
/*			s[i++] = deq_buffer(&buffer2);*/
/*	}*/

/*	while(!empty_queue(&buffer1)) */
/*		s[i++] = deq_buffer(&buffer1);*/
/*		*/
/*	while(!empty_queue(&buffer2)) */
/*		s[i++] = deq_buffer(&buffer2);*/
/*	*/
/*	clear_queue(&buffer1);*/
/*	clear_queue(&buffer2);*/
}

/*	Swap the ith and jth elements of array s.	*/
static void newswap(int s[], int i, int j) {
	int tmp;		

	tmp = s[i]; s[i] = s[j]; s[j] = tmp;
}

static int partition(int s[], int l, int h) {
	int i, p;			/* pivot element index */
	int firsthigh;		/* divider position for pivot element */

	p = h;
	firsthigh = l;
	
	for(i = l; i < h; i++) 
		if(s[i] < s[p]) {
			swap(&s[i], &s[firsthigh]);
			firsthigh++;
		}
		
	swap(&s[p], &s[firsthigh]);

	return firsthigh;
}


