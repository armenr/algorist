/*see README for original credits */

#include"tree.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static tree** del_search(tree** t, int node);
static tree* delete_root(tree** t);
static void delete_node(tree** n);
static void repoint_child(tree** t);
static void update_node(tree** t, tree* p);

void clear_tree(tree** t) { 
  if(*t == NULL) 
    return;
  
  if((*t)->left != NULL)
    clear_tree(&((*t)->left));
    
  if((*t)->right != NULL)
    clear_tree(&((*t)->right));

  free((*t)->item);
  free(*t);
}

void init_tree(tree** t) {
  *t = NULL;
}

bool empty_tree(const tree* t) {
  if(t == NULL) 
    return true;
    
  return false;
}

const tree* search_tree(const tree* t, int node) {
  if(t == NULL) 
    return NULL;

  if(node == t->node)  
    return t;
    
  if(node < t->node) 
    return search_tree(t->left, node);
  else
    return search_tree(t->right, node);
}

void insert_tree(tree** t, int node, const void* item, const tree* parent, 
  int sz) {
  tree* p; 

  if(*t == NULL) {
    p = malloc(sizeof(tree));
    p->node = node;
    p->item = malloc(sz);  
  	memcpy(p->item, item, sz);
    p->left = p->right = NULL;
    p->parent = (tree*)parent;
    *t = p;
    return;
  }

  if(node < (*t)->node) /* x < t->item */
    insert_tree(&((*t)->left), node, item, *t, sz);
  else
    insert_tree(&((*t)->right), node, item, *t, sz);
}

void print_tree(const tree* t, int order, void (*print_item)(void* item)) {
  if(t == NULL) 
    return;
    
  switch(order) {
    case PRE_ORDER:
      print_item(t->item);
      print_tree(t->left, PRE_ORDER, print_item);
      print_tree(t->right, PRE_ORDER, print_item);
      break;
      
    case IN_ORDER:
      print_tree(t->left, IN_ORDER, print_item);
      print_item(t->item);
      print_tree(t->right, IN_ORDER, print_item);
      break;
      
    case POST_ORDER:
      print_tree(t->left, POST_ORDER, print_item);
      print_tree(t->right, POST_ORDER, print_item);
      print_item(t->item);
      break;

    default:
      break;      
  }    
}

const tree* find_minimum(const tree* t) {
  if(t == NULL) 
    return NULL;

  tree* min = (tree*)t; 
  while(min->left != NULL)
    min = min->left;
    
  return min;
}

const tree* predecessor_descendant(const tree* t) {
  if(t->left == NULL) 
    return NULL;

  tree* pred = t->left;  
  while(pred->right != NULL)
    pred = pred->right;
    
  return pred;
}

const tree* successor_descendant(const tree* t) {
  if(t->right == NULL) 
    return NULL;

  tree* succ = t->right;  
  while(succ->left != NULL)
    succ = succ->left;
    
  return succ;
}

void delete_tree(tree** t, int node) {
  /* node with key to delete */
  tree** d = del_search(t, node);
  if(d == NULL) /*not found*/ 
    return;

  tree* p = NULL; /*node to be physically deleted */

  if((*d)->parent == NULL)  /*d is the root */
    p = delete_root(d); /*fiiled if root has at least 1 child*/
  
  else {  /* not root */
    if(((*d)->left == NULL) || ((*d)->right == NULL))  /*0 or 1 children*/
      repoint_child(d);
    else  /*2 children*/
      p = (tree*)successor_descendant(*d); 
  }

  /*move child up to replace parent and delete child*/
  if(p != NULL)  
    update_node(d, p);    
}

static tree** del_search(tree** t, int node) {
  if(*t == NULL) 
    return NULL;

  if(node == (*t)->node)  
    return t;
    
  if(node < (*t)->node) 
    return del_search(&((*t)->left), node);
  else
    return del_search(&((*t)->right), node);
}

static void delete_node(tree** n) {
  free((*n)->item);
  free(*n);
  *n = NULL;
}

static tree* delete_root(tree** t) {
  if(((*t)->left == NULL) && ((*t)->right == NULL)) { /*no children */
    delete_node(t);
    return NULL;
  }
  
  /*has at least one child    */
  if((*t)->left != NULL) /*find node to physically delete */
    return (tree*)predecessor_descendant(*t);
  else
    return (tree*)successor_descendant(*t);
}

static void repoint_child(tree** t) {
  tree* child = NULL; /* d's only child, if any */

  /* d has <=1 child, so try to find non-null child */
  if((*t)->left != NULL)
    child = (*t)->left;
  else if((*t)->right != NULL)
    child = (*t)->right;

  tree* tmp = *t; /*delete later*/
  
  if(child != NULL) { /*replace node with child*/
    child->parent = (*t)->parent;
     
    if((*t)->parent->left == *t)  
      (*t)->parent->left = child;
    else
      (*t)->parent->right = child;

    delete_node(&tmp);
    
  } else   /*no children*/
    delete_node(t);
}

static void update_node(tree** t, tree* p) {
  /*overwrite existing node with new node  */
  free((*t)->item); /*release existing data*/
  int sz = sizeof(p->item); /*copy node's data*/
  (*t)->item = malloc(sz);
  memcpy((*t)->item, p->item, sz);
  
  int n = p->node;
  delete_tree(t, p->node);  /*delete before re-assignment of node*/
  (*t)->node = n;  
}
