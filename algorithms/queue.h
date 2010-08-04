/*see README for original credits */

#ifndef QUEUE_H
#define QUEUE_H

#define QUEUESIZE       1000

#include "item.h"

typedef struct {
  int q[QUEUESIZE+1];	            /* body of queue */
  int first;                      /* position of first element */
  int last;                       /* position of last element */
  int count;                      /* number of queue elements */
} queue;

item_type dequeue(queue *q);
int empty_queue(const queue *q);
void enqueue(queue *q, item_type x);
item_type headq(const queue *q);
void init_queue(queue *q);
void print_queue(const queue *q);

#endif /* QUEUE_H */




