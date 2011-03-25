/*see LICENSES file for original credits*/

#include"queue.h"
#include<string.h>

static list* tail;  /*so we can add to back of list instead of front*/

void clear_queue(queue* q) {
  clear_list(q);
}

bool empty_queue(const queue q) {
  return empty_list(q); 
}

item_type head_queue(const queue q) {
	return head_list(q);
}

queue init_queue(void) {
	return init_list();
}

item_type de_queue(queue* q) {
  item_type x;
  queue p;

  if(*q != NULL) {
    x = (*q)->item;
    p = *q;
    *q = p->next;
    free(p);
    return x; /*caller must free this item*/
    
  } else
    return NULL;
}

void en_queue(queue* q, const item_type x, size_t n) {
	list* p = malloc(sizeof(list));
  p->item = malloc(n);  
	memcpy(p->item, x, n);
	p->next = NULL;
	
  if(*q != NULL) {
  	tail->next = p; 
    tail = p;
  }	else {
	  *q  = tail = p;
  }
}

void print_queue(const queue q, void (*print_item)(void*)) {
	print_list(q, print_item);
}
