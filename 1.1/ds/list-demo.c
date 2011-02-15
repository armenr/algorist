/*see README for original credits */

#include"list.h"
#include<ctype.h>
#include<stdio.h>

static void print_list(const list* l) {
  while(l != NULL) {
    printf("%d ", *(int*)l->item);
    l = l->next;
  }
  printf("\n");
}

int main(void) {
	char c;			/* input character */
	int d;		/* input item */
	list *l;		/* list under construction */
	const list *tmp;		/* returned list from search */

	l = init_list();

  printf("list options: (p)rint, (s)earch, (i)nsert, (d)elete, (q) quit \n");
	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) {
		if(tolower(c) == 'p')
			print_list(l);
			
		else if(tolower(c) == 'i') {
		  printf("insert item: ");
			scanf("%d", &d);
      printf("new item: %d\n", d);
			insert_list(&l, &d, sizeof(int));
		}
		
		else if(tolower(c) == 's') {
		  printf("search for item: ");
			scanf("%d", &d);
			tmp = search_list(l, &d, sizeof(int));
			
			if(tmp == NULL) 
				printf("item %d not found\n", d);
			else
				printf("item %d found\n", d);
		}
		
		else if(tolower(c) == 'd') {
		  printf("delete item: ");
			scanf("%d", &d);
      tmp = search_list(l, &d, sizeof(int));

      if(tmp == NULL)
        printf("item to delete %d not found\n", d);
			else
				printf("item %d deleted\n", d);
  			delete_list(&l, &d, sizeof(int));
		}
	}
	
	clear_list(&l);
	return 0;
}
