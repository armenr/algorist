/*see README for original credits */

#include"stack.h"
#include<ctype.h>
#include<stdio.h>

static void print_item(int* item) {
  printf("%d ", *item);
}

int main(void) {
	char c;			/* input character */
	int d;		/* input item */
	stack s;		/* list under construction */
	
	s = init_stack();

  printf("stack options: (1)push, (2)pop, (3)print, (q)uit \n");
	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) 

		if(c == '1') {
		  printf("push item: ");
			scanf("%d", &d);
      printf("new item: %d\n", d);
			push_stack(&s, &d, sizeof(int));
		
		} else if(c == '2') {
		  int *ip = (int*)pop_stack(&s);
		  
		  if(ip != NULL) {
  		  printf("popped item: %d\n", *ip);
  		  free(ip);	  
  		  
		  } else
  		  printf("stack empty\n");
  		  
		} else if(c == '3')
			print_stack(s, print_item);
	
	clear_stack(&s);
	return 0;
}
