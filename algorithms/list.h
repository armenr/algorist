/*see README for original credits */

#ifndef LIST_H
#define LIST_H

#include "item.h"

typedef struct list {
  item_type item;			/* data item */
  struct list *next;		/* point to successor */
} list;

list *init_list();
bool empty_list(const list *l);
const list *search_list(const list *l, item_type x);
const list *predecessor_list(const list *l, item_type x);
void print_list(const list *l);
void insert_list(list **l, item_type x);
void delete_list(list **l, item_type x);

#endif /* LIST_H */






