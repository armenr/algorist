/*see README for original credits */

#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include"skip-list.h"

#define HEADER -1

static void clear_skipset_item(skipset* ss);
static skipnode* make_skipnode(skipset* ss, int level, const void* key, 
  int key_sz);
static void insert_node(skipnode* h, skipnode* s, int l,
  int (*compare_keys)(const void* key1, const void* key2));
static void delete_node(skipset* ss, skipnode* s);
static void release_node(skipnode* s);

static float frand(void);
static int random_level(void);

void add_skipset_item(skipset* ss, const void* item, int sz) {
  clear_skipset_item(ss);
  ss->item = malloc(sz);
  memcpy(ss->item, item, sz);
  ss->item_sz = sz;
}

void clear_skipset(skipset* ss ) {
  /*clear skiplists  */
  skipnode* s = ss->header->next[0];

  while(s != NULL) {
    skipnode* tmp = s;
    s = s->next[0];
    release_node(tmp);
  }

  release_node(ss->header);
  clear_skipset_item(ss);
  free(ss);
}

/*To create a SkipSet we must first allocate memory for the structure and then */
/*allocate memory for the header node. The initial level of the set is 0 because */
/*C arrays are indexed starting at 0. */
void init_skipset(skipset** ss ) {
  *ss = malloc(sizeof(skipset));
  (*ss)->item = NULL;
  (*ss)->level = 0;
  int i = HEADER;
  (*ss)->header = make_skipnode((*ss), MAX_LEVEL, &i, sizeof(int));
}

/*Before getting to the algorithms for insert, delete and search, let us first */
/*start off with a function that will print the contents of a skip set to the */
/*console. This function simply traverses the level 0 pointers and visits every */
/*node while printing out the keys. */
void print_skipset(const skipset* ss, void (*print_item)(const void* item)) {
  int i;

  for(i = ss->level; i >= 0; i--) {
    printf("level %d:\n{", i);
    skipnode* s = ss->header->next[i];
    
    while(s != NULL) {
      print_item(s);
      s = s->next[i];
      
      if(s != NULL)
        printf(", ");
    }    
    
    printf("}\n");
  }
}

/*The search algorithm will return true(1) if the given key is stored in the */
/*set, otherwise false(0).*/

/*The pointer x is set to the header node of the list. The search begins at the */
/*topmost pointer of the header node according to the current level of the list. */
/*The next pointers at this level are traversed until the key is found, a NULL */
/*pointer is encountered or a key greater than the key being searched for is */
/*encountered. When this occurs we attempt to continue the search at the next */
/*lower level (from the previous element) until we have traversed as far as */
/*possible. */

/*Finally the level 0 pointer is traversed once. So now there are three */
/*possibilities for x.*/

/** x is pointing at the node with the key we are searching for.*/
/** x is pointing at a node with key greater than the key we are searching for.*/
/** x is NULL. */

/*In the first case the search was successful. */
const skipnode* contains_skipnode(const skipset* ss, const void* key, 
  int (*compare_keys)(const void* key1, const void* key2)) {

  skipnode* s = ss->header;
  int i;

  for(i = ss->level; i >= 0; i--) {
    /*first key less than second key*/
    int j = (s->next[i] != NULL) ? 
      compare_keys(s->next[i]->key, key) : INT_MAX;  

    while(s->next[i] != NULL && j < 0) {
      s = s->next[i];
      j = (s->next[i] != NULL) ? 
        compare_keys(s->next[i]->key, key) : INT_MAX;  
    }

    /*both keys equal*/
    if(s->next[i] != NULL && j == 0)
      return s->next[i];
  }

  return NULL;   
}

/*To insert a key we first perform the same kind of search as in the search */
/*algorithm. But, in order to insert a new node into the list we must maintain */
/*an array of pointers to the nodes that must be updated. */
void insert_skipnode(skipset* ss, const void* key, int key_sz, 
  int (*compare_keys)(const void* key1, const void* key2)) {
  
  if(contains_skipnode(ss, key, compare_keys) != NULL) /*no duplicates allowed in set*/
    return;

  int l = random_level(); /*level of new node*/

  if(l > ss->level) 
    ss->level = l;  
  
  insert_node(ss->header, make_skipnode(ss, l, key, key_sz), l, compare_keys);
}

/*The deletion algorithm starts the same way as the insertion algorithm. We */
/*declare an update array and then search for the node to be deleted. If the node */
/*is found we set the nodes in the update array to point at what |x| is pointing */
/*at. This effectively removes x from the list and so the memory occupied by the */
/*node may be freed. */
void delete_skipnode(skipset* ss, const void* key,
  int (*compare_keys)(const void* key1, const void* key2)) {

  skipnode* s = (skipnode*)contains_skipnode(ss, key, compare_keys);  
  if(s == NULL) /*must be in set*/
    return;

  delete_node(ss, s);
}

