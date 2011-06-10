/*see README for original credits */

#ifndef DLIST_H
#define DLIST_H

#include<stdbool.h>

typedef struct dlist {
  void* item;			/* data item */
  struct dlist* prev;		/* point to predecessor */
  struct dlist* next;		/* point to successor */
} dlist;

void clear_dlist(dlist* l);
void delete_dlist(dlist** l, const void* item, int sz);
bool empty_dlist(const dlist* l);
const void* head_dlist(const dlist* l);
void init_dlist(dlist** l);
void insert_dlist(dlist** l, const void* item, int sz);
void print_dlist(const dlist* l, void (*print_item)(const void* item));
const dlist* search_dlist(const dlist* l, const void* item, int sz);

#endif /* DLIST_H */
