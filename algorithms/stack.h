/*see README for original credits */

#ifndef STACK_H
#define STACK_H

#define STACKSIZE       1000

typedef struct {
  int s[STACKSIZE+1];		/* body of queue */
  int top;                        /* position of top element */
  int count;                      /* number of stack elements */
} stack;

int empty_stack(const stack *s);
void init_stack(stack *s);
int pop(stack *s);
void print_stack(const stack *s);
void push(stack *s, int x);

#endif /* STACK_H */


