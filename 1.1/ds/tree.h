/*see README for original credits */

#ifndef TREE_H
#define TREE_H

#include"item.h"
#include<stdbool.h>
#include<stdlib.h>

typedef struct tree {
  item_type item; /* data item */
  struct tree* parent; /* pointer to parent */
  struct tree* left; /* pointer to left child */
  struct tree* right; /* pointer to right child */
} tree;

void clear_tree(tree** t);
tree* init_tree();
tree* delete_tree(tree* t, const item_type x, size_t n);
bool empty_tree(const tree* t);
const tree* find_minimum(const tree* t);
void insert_tree(tree** t, const item_type x, const tree* parent, size_t n);
void print_tree(const tree* t);
const tree* predecessor_descendant(const tree* t);
const tree* successor_descendant(const tree* t);
const tree* search_tree(const tree* t, const item_type x, size_t n);
 
#endif /* TREE_H */



