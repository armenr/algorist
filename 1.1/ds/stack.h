/*see README for original credits */

#ifndef STACK_H
#define STACK_H

#include"list.h"

typedef list* stack;

void clear_stack(stack s);
bool empty_stack(const stack s);
void init_stack(stack* s);
void* pop_stack(stack* s);
void push_stack(stack* s, const void* item, int sz);
void print_stack(const stack s, void (*print_item)(const void* item));

#endif /* STACK_H */
