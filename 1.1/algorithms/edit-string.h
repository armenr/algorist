/*see README for original credits */

#ifndef EDIT_STRING_H
#define EDIT_STRING_H

#include<stdbool.h>

#define NONE  -1

typedef enum {
  MATCH = 0,        /* enumerated type symbol for match */
  INSERT = 1,        /* enumerated type symbol for insert */
  DELETE = 2       /* enumerated type symbol for delete */
} edit;

typedef struct cell {
  int cost;               /* cost of reaching this cell */
  int parent;             /* parent cell */
} cell;

typedef struct edit_string {
  cell* m;  /*dynamic table*/
  int row_sz;
  int col_sz;
  
  /*user supplied functions*/  
  void (*delete_out)(const char* s, int i);
  void (*insert_out)(const char* t, int j);
  void (*match_out)(const char* s, const char* t, int i, int j);
  
  void (*row_init)(struct edit_string* e, int i);
  void (*col_init)(struct edit_string* e, int i);
  void (*goal_cell)(const struct edit_string* e, int* i, int* j);
  int (*match)(char c, char d);  
} edit_string;

void clear_edit_str(edit_string* e);
void init_edit_str(edit_string* e, int row_sz, int col_sz);
void print_matrix(const edit_string* e, const char* s, const char* t, 
  bool costQ);
void reconstruct_path(const edit_string* e, const char* s, const char* t, 
  int i, int j);
int string_compare(edit_string* e, const char* s, const char* t);
  
/*edit string match*/
void col_init(edit_string* e, int i);	
void row_init(edit_string* e, int i);		
void goal_cell(const edit_string* e, int* i, int* j);

int match(char c, char d);
void delete_out(const char* s, int i);
void insert_out(const char* t, int j);
void match_out(const char* s, const char* t, int i, int j);

/*find substring */
void row_init_sub(edit_string* e, int i);
void goal_cell_sub(const edit_string* e, int* i, int* j);

/*lcs*/
int match_lcs(char c, char d);
void delete_out_lcs(const char* s, int i);
void insert_out_lcs(const char* t, int j);
void match_out_lcs(const char* s, const char* t, int i, int j);

#endif /* EDIT_STRING_H */
