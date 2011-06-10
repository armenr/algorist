/*see README for original credits */

#ifndef EDIT_STRING_H
#define EDIT_STRING_H

#include<stdbool.h>

#define NONE  -1
#define MAXLEN  101     /* longest possible string */

typedef enum {
  MATCH = 0,        /* enumerated type symbol for match */
  INSERT = 1,        /* enumerated type symbol for insert */
  DELETE = 2       /* enumerated type symbol for delete */
} edit;

typedef struct {
  int cost;               /* cost of reaching this cell */
  int parent;             /* parent cell */
} cell;

void goal_cell(const char* s, const char* t, int* i, int* j);
void print_matrix(const char* s, const char* t, bool costQ);
void reconstruct_path(char* s, char* t, int i, int j);
int string_compare(char* s, char* t);

#endif /* EDIT_STRING_H */
