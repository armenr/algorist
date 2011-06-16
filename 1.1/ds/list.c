/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"

void clear_list(list* l) {
  while(l != NULL) {
    list* p = l;
    l = p->next;
    free(p->item);
    free(p);
  }
}

void delete_list(list** l, const void* item, int sz) {
	list* p = (list*)search_list(*l, item, sz);
	
	if(p == NULL) 
	  return;
	  
	list* pred = (list*)predecessor_list(*l, item, sz);

	if(pred == NULL)	/* splice out out list */
		*l = p->next;
	else
		pred->next = p->next;

  free(p->item);
  free(p);
}

bool empty_list(const list* l) {
  if(l == NULL) 
    return true;
    
  return false;
}

const void* head_list(const list* l) {
	return l->item;
}

void init_list(list** l) {
 *l = NULL;
}

void insert_list(list** l, const void* item, int sz) {
	list* p = malloc(sizeof(list));
  p->item = malloc(sz);  
	memcpy(p->item, item, sz);
	p->next = *l;
	*l = p;
}

const list* predecessor_list(const list* l, const void* item, int sz) {
  if((l == NULL) || (l->next == NULL)) 
		return NULL;

  int cmp = memcmp((l->next)->item, item, sz);
  if(!cmp) /*equal values*/
    return l;
  else
    return predecessor_list(l->next, item, sz);
}

const list* search_list(const list* l, const void* item, int sz) {
	if(l == NULL) 
	  return NULL;

  int cmp = memcmp(l->item, item, sz);
  if(!cmp) /*equal values*/
		return l;
	else
		return search_list(l->next, item, sz);
}

void print_list(const list* l, void (*print_item)(const void* item)) {
  while(l != NULL) {
    print_item(l->item);
    l = l->next;
  }
  printf("\n");
}
