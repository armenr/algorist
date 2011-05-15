/*see README for original credits */

#ifndef HASHTBL_H
#define HASHTBL_H

#include"hash-fn.h"
#include<stdlib.h>

typedef struct hashnode {
	void* key;
	void* item;
	struct hashnode* next;
} hashnode;

typedef struct hashtbl {
	int size;
	hashnode** nodes;
	hash_t (*hashfunc)(const void* key);
} hashtbl;


void init_hashtbl(hashtbl** h, size_t size, 
  hash_t (*hashfunc)(const void* key));
void destroy_hashtbl(hashtbl* hashtbl);
hashnode* get_hashtbl(const hashtbl* h, const void* key,
  size_t (*compare_keys)(const void* key1, const void* key2));
void insert_hashtbl(hashtbl* h, const void* key, size_t key_sz, 
  const void* data, size_t item_sz,
  size_t (*compare_keys)(const void* key1, const void* key2));
void remove_hashtbl(hashtbl* h, const void* key,
  size_t (*compare_keys)(const void* key1, const void* key2));
void resize_hashtbl(hashtbl* h, size_t size);

#endif  /* HASHTBL_H */

