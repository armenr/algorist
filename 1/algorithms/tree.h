/*see README for original credits */

#ifndef TREE_H
#define TREE_H

#include "bool.h"
#include "item.h"

typedef struct tree {
  item_type item; /* data item */
  struct tree *parent; /* pointer to parent */
  struct tree *left; /* pointer to left child */
  struct tree *right; /* pointer to right child */
} tree;

tree *parent; /* last node visited */

tree *init_tree();
bool empty_tree(const tree *t);
const tree *search_tree(const tree *l, item_type x);
void insert_tree(tree **l, item_type x, const tree *parent);
void print_tree(const tree *l);
const tree *successor_descendant(const tree *t);
const tree *find_minimum(const tree *t);
const tree *predecessor_descendant(const tree *t);
tree *delete_tree(tree *t, item_type x);
 
#endif /* TREE_H */



