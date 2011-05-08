/*see README for original credits */

#ifndef LIST_H
#define LIST_H

#include<stdbool.h>
#include<stdlib.h>

typedef struct list {
  void* item;			/* data item */
  struct list* next;		/* point to successor */
} list;

void clear_list(list** l);
void delete_list(list** l, const void* item, size_t sz);
bool empty_list(const list* l);
void* head_list(const list* l);
void init_list(list** l);
void insert_list(list** l, const void* item, size_t sz);
const list* predecessor_list(const list* l, const void* item, size_t sz);
void print_list(const list* l, void (*print_item)(const void* item));
const list* search_list(const list* l, const void* item, size_t sz);

#endif /* LIST_H */






