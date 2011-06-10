/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dlist.h"

void clear_dlist(dlist* l) {
  while(l != NULL) {
    dlist* p = l;
    l = p->next;
    free(p->item);
    free(p);
  }
}

void delete_dlist(dlist** l, const void* item, int sz) {
	dlist* p = (dlist*)search_dlist(*l, item, sz);
	
	if(p == NULL) 
	  return;
	  
	dlist* pred = p->prev;
	if(pred == NULL)	/* splice out out dlist */
		*l = p->next;
	else
		pred->next = p->next;

	dlist* succ = p->next;
	if(succ != NULL)	
		succ->prev = p->prev;

  free(p->item);
  free(p);
}

bool empty_dlist(const dlist* l) {
  if(l == NULL) 
    return true;
    
  return false;
}

const void* head_dlist(const dlist* l) {
	return l->item;
}

void init_dlist(dlist** l) {
 *l = NULL;
}

void insert_dlist(dlist** l, const void* item, int sz) {
	dlist* p = malloc(sizeof(dlist));
  p->item = malloc(sz);  
	memcpy(p->item, item, sz);
	p->prev = NULL;
	
  if(*l != NULL) {
	  p->next = *l;
	  (*l)->prev = p;
  }	else  /* new list*/
	  p->next = NULL;
  
	*l = p;
}

const dlist* search_dlist(const dlist* l, const void* item, int sz) {
	if(l == NULL) 
	  return NULL;

  int cmp = memcmp(l->item, item, sz);
  if(!cmp) /*equal values*/
		return l;
	else
		return search_dlist(l->next, item, sz);
}

void print_dlist(const dlist* l, void (*print_item)(const void* item)) {
  while(l != NULL) {
    print_item(l->item);
    l = l->next;
  }
  printf("\n");
}
