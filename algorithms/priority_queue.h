/*see README for original credits */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "item.h"

#define PQ_SIZE       1000

typedef struct {
  item_type q[PQ_SIZE+1];		      /* body of queue */
  int n;                          /* number of queue elements */
} priority_queue;

int empty_pq(const priority_queue *q);
item_type extract_min(priority_queue *q);
void pq_init(priority_queue *q);
void pq_insert(priority_queue *q, item_type x);
void make_heap(priority_queue *q, const item_type s[], int n);
void make_heap1(priority_queue *q, const item_type s[], int n);
void print_pq(const priority_queue *q);

#endif /* PRIORITY_QUEUE_H */

