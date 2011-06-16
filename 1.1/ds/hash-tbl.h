/*see README for original credits */

#ifndef HASHTBL_H
#define HASHTBL_H

#include"hash-fn.h"

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


void init_hashtbl(hashtbl** h, int size, 
  hash_t (*hashfunc)(const void* key));
void clear_hashtbl(hashtbl* hashtbl);
hashnode* get_hashtbl(const hashtbl* h, const void* key,
  int (*compare_keys)(const void* key1, const void* key2));
void insert_hashtbl(hashtbl* h, const void* key, int key_sz, 
  const void* data, int item_sz,
  int (*compare_keys)(const void* key1, const void* key2));
void remove_hashtbl(hashtbl* h, const void* key,
  int (*compare_keys)(const void* key1, const void* key2));
void resize_hashtbl(hashtbl* h, int size);

#endif  /* HASHTBL_H */

