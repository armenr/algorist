/*see LICENSES file for original credits*/

#ifndef STACK_H
#define STACK_H

#include"list.h"

typedef list* stack;

void clear_stack(stack* s);
bool empty_stack(const stack s);
stack init_stack(void);
item_type pop_stack(stack* s);
void push_stack(stack* s, const item_type x, size_t n);

#endif /* STACK_H */


