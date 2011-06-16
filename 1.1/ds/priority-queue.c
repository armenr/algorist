/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"priority-queue.h"

static void bubble_down(priority_queue* q, int p);
static void bubble_up(priority_queue* q, int p);
static int parent(int n);
static void swap(priority_queue* q, int i, int j);
static int young_child(int n);

void clear_pq(priority_queue* q) {
  int i;
  
  for(i = 0; i < q->n; i++)
    if(q->q[i].item != NULL)
    	free(q->q[i].item);
}

bool empty_pq(const priority_queue* q) {
  if(q->n <= 0) 
  	return true;
  return false;
}

void* extract_min(priority_queue* q) {
  void* item = NULL;

  if(q->n <= 0) 
  	printf("Warning: empty priority queue.\n");
  	
  else {
		q->q[1].pos = q->q[q->n].pos;
  	item = q->q[1].item;	/*caller must free this item*/
		q->q[1].item = q->q[q->n].item;
		(q->n)--;
		bubble_down(q, 1);
  }

  return item;
}

void pq_init(priority_queue* q) {
  q->n = 0;
}

void pq_insert(priority_queue* q, const pq_data item, int sz) {
  if(q->n >= PQ_SIZE)
		printf("Warning: priority queue overflow pq_insert\n");
		
  else {
		(q->n)++;
		q->q[q->n].pos = item.pos;		
		q->q[q->n].item = malloc(sz);
		memcpy(q->q[q->n].item, item.item, sz);
		bubble_up(q, q->n);
  }
}

void make_heap(priority_queue* q, const pq_data s[], int n, int sz) {
  int i;

  pq_init(q);
  for(i = 0; i < n; i++)
    pq_insert(q, s[i], sz);
}

/*void print_pq(const priority_queue* q) {*/
/*  int i;*/

/*  for(i = 1; i <= q->n; i++)*/
/*    printf("%d %d\n", *(int*)q->q[i].item, q->q[i].pos);*/

/*  printf("\n");*/
/*}*/

static void bubble_down(priority_queue* q, int p) {
	int c;				/* child index */
	int i;
	int min_index;		        /* index of lightest child */

	c = young_child(p);
	min_index = p;

	for(i = 0; i <= 1; i++) 
		if((c + i) <= q->n) 
  		if(q->q[min_index].pos > q->q[c + i].pos) 
  			min_index = c + i;

  if(min_index != p) {
		swap(q, p, min_index);
    bubble_down(q, min_index);
  }
}

static void bubble_up(priority_queue* q, int p) {
	if(parent(p) == -1)	
		return;	/* at root of heap, no parent */

	if(q->q[parent(p)].pos > q->q[p].pos) {
		swap(q, p, parent(p));
		bubble_up(q, parent(p));
	}
}

static int parent(int n) {
	if(n == 1) 
		return -1;
	else 
		return (int) n/2;		/* implicitly take floor(n/2) */
}

static void swap(priority_queue* q, int i, int j) {
	void* temp_item = q->q[i].item;
	int temp_pos = q->q[i].pos;
	
	q->q[i].item = q->q[j].item;
	q->q[i].pos = q->q[j].pos;
	q->q[j].item = temp_item;
	q->q[j].pos = temp_pos;
}

static int young_child(int n) {
	return 2*n;
}
