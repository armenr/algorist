/*see README for original credits */

#ifndef TREE_H
#define TREE_H

#include<stdbool.h>

#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2

typedef struct tree {
  void* key;    /* id */
  int key_sz;
  void* item; /* data item */
  int item_sz;
  struct tree* parent; /* pointer to parent */
  struct tree* left; /* pointer to left child */
  struct tree* right; /* pointer to right child */
} tree;

void add_tree_item(tree* t, const void* item, int sz);
void clear_tree(tree** t);
void init_tree(tree** t);
void delete_tree(tree** t, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2));
bool empty_tree(const tree* t);
const tree* find_minimum(const tree* t);
tree* insert_tree(tree** t, const void* key, int key_sz, const tree* parent, 
  int (*compare_keys)(const void* key1, const void* key2));
void print_tree(const tree* t, int order, void (*print_item)(const void* item));
const tree* predecessor_descendant(const tree* t);
const tree* successor_descendant(const tree* t);
const tree* search_tree(const tree* t, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2));
 
#endif /* TREE_H */
