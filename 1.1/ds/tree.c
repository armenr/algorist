/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"tree.h"

static tree** del_search(tree** t, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2));
static tree* delete_root(tree** t);
static void delete_node(tree** n);
static void repoint_child(tree** t);
static void update_node(tree** t, tree* p, 
  int (*compare_keys)(const void* key1, const void* key2));

void add_tree_item(tree* t, const void* item, int sz) {
  if(t->item != NULL) {
    free(t->item);
    t->item = NULL;
  }
    
  if(item != NULL) {
    t->item = malloc(sz);  
    t->item_sz = sz;
	  memcpy(t->item, item, sz);
  }
}

void clear_tree(tree** t) { 
  if(*t == NULL) 
    return;
  
  if((*t)->left != NULL)
    clear_tree(&((*t)->left));
    
  if((*t)->right != NULL)
    clear_tree(&((*t)->right));

  delete_node(t);
}

void init_tree(tree** t) {
  *t = NULL;
}

bool empty_tree(const tree* t) {
  if(t == NULL) 
    return true;
    
  return false;
}

const tree* search_tree(const tree* t, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  if(t == NULL) 
    return NULL;

  int cmp = compare_keys(key, t->key);
  if(cmp == 0)  
    return t;
    
  if(cmp < 0) 
    return search_tree(t->left, key, compare_keys);
  else
    return search_tree(t->right, key, compare_keys);
}

tree* insert_tree(tree** t, const void* key, int key_sz, const tree* parent, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  tree* p; 

  if(*t == NULL) {
    p = malloc(sizeof(tree));
    
    p->key = malloc(key_sz);
    p->key_sz = key_sz;
  	memcpy(p->key, key, key_sz);
    
    p->item = NULL;  

    p->left = p->right = NULL;
    p->parent = (tree*)parent;
    
    *t = p;
    return *t;
  }

  int cmp = compare_keys(key, (*t)->key);
  if(cmp < 0) 
    return insert_tree(&((*t)->left), key, key_sz, *t, compare_keys);
  else
    return insert_tree(&((*t)->right), key, key_sz, *t, compare_keys);
}

void print_tree(const tree* t, tree_order order, 
  void (*print_item)(const void* item)) {
  if(t == NULL) 
    return;
    
  switch(order) {
    case PRE_ORDER:
      print_item(t);
      print_tree(t->left, PRE_ORDER, print_item);
      print_tree(t->right, PRE_ORDER, print_item);
      break;
      
    case IN_ORDER:
      print_tree(t->left, IN_ORDER, print_item);
      print_item(t);
      print_tree(t->right, IN_ORDER, print_item);
      break;
      
    case POST_ORDER:
      print_tree(t->left, POST_ORDER, print_item);
      print_tree(t->right, POST_ORDER, print_item);
      print_item(t);
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

void delete_tree(tree** t, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  /* key with key to delete */
  tree** d = del_search(t, key, compare_keys);
  if(d == NULL) /*not found*/ 
    return;

  tree* p = NULL; /*key to be physically deleted */

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
    update_node(d, p, compare_keys);    
}

static tree** del_search(tree** t, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  if(*t == NULL) 
    return NULL;

  int cmp = compare_keys(key, (*t)->key);
  if(cmp == 0)  
    return t;
    
  if(cmp < 0) 
    return del_search(&((*t)->left), key, compare_keys);
  else
    return del_search(&((*t)->right), key, compare_keys);
}

static void delete_node(tree** n) {
  free((*n)->key);
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
  if((*t)->left != NULL) /*find key to physically delete */
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
  
  if(child != NULL) { /*replace key with child*/
    child->parent = (*t)->parent;
     
    if((*t)->parent->left == *t)  
      (*t)->parent->left = child;
    else
      (*t)->parent->right = child;

    delete_node(&tmp);
    
  } else   /*no children*/
    delete_node(t);
}

static void update_node(tree** t, tree* p, 
   int (*compare_keys)(const void* key1, const void* key2)) {

 /*overwrite existing node item with new node item */
  add_tree_item(*t, p->item, p->item_sz);
  
  /*copy node key then delete old key*/
  void* key = malloc(p->key_sz);
  int key_sz = p->key_sz;
  memcpy(key, p->key, p->key_sz);

  delete_tree(t, p->key, compare_keys);  /*delete before re-assignment of key*/

  free((*t)->key); 
  (*t)->key = key;  
  (*t)->key_sz = key_sz;  
}
