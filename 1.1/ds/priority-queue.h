/*see README for original credits */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include"item.h"
#include<stdbool.h>
#include<stdlib.h>

#define PQ_SIZE       1000

typedef struct {
  item_type item;
  int pos;
} pq_data;

typedef struct {
  pq_data q[PQ_SIZE+1];		      /* body of queue */
  int n;                          /* number of queue elements */
} priority_queue;

void clear_pq(priority_queue* q);
bool empty_pq(const priority_queue* q);
item_type extract_min(priority_queue* q);
void pq_init(priority_queue* q);
void pq_insert(priority_queue* q, const pq_data x, size_t sz);
void make_heap(priority_queue* q, const pq_data s[], int n, size_t sz);
//void print_pq(const priority_queue* q);

#endif /* PRIORITY_QUEUE_H */

