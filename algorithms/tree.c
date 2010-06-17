/*see README for original credits */

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

tree *parent; /* last node visited */

tree *init_tree() {
  return NULL;
}

bool empty_tree(const tree *t) {
  if(t == NULL) return TRUE;
  else return FALSE;
}

const tree *search_tree(const tree *l, item_type x) {
  if(l == NULL) return NULL;

  if(l->item == x) return l;

  if(x < l->item)
    return search_tree(l->left, x);
  else
    return search_tree(l->right, x);
}

void insert_tree(tree **l, item_type x, const tree *parent) {
  tree *p; /* temporary pointer */

  if(*l == NULL) {
    p = malloc(sizeof (tree));
    p->item = x;
    p->left = p->right = NULL;
    p->parent = (tree *)parent;
    *l = p;
    return;
  }

  if(x < (*l)->item)
    insert_tree(&((*l)->left), x, *l);
  else
    insert_tree(&((*l)->right), x, *l);
}

void print_tree(const tree *l) {
  if(l != NULL) {
    print_tree(l->left);
    printf("%d ", l->item);
    print_tree(l->right);
  }
}

const tree *successor_descendant(const tree *t) {
  tree *succ; /* successor pointer */

  if(t->right == NULL) return NULL;

  succ = t->right;
  while(succ->left != NULL)
    succ = succ->left;
    
  return succ;
}

const tree *find_minimum(const tree *t) {
  tree *min; /* pointer to minimum */

  if(t == NULL) return NULL;

  min = (tree *)t;
  while(min->left != NULL)
    min = min->left;
  return min;
}

const tree *predecessor_descendant(const tree *t) {
  tree *pred; /* predecessor pointer */

  if(t->left == NULL) return NULL;

  pred = t->left;
  while(pred->right != NULL)
    pred = pred->right;
  return pred;
}

tree *delete_tree(tree *t, item_type x) {
  tree *d; /* node with key to delete */
  tree *p; /* node to be physically deleted */
  item_type new_key; /* key to overwrite deleted key */
  tree *child; /* d's only child, if any */

  d = (tree *)search_tree(t, x);

  if(d == NULL) {
    printf("Warning: key to be deleted %d is not in tree.\n", x);
    return t;
  }

  if(d->parent == NULL) { /* if d is the root */
  
    if((d->left == NULL) && (d->right == NULL)) { /* no children */
      free(d);
      return NULL; /* root-only tree */
    }

    if(d->left != NULL) /* find node to physically delete */
      p = (tree *)predecessor_descendant(d);
    else
      p = (tree *)successor_descendant(d);
      
  } else {  /* not root */
  
    if((d->left == NULL) || (d->right == NULL)) {
      /* d has <=1 child, so try to find non-null child */
      if(d->left != NULL)
        child = d->left;
      else
        child = d->right;

      if((d->parent)->left == d)  /* fill null pointer */
        d->parent->left = child;
      else
        d->parent->right = child;
      
      if(child != NULL) child->parent = d->parent;

      free(d);
      return (t);
      
    } else 
      p = (tree *)successor_descendant(d); /* p has 2 children */
  }

  new_key = p->item; /* deal with simpler case of deletion */
  delete_tree(t, p->item);
  d->item = new_key;
  return t;
}

