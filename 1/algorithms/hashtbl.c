/*see README for original credits */

#include "hashtbl.h"
#include <string.h>
#include <stdio.h>

static char *myStrDup(const char *s) {
	char *d;
	if(!(d = malloc(strlen(s)+1))) 
	  return NULL;
	  
	strcpy(d, s);
	return d;
}

/*
def_hashfunc() is the default used by hashtbl_create() when the user didn't 
specify one. This is a simple/naive hash function which adds the key's ASCII 
char values. It will probably generate lots of collisions on large hash tables.
*/
static hash_size def_hashfunc(const char *key) {
	hash_size hash = 0;
	
	while(*key) 
	  hash += (unsigned char) *key++;

	return hash;
}

/*
hashtbl_create() sets up the initial structure of the hash table. The user 
specified size will be allocated and initialized to NULL. The user can also 
specify a hash function. If the hashfunc argument is NULL, a default hash 
function is used.

If an error occurred, NULL is returned. All other values in the returned 
HASHTBL pointer should be released with hashtbl_destroy(). 
*/
HASHTBL *hashtbl_create(hash_size size, hash_size (*hashfunc)(const char *)) {
	HASHTBL *hashtbl;

	if(!(hashtbl = malloc(sizeof(HASHTBL)))) 
	  return NULL;

	if(!(hashtbl->nodes = calloc(size, sizeof(hashnode_s*)))) {
		free(hashtbl);
		return NULL;
	}

	hashtbl->size = size;

	if(hashfunc) 
	  hashtbl->hashfunc = hashfunc;
	else 
	  hashtbl->hashfunc = def_hashfunc;

	return hashtbl;
}

/*
The hashtbl_destroy() walks through the linked lists for each possible hash 
value, and releases the elements. It also releases the nodes  array and the 
HASHTBL. 
*/
void hashtbl_destroy(HASHTBL *hashtbl) {
	hash_size n;
	hashnode_s *node, *oldnode;
	
	for(n = 0; n<hashtbl->size; ++n) {
		node = hashtbl->nodes[n];

		while(node) {
			free(node->key);
			oldnode = node;
			node = node->next;
			free(oldnode);
		}

	}
	
	free(hashtbl->nodes);
	free(hashtbl);
}

/*
To make sure the hash value is not bigger than size, the result of the user 
provided hash function is used modulo size.

To get the correct position in the nodes table, hash is used as an index.

We have to search the linked list to see if data with the same key has beeen 
inserted before, in which case we just replace the data member of the 
hashnode_s struct. 
*/
int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data) {
	hashnode_s *node;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

/*	fprintf(stderr, "hashtbl_insert() key = %s, hash = %d, data = %s\n", key, hash, (char*)data);*/

	node = hashtbl->nodes[hash];
	while(node) {
		if(!strcmp(node->key, key)) {
			node->data = data;
			return SUCCESS;
		}
		node = node->next;
	}

	if(!(node = malloc(sizeof(hashnode_s)))) 
	  return FAILURE;
	  
	if(!(node->key = myStrDup(key))) {
		free(node);
		return FAILURE;
	}
	
	node->data = data;
	node->next = hashtbl->nodes[hash];
	hashtbl->nodes[hash] = node;

	return SUCCESS;
}

/*
To remove an element from the hash table, we just search for it in the linked 
list for that hash value, and remove it if it is found. If it was not found, it 
is an error and -1 is returned. 
*/
int hashtbl_remove(HASHTBL *hashtbl, const char *key) {
	hashnode_s *node, *prevnode = NULL;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

	node = hashtbl->nodes[hash];
	
	while(node) {
	
		if(!strcmp(node->key, key)) {
			free(node->key);
	
			if(prevnode) 
			  prevnode->next = node->next;
			else 
			  hashtbl->nodes[hash] = node->next;
			free(node);
	
			return SUCCESS;
		}
	
		prevnode = node;
		node = node->next;
	}

	return FAILURE;
}

/*
Searching for an element is easy. We just search through the linked list for 
the corresponding hash value. NULL is returned if we didn't find it. 
*/
void *hashtbl_get(HASHTBL *hashtbl, const char *key) {
	hashnode_s *node;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

/*	fprintf(stderr, "hashtbl_get() key = %s, hash = %d\n", key, hash);*/

	node = hashtbl->nodes[hash];
	while(node) {
		if(!strcmp(node->key, key)) 
		  return node->data;
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

We create a temporary HASHTBL object (newtbl) to be used while building the new 
hashes. This allows us to reuse hashtbl_inset() and hashtbl_remove(), when 
moving the elements to the new table. After that, we can just free the old table
 and copy the elements from newtbl to hashtbl. 
 */
int hashtbl_resize(HASHTBL *hashtbl, hash_size size) {
	HASHTBL newtbl;
	hash_size n;
	hashnode_s *node,*next;

	newtbl.size = size;
	newtbl.hashfunc = hashtbl->hashfunc;

	if(!(newtbl.nodes = calloc(size, sizeof(struct hashnode_s*)))) 
	  return FAILURE;

	for(n = 0; n<hashtbl->size; ++n) 
		for(node = hashtbl->nodes[n]; node; node = next) {
			next  =  node->next;
			hashtbl_insert(&newtbl, node->key, node->data);
			hashtbl_remove(hashtbl, node->key);
		}

	free(hashtbl->nodes);
	hashtbl->size = newtbl.size;
	hashtbl->nodes = newtbl.nodes;

	return SUCCESS;
}

