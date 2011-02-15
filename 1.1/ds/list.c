/*see LICENSES file for original credits*/

#include"list.h"
#include<string.h>

void clear_list(list** l) {
  list* p;
  
  while(*l != NULL) {
    p = *l;
    *l = p->next;
    free(p->item);
    free(p);
  }
}

void delete_list(list** l, const item_type x, size_t n) {
	list* p;			/* item pointer */
	list* pred;			/* predecessor pointer */

	p = (list*)search_list(*l, x, n);
	if(p != NULL) {
		pred = (list*)predecessor_list(*l, x, n);
	
		if(pred == NULL)	/* splice out out list */
			*l = p->next;
		else
			pred->next = p->next;

    free(p->item);
    free(p);
	}
}

bool empty_list(const list* l) {
  if(l == NULL) 
    return true;
  return false;
}

item_type head_list(const list* l) {
	return l->item;
}

list* init_list(void) {
 return NULL;
}

void insert_list(list** l, const item_type x, size_t n) {
	list* p = malloc(sizeof(list));
  p->item = malloc(n);  
	memcpy(p->item, x, n);
	p->next = *l;
	*l = p;
}

const list* predecessor_list(const list* l, const item_type x, size_t n) {
  if((l == NULL) || (l->next == NULL)) {
/*    printf("Error: predecessor sought on null list.\n");*/
		return NULL;
	}

  if(!memcmp((l->next)->item, x, n)) /*equal values*/
    return l;
  else
    return predecessor_list(l->next, x, n);
}

const list* search_list(const list* l, const item_type x, size_t n) {
	if(l == NULL) 
	  return NULL;

  if(!memcmp(l->item, x, n)) /*equal values*/
		return l;
	else
		return search_list(l->next, x, n);
}
