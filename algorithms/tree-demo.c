/*see README for original credits */

#include "item.h"
#include "tree.h"
#include <stdio.h>

int main(void) {
  char c; /* input character */
  item_type d; /* input item */
  tree *l; /* tree under construction */
  const tree *tmp; /* returned tree from search */

  l = init_tree();
  printf("tree options: (p)rint, (s)earch, (i)nsert, (d)elete \n");

  while(scanf("%c", &c) != EOF) {
  
    if(tolower(c) == 'p') {
      print_tree(l);
      printf("\n");
    }
  
    if(tolower(c) == 'i') {
		  printf("insert item: ");
      scanf("%d", &d);
      printf("new item: %d\n", d);
      insert_tree(&l, d, NULL);
    }

    if(tolower(c) == 's') {
		  printf("search for item: ");
      scanf("%d", &d);
      tmp = search_tree(l, d);
      
      if(tmp == NULL)
        printf("item %d not found\n", d);
      else
        printf("item %d found\n", d);
    }
  
    if(tolower(c) == 'd') {
		  printf("delete item: ");
      scanf("%d", &d);
      printf(" deleting item %d\n", d);
      l = delete_tree(l, d);
      print_tree(l);
      printf("\n");
    }
  }
  
  return 0;
}
