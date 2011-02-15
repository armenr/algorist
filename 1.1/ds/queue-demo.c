/*see README for original credits */

#include"queue.h"
#include<ctype.h>
#include<stdio.h>

static void print_queue(const list* l) {
  while(l != NULL) {
    printf("%d ", *(int*)l->item);
    l = l->next;
  }
  printf("\n");
}

int main(void) {
	char c;			/* input character */
	int d;		/* input item */
	queue q;		/* list under construction */
	
	q = init_queue();

  printf("queue options: (1)enqueue, (2)dequeue, (3)print, (q)uit \n");
	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) 

		if(c == '1') {
		  printf("enqueue item: ");
			scanf("%d", &d);
      printf("new item: %d\n", d);
			en_queue(&q, &d, sizeof(int));
		
		} else if(c == '2') {
		  int* ip = (int*)de_queue(&q);
		  if(ip != NULL) {
  		  printf("dequeue item: %d\n", *ip);
  		  free(ip);	  
  		  
		  } else
  		  printf("queue empty\n");
  		  
		} else if(c == '3')
			print_queue(q);
	
	clear_queue(&q);
	return 0;
}