void delete_skipnode2(skipset* ss, skipnode* node) {
  delete_node(ss, node);
}

static void clear_skipset_item(skipset* ss) {
  if(ss->item != NULL) 
    free(ss->item);

  ss->item_sz = -1;
  ss->item = NULL;
}

/*The implementation of skip lists given by William Pugh states that the list */
/*should be terminated by a special NIL node that stores a key greater than any */
/*legal key. This stipulation was made so that the algorithms described in his */
/*paper would be very simple as they never had to explicitly check for pointers */
/*pointing at NIL. I will instead set the initial key of all pointer fields to */
/*the special C key NULL which is defined as 0. The function calloc() is used */
/*to allocate the array, calloc() will initialize all the pointers in the array */
/*to NULL. A level 0 node will have one next pointer, a level 1 node will have */
/*two next pointers and so on. Therefore we need to add one to the level when */
/*allocating memory for the array of next pointers. */
static skipnode* make_skipnode(skipset* ss, int level, const void* key, 
  int key_sz) {
  
  skipnode* sn = malloc(sizeof(skipnode));
  sn->next = calloc(level + 1, sizeof(skipnode*));
  sn->prev = calloc(level + 1, sizeof(skipnode*));

  sn->key = malloc(key_sz); 
  memcpy(sn->key, key, key_sz);
  sn->item = NULL;
  
  if(ss->item != NULL) {
    sn->item = malloc(ss->item_sz);
    memcpy(sn->item, ss->item, ss->item_sz);
    clear_skipset_item(ss);
  }

  sn->level = level;
  return sn;
}

/*Before getting to the main algorithms it is a good idea to tackle the problem */
/*of generating random levels for nodes. Each node that is created will have a */
/*random level between 0 and MAX_LEVEL inclusive. First we create a function that */
/*returns a float key between 0.0 and 1.0. The rand() function returns a */
/*pseudo-random integer between 0 and RAND_MAX. In order to get a float between */
/*0.0 and 1.0 we divide this key by RAND_MAX. */
static float frand(void) {
  return (float) rand() / RAND_MAX;
}

/*The desired function will return a random level between 0 and MAX_LEVEL. A */
/*probability distribution where half of the nodes that have level i pointers also */
/*have level i+1 pointers is used. This gives us a 50% chance of the */
/*random_level() function returning 0, a 25% chance of returning 1, a 12.5% */
/*chance of returning 2 and so on.*/

/*This function will seed the random number generator the first time it is called. */
/*This is achieved through the use of a static variable that keeps its key */
/*between function calls. This allows the function to seed the generator the */
/*first time it is called, and to remember not to seed it again on subsequent calls. */
static int random_level(void) {
  static bool first = true;
  int l = 0;

/*The random number generator should be seeded with the current system time so */
/*that the same sequence of random numbers isn't generated every time the program */
/*is run. */
  if(first) {
  /*original function crashes program, so using workaround    */
    srand(rand());  
/*    srand((unsigned int)time(NULL));*/
    first = false;
  }

  while(frand() < PROBABILITY && l < MAX_LEVEL)
    l++;

  return l;
} 

static void insert_node(skipnode* h, skipnode* s, int l,
  int (*compare_keys)(const void* key1, const void* key2)) {
  
  int i;
  for(i = l; i >= 0; i--) {
    int j = (h->next[i] != NULL) ? 
      compare_keys(h->next[i]->key, s->key) : INT_MAX;  
    
    while(h->next[i] != NULL && j < 0) {
      h = h->next[i];
      j = (h->next[i] != NULL) ? 
        compare_keys(h->next[i]->key, s->key) : INT_MAX;      
    }

    /*slot in new node*/
    s->next[i] = h->next[i];   
    s->prev[i] = h;   
    h->next[i] = s;   

    if(s->next[i] != NULL)
      s->next[i]->prev[i] = s;
  }  
}  

static void delete_node(skipset* ss, skipnode* s) {
  int i;
  
  for(i = s->level; i >= 0; i--) {
    /*repoint adjacent nodes*/
    if(s->next[i] != NULL)
      s->next[i]->prev[i] = s->prev[i];   

    if(s->prev[i] != NULL)
      s->prev[i]->next[i] = s->next[i];   
  }

  /*delete node*/
  release_node(s);
  
  /*reduce skipset level if higher levels are now empty*/
  for(i = ss->level; i >= 0; i--) 
    if(ss->header->next[i] == NULL && ss->level > 0) 
      ss->level--;
}  

static void release_node(skipnode* s) {
  free(s->key);
  free(s->next);
  free(s->prev);
  free(s->item);
  free(s);
}

