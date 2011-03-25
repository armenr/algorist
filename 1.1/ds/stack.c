/*see LICENSES file for original credits*/

#include"stack.h"

void clear_stack(stack* s) {
  clear_list(s);
}

bool empty_stack(const stack s) {
  return empty_list(s); 
}

stack init_stack(void) {
	return init_list();
}

item_type pop_stack(stack* s) {
  item_type x;
  stack p;

  if(*s != NULL) {
    x = (*s)->item;
    p = *s;
    *s = p->next;
    free(p);
    return x; /*caller must free this item*/
    
  } else
    return NULL;

}

void push_stack(stack* s, const item_type x, size_t n) {
  insert_list(s, x, n);
}

void print_stack(const stack s, void (*print_item)(void*)) {
	print_list(s, print_item);
}
