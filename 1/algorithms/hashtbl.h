/*see README for original credits */

#ifndef HASHTBL_H
#define HASHTBL_H

#define SUCCESS 0
#define FAILURE -1

#include<stdlib.h>

typedef size_t hash_size;

typedef struct hashnode_s {
	char *key;
	void *data;
	struct hashnode_s *next;
} hashnode_s;

typedef struct hashtbl {
	hash_size size;
	hashnode_s **nodes;
	hash_size (*hashfunc)(const char *);
} HASHTBL;


HASHTBL *hashtbl_create(hash_size size, hash_size (*hashfunc)(const char *));
void hashtbl_destroy(HASHTBL *hashtbl);
void *hashtbl_get(HASHTBL *hashtbl, const char *key);
int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data);
int hashtbl_remove(HASHTBL *hashtbl, const char *key);
int hashtbl_resize(HASHTBL *hashtbl, hash_size size);

#endif  /* HASHTBL_H */

