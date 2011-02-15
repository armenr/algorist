/*see README for original credits */

#include"tree.h"
#include<ctype.h>
#include<stdio.h>

int main(void) {
  char c; /* input character */
  int d; /* input item */
  tree* t; /* tree under construction */
  const tree* tmp; /* returned tree from search */

  t = init_tree();
  printf("tree options: (p)rint, (s)earch, (i)nsert, (d)elete (q)uit\n");

	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) {
  
    if(tolower(c) == 'p') {
      print_tree(t);
      printf("\n");
    }
  
    if(tolower(c) == 'i') {
		  printf("insert item: ");
      scanf("%d", &d);
      printf("new item: %d\n", d);
      insert_tree(&t, &d, NULL, sizeof(int));
    }

    if(tolower(c) == 's') {
		  printf("search for item: ");
      scanf("%d", &d);
      tmp = search_tree(t, &d, sizeof(int));
      
      if(tmp == NULL)
        printf("item %d not found\n", d);
      else
        printf("item %d found\n", d);
    }
  
    if(tolower(c) == 'd') {
		  printf("delete item: ");
      scanf("%d", &d);
      printf(" deleting item %d\n", d);
      t = delete_tree(t, &d, sizeof(int));
      print_tree(t);
      printf("\n");
    }
  }
  
  clear_tree(&t);
  return 0;
}
