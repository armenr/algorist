  /*see README for original credits */

#include<string.h>
#include<stdlib.h>
#include"set-union2.h"

void init_set_union2(forest_node** node, const void* item, int sz) {
  forest_node* n = malloc(sizeof(forest_node));

  n->item = malloc(sz);
  memcpy(n->item, item, sz);
  n->parent = NULL;
  n->rank = 0;

  (*node) = n;
}

/*
If rank(s) ≠ rank(t), then rank(Union(s,t)) is the larger of rank(s) and rank(t). 
In this case, we attach the tree with smaller rank to the root of the tree with 
larger rank.

If rank(s) = rank(t), then rank(Union(s,t)) = rank(s) + 1 = rank(t) + 1. 
*/
void merge_set_union2(forest_node* node1, forest_node* node2) {
  if(node1->rank > node2->rank) 
    node2->parent = node1;

  else if(node2->rank > node1->rank) 
    node1->parent = node2;

  else { /* they are equal */
    node2->parent = node1;
    node1->rank++;
  }
}

/*
This technique, known as the union find heuristic, guarantees logarithmic 
height, which is reasonably efficient. But we can do even better by using a 
technique called path compression. The idea is that all nodes we visit when 
traversing up from a node to the root are in the same tree, and so they might 
as well be pointing directly at the root. We make a second pass and update their 
parent pointers, speeding up future searches involving these nodes dramatically:
*/
/*side effect in search*/
const forest_node* find_set_union2(forest_node* node) {
  /* find the root */
  forest_node* root = node;

  while(root->parent != NULL) 
    root = root->parent;

  /* update the parent pointers */
  forest_node* tmp;

  while(node->parent != NULL) {
    tmp = node->parent;
    node->parent = root;
    node = tmp;
  }
  
  return root;
}
