/*see README for original credits */

#include "bool.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list *init_list() {
 return NULL;
}

bool empty_list(const list *l) {
  if(l == NULL) return TRUE;
  else return FALSE;
}

const list *search_list(const list *l, item_type x) {
	if(l == NULL) return NULL;

	if(l->item == x)
		return l;
	else
		return search_list(l->next, x);
}

const list *predecessor_list(const list *l, item_type x) {
  if((l == NULL) || (l->next == NULL)) {
    printf("Error: predecessor sought on null list.\n");
		return NULL;
	}

  if((l->next)->item == x)
    return l;
  else
    return predecessor_list(l->next, x);
}

void print_list(const list *l) {
  while(l != NULL) {
    printf("%d ", l->item);
    l = l->next;
  }

  printf("\n");
}

void insert_list(list **l, item_type x) {
	list *p;			/* temporary pointer */

	p = malloc( sizeof(list) );
	p->item = x;
	p->next = *l;
	*l = p;
}

void delete_list(list **l, item_type x) {
	list *p;			/* item pointer */
	list *pred;			/* predecessor pointer */

	p = (list *)search_list(*l, x);
	if(p != NULL) {
		pred = (list *)predecessor_list(*l, x);
		if(pred == NULL)	/* splice out out list */
			*l = p->next;
		else
			pred->next = p->next;

		free(p);		/* free memory used by node */
	}
}

