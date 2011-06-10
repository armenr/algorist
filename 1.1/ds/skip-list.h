/*see README for original credits */

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#define PROBABILITY 0.5
#define MAX_LEVEL 7

/*
Each element in the list is stored in a node. The level of the node is chosen 
randomly when the node is created. Each SkipNode stores an array of next 
pointers as well as a key which represents the element stored in the node. 
For the purposes of this implementation the use of an int for the key is 
sufficient. In a more general implementation we could have used a void pointer 
to any arbitrary structure. (This would also require the skip list to store a 
function pointer to a comparison function).

The maximum level index is 6. C arrays are indexed starting at 0, therefore 
each node will have between one and seven next pointers. 
*/
typedef struct skipnode {
  void* key;  /*need to provide comparison function*/
	void* item; /* node data item */
  int level;
  struct skipnode** next; /* pointer to array of forward pointers */
  struct skipnode** prev; /* pointer to array of backward pointers */
} skipnode;

/*
A structure that represents a SkipSet is defined. It stores a pointer to a 
header node. The key stored in the header node is irrelevant and is never 
accessed. The current level of the set is also stored as this is needed by the 
insert, delete and search algorithms. 
*/
typedef struct {
  skipnode* header;
  int level;
	void* item; /* for copying auxilliary data for nodes */
	int item_sz;  
} skipset;

void add_skipset_item(skipset* ss, const void* item, int sz);
const skipnode* contains_skipnode(const skipset* ss, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2));
void insert_skipnode(skipset* ss, const void* key, int key_sz, 
  int (*compare_keys)(const void* key1, const void* key2));
void delete_skipnode(skipset* ss, const void* key,
  int (*compare_keys)(const void* key1, const void* key2));
void delete_skipnode2(skipset* ss, skipnode* node);
void clear_skipset(skipset* ss);
void init_skipset(skipset** ss);
void print_skipset(const skipset* ss, void (*print_item)(const void* item));

#endif /* SKIP_LIST_H */
