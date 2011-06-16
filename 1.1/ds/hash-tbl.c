/*see README for original credits */

#include<string.h>
#include<stdlib.h>
#include"hash-fn.h"
#include"hash-tbl.h"

static const hashnode* predecessor_node(const hashnode* h, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2));
static void delete_node(hashnode* node);

/*
hashtbl_create() sets up the initial structure of the hash table. The user 
specified size will be allocated and initialized to NULL. The user can also 
specify a hash function. If the hashfunc argument is NULL, a default hash 
function is used.

If an error occurred, NULL is returned. All other values in the returned 
hashtbl pointer should be released with hashtbl_destroy(). 
*/
void init_hashtbl(hashtbl** h, int size, 
  hash_t (*hashfunc)(const void* key)) {
  
	*h = malloc(sizeof(hashtbl)); 
	(*h)->nodes = calloc(size, sizeof(hashnode*));
	(*h)->size = size;
  (*h)->hashfunc = hashfunc;
}

/*
The hashtbl_destroy() walks through the linked lists for each possible hash 
value, and releases the elements. It also releases the nodes  array and the 
hashtbl. 
*/
void clear_hashtbl(hashtbl* h) {
	int n;
	
	for(n = 0; n < h->size; n++) {
  	hashnode* node = h->nodes[n];

		while(node != NULL) {
			hashnode* oldnode = node;
			node = node->next;
			delete_node(oldnode);
		}
	}
	
	free(h->nodes);
	free(h);
}

/*
To make sure the hash value is not bigger than size, the result of the user 
provided hash function is used modulo size.

To get the correct position in the nodes table, hash is used as an index.

We have to search the linked list to see if data with the same key has been 
inserted before, in which case we just replace the data member of the 
hashnode struct. 
*/
void insert_hashtbl(hashtbl* h, const void* key, int key_sz, 
  const void* item, int item_sz,
  int (*compare_keys)(const void* key1, const void* key2)) {
  
	hashnode* node = get_hashtbl((const hashtbl*)h, key, compare_keys);

  /*create new node if not found*/
  if(node == NULL) {
    node = malloc(sizeof(hashnode));

	  node->key = malloc(key_sz);
	  memcpy(node->key, key, key_sz);
	  
  	hash_t hash = h->hashfunc(key) % h->size;
	  node->next = h->nodes[hash];
	  h->nodes[hash] = node;

  } else
	  free(node->item);
	  
	node->item = malloc(item_sz);
	memcpy(node->item, item, item_sz);
}

/*
To remove an element from the hash table, we just search for it in the linked 
list for that hash value, and remove it if it is found. If it was not found, it 
is an error and -1 is returned. 
*/
void remove_hashtbl(hashtbl* h, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  
	hashnode* node = get_hashtbl((const hashtbl*)h, key, compare_keys);
	if(node == NULL)
	  return;

	hash_t hash = h->hashfunc(key) % h->size;
  hashnode* pred = (hashnode*)predecessor_node(node, key, compare_keys);

	if(pred == NULL)	
		h->nodes[hash] = node->next;
	else
		pred->next = node->next;

  delete_node(node);  
}

/*
Searching for an element is easy. We just search through the linked list for 
the corresponding hash value. NULL is returned if we didn't find it. 
*/
hashnode* get_hashtbl(const hashtbl* h, const void* key,
  int (*compare_keys)(const void* key1, const void* key2)) {
	int hash = h->hashfunc(key) % h->size;
	hashnode* node = h->nodes[hash];

	while(node != NULL) {
		if(!compare_keys(node->key, key)) 
		  return node;
		node = node->next;
	}

	return NULL;
}

/*
The number of elements in a hash table is not always known when creating the 
table. If the number of elements grows too large, it will seriously reduce the 
performance of most hash table operations. If the number of elements are 
reduced, the hash table will waste memory. That is why we provide a function 
for resizing the table.

Resizing a hash table is not as easy as a realloc(). All hash values must be 
recalculated and each element must be inserted into its new position.

We create a temporary hashtbl object (newtbl) to be used while building the new 
hashes. This allows us to reuse hashtbl_inset() and hashtbl_remove(), when 
moving the elements to the new table. After that, we can just free the old table
 and copy the elements from newtbl to hashtbl. 
 */
void resize_hashtbl(hashtbl* h, int size) {
  if(size < 1)
    return;
    
	hashnode** nodes = calloc(size, sizeof(hashnode*));
	int n;

	for(n = 0; n < h->size; n++) 
    if(h->nodes[n] != NULL) {
    	int hash = h->hashfunc(h->nodes[n]->key) % size;
  	  nodes[hash] = h->nodes[n];
    } 	  

	free(h->nodes);
	h->size = size;
	h->nodes = nodes;
}

static const hashnode* predecessor_node(const hashnode* h, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  if((h == NULL) || (h->next == NULL)) 
		return NULL;

  if(!compare_keys(h->next->key, key)) 
    return h;
  else
    return predecessor_node(h->next, key, compare_keys);
}

static void delete_node(hashnode* node) {
	free(node->key);
	free(node->item);
	free(node);
}
