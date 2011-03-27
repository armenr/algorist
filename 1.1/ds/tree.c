/*see README for original credits */

#include"tree.h"
#include<stdio.h>
#include<string.h>

void clear_tree(tree** t) {
  
  if(*t != NULL) {
  
    if((*t)->left != NULL)
      clear_tree(&((*t)->left));
      
    if((*t)->right != NULL)
      clear_tree(&((*t)->right));
      
    free((*t)->item);
    free(*t);
  }
}

tree* init_tree() {
  return NULL;
}

bool empty_tree(const tree* t) {
  if(t == NULL) 
    return true;
  return false;
}

const tree* search_tree(const tree* t, const item_type x, size_t n) {
  if(t == NULL) 
    return NULL;

  if(!memcmp(t->item, x, n)) /*equal values*/
    return t;
    
  if(memcmp(x, t->item, n) < 0) /* x < t->item */
    return search_tree(t->left, x, n);
  else
    return search_tree(t->right, x, n);
}

void insert_tree(tree** t, const item_type x, const tree* parent, size_t n) {
  tree* p; // temporary pointer 

  if(*t == NULL) {
    p = malloc(sizeof(tree));
    p->item = malloc(n);  
  	memcpy(p->item, x, n);
    p->left = p->right = NULL;
    p->parent = (tree*)parent;
    *t = p;
    return;
  }

  if(memcmp(x, (*t)->item, n) < 0) /* x < t->item */
    insert_tree(&((*t)->left), x, *t, n);
  else
    insert_tree(&((*t)->right), x, *t, n);
}

void print_tree(const tree* t, void (*print_item)(void*)) {
  if(t != NULL) {
    print_tree(t->left, print_item);
    print_item(t->item);
    print_tree(t->right, print_item);
  }
}

const tree* successor_descendant(const tree* t) {
  tree* succ; // successor pointer 

  if(t->right == NULL) 
    return NULL;

  succ = t->right;
  while(succ->left != NULL)
    succ = succ->left;
    
  return succ;
}

const tree* find_minimum(const tree* t) {
  tree* min; // pointer to minimum 

  if(t == NULL) return NULL;

  min = (tree* )t;
  while(min->left != NULL)
    min = min->left;
  return min;
}

const tree* predecessor_descendant(const tree* t) {
  tree* pred; // predecessor pointer 

  if(t->left == NULL) return NULL;

  pred = t->left;
  while(pred->right != NULL)
    pred = pred->right;
  return pred;
}

tree* delete_tree(tree* t, const item_type x, size_t n) {
  tree* d; // node with key to delete 
  tree* p; // node to be physically deleted 
  item_type new_key; // key to overwrite deleted key 
  tree* child; // d's only child, if any 

  d = (tree*)search_tree(t, x, n);

  if(d == NULL) 
    return t;

  if(d->parent == NULL) { // if d is the root 
  
    if((d->left == NULL) && (d->right == NULL)) { // no children 
      free(d->item);
      free(d);
      return NULL; // root-only tree
    }

    if(d->left != NULL) // find node to physically delete 
      p = (tree*)predecessor_descendant(d);
    else
      p = (tree*)successor_descendant(d);
      
  } else {  // not root 
  
    if((d->left == NULL) || (d->right == NULL)) {
      // d has <=1 child, so try to find non-null child 
      if(d->left != NULL)
        child = d->left;
      else
        child = d->right;

      if((d->parent)->left == d)  // fill null pointer 
        d->parent->left = child;
      else
        d->parent->right = child;
      
      if(child != NULL) child->parent = d->parent;

      free(d);
      return (t);
      
    } else 
      p = (tree*)successor_descendant(d); // p has 2 children 
  }

  new_key = p->item; // deal with simpler case of deletion 
  delete_tree(t, p->item, n);
  d->item = new_key;
  return t;
}

