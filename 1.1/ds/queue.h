/*see README for original credits */

#ifndef QUEUE_H
#define QUEUE_H

#include"list.h"

typedef struct queue {
  list* tail; /* pointer to last element*/
  list* data; /* linked list of items*/
} queue;

void clear_queue(queue* q);
bool empty_queue(const queue* q);
const void* head_queue(const queue* q);
void init_queue(queue* q);
void* de_queue(queue* q);
void en_queue(queue* q, const void* item, int sz);
void print_queue(const queue* q, void (*print_item)(const void* item));

#endif /* QUEUE_H */
