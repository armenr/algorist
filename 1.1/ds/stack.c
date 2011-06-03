/*see README for original credits */

#include<stdlib.h>
#include"stack.h"

void clear_stack(stack s) {
  clear_list(s);
}

bool empty_stack(const stack s) {
  return empty_list(s); 
}

void init_stack(stack* s) {
	return init_list(s);
}

void* pop_stack(stack* s) {
  void* item;
  stack p;

  if(*s != NULL) {
    item = (*s)->item;
    p = *s;
    *s = p->next;
    free(p);
    return item; /*caller must free this item*/
    
  } else
    return NULL;

}

void push_stack(stack* s, const void* item, int sz) {
  insert_list(s, item, sz);
}

void print_stack(const stack s, void (*print_item)(const void* item)) {
	print_list(s, print_item);
}
