/*see README for original credits */

#include "bool.h"
#include "priority_queue.h"
#include <stdio.h>

static void bubble_down(priority_queue *q, int p);
static void bubble_up(priority_queue *q, int p);
static int pq_parent(int n);
static void pq_swap(priority_queue *q, int i, int j);
static int pq_young_child(int n);


int empty_pq(const priority_queue *q) {
  if(q->n <= 0) return TRUE;
  else return FALSE;
}

item_type extract_min(priority_queue *q) {
  int min = -1;

  if(q->n <= 0) printf("Warning: empty priority queue.\n");
  else {
  min = q->q[1];

  q->q[1] = q->q[ q->n ];
  q->n = q->n - 1;
  bubble_down(q,1);
  }

  return(min);
}

void pq_init(priority_queue *q) {
  q->n = 0;
}

void pq_insert(priority_queue *q, item_type x) {
  if(q->n >= PQ_SIZE)
		printf("Warning: priority queue overflow insert x=%d\n",x);
  else {
		q->n = (q->n) + 1;
		q->q[ q->n ] = x;
		bubble_up(q, q->n);
  }
}

void make_heap(priority_queue *q, const item_type s[], int n) {
  int i;

  q->n = n;
  for(i = 0; i < n; i++)
    q->q[i+1] = s[i];

  for(i = q->n; i >= 1; i--)
    bubble_down(q, i);
}

void make_heap1(priority_queue *q, const item_type s[], int n) {
  int i;

  pq_init(q);
  for( i= 0; i < n; i++)
    pq_insert(q, s[i]);
}

void print_pq(const priority_queue *q) {
  int i;

  for(i = 1; i <= q->n; i++)
    printf("%d ", q->q[i]);

  printf("\n");
}


static void bubble_down(priority_queue *q, int p) {
	int c;				/* child index */
	int i;
	int min_index;		        /* index of lightest child */

	c = pq_young_child(p);
	min_index = p;

	for(i = 0; i <= 1; i++) 
		if((c + i) <= q->n) 
  		if(q->q[min_index] > q->q[c + i]) min_index = c + i;

  if(min_index != p) {
		pq_swap(q, p, min_index);
    bubble_down(q, min_index);
  }
}

static void bubble_up(priority_queue *q, int p) {
	if(pq_parent(p) == -1)	return;	/* at root of heap, no parent */

	if(q->q[pq_parent(p)] > q->q[p]) {
		pq_swap(q, p, pq_parent(p));
		bubble_up(q, pq_parent(p));
	}
}

static int pq_parent(int n) {
	if(n == 1) return(-1);
	else return((int) n/2);		/* implicitly take floor(n/2) */
}

static void pq_swap(priority_queue *q, int i, int j) {
	item_type temp;

	temp = q->q[i];
	q->q[i] = q->q[j];
	q->q[j] = temp;
}

static int pq_young_child(int n) {
	return(2 * n);
}
