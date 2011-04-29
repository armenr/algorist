/*see README for original credits */

#ifndef TREE_H
#define TREE_H

#include<stdbool.h>

#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2

typedef struct tree {
  int node;    /* id */
  void* item; /* data item */
  struct tree* parent; /* pointer to parent */
  struct tree* left; /* pointer to left child */
  struct tree* right; /* pointer to right child */
} tree;

void clear_tree(tree** t);
void init_tree(tree** t);
void delete_tree(tree** t, int node);
bool empty_tree(const tree* t);
const tree* find_minimum(const tree* t);
void insert_tree(tree** t, int node, const void* item, const tree* parent, 
  int sz);
void print_tree(const tree* t, int order, void (*print_item)(void* item));
const tree* predecessor_descendant(const tree* t);
const tree* successor_descendant(const tree* t);
const tree* search_tree(const tree* t, int node);
 
#endif /* TREE_H */
