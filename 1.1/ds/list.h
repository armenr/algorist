/*see LICENSES file for original credits*/

#ifndef LIST_H
#define LIST_H

#include"item.h"
#include<stdbool.h>
#include<stdlib.h>

typedef struct list {
  item_type item;			/* data item */
  struct list* next;		/* point to successor */
} list;

void clear_list(list** l);
void delete_list(list** l, const item_type x, size_t n);
bool empty_list(const list* l);
item_type head_list(const list* l);
list* init_list(void);
void insert_list(list** l, const item_type x, size_t n);
const list* predecessor_list(const list* l, const item_type x, size_t n);
void print_list(const list* l, void (*print_item)(void*));
const list* search_list(const list* l, const item_type x, size_t n);

#endif /* LIST_H */






