/*see README for original credits */

#include "bool.h"
#include "stack.h"
#include <stdio.h>

int empty_stack(const stack *s) {
  if(s->count <= 0) return (TRUE);
  else return (FALSE);
}

void init_stack(stack *s) {
  s->top = -1;
  s->count = 0;
}

int pop(stack *s) {
  int x;

  if(s->count <= 0) printf("Warning: empty stack pop.\n");
  else {
    x = s->s[ s->top ];
    s->top = s->top - 1;
    s->count = s->count - 1;
  }

  return(x);
}

void print_stack(const stack *s) {
  int i;				/* counter */

  for(i = (s->count-1); i >= 0; i--)
    printf("%d ",s->s[i]);

  printf("\n");
}

void push(stack *s, int x) {
  if(s->count >= STACKSIZE)
    printf("Warning: stack overflow push x=%d\n",x);
  else {
    s->top = s->top + 1;
    s->s[ s->top ] = x;
    s->count = s->count + 1;
  }
}
