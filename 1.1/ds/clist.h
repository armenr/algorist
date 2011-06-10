/*see README for original credits */

#ifndef CLIST_H
#define CLIST_H

#include<stdbool.h>

typedef struct clist_item {
  void* item;			/* data item */
  struct clist_item* prev;		/* point to predecessor */
  struct clist_item* next;		/* point to successor */
} clist_item;

typedef struct clist {
  clist_item* tail; /* pointer to last element*/
  clist_item* data;
  int count;  /* data count*/
} clist;

void clear_clist(clist* l);
void delete_clist(clist* l, const void* item, int sz);
bool empty_clist(const clist* l);
const void* head_clist(const clist* l);
void init_clist(clist* l);
void insert_clist(clist* l, const void* item, int sz);
void print_clist(const clist* l, void (*print_item)(const void* item));
const clist_item* search_clist(const clist* l, const void* item, 
  int sz);

#endif /* CLIST_H */
