/*see README for original credits */

#include<string.h>
#include<stdlib.h>
#include"queue.h"

void clear_queue(queue* q) {
  clear_list(q->data);
}

bool empty_queue(const queue* q) {
  return empty_list(q->data); 
}

const void* head_queue(const queue* q) {
	return head_list(q->data);
}

void init_queue(queue* q) {
	init_list(&(q->data));
}

void* de_queue(queue* q) {
  void* item;
  queue p;

  if(q->data != NULL) {
    item = q->data->item;
    p.data = q->data;
    q->data = p.data->next;
    free(p.data);
    return item; /*caller must free this item*/
    
  } else
    return NULL;
}

void en_queue(queue* q, const void* item, int sz) {
	list* p = malloc(sizeof(list));
  p->item = malloc(sz);  
	memcpy(p->item, item, sz);
	p->next = NULL;
	
  if(q->data != NULL) {
  	q->tail->next = p; 
    q->tail = p;   
  }	else  /* new queue*/
	  q->data = q->tail = p;
}

void print_queue(const queue* q, void (*print_item)(const void* item)) {
	print_list(q->data, print_item);
}
