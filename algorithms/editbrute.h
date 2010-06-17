/*see README for original credits */

#ifndef EDIT_BRUTE_H
#define EDIT_BRUTE_H

#include "bool.h"
#include "stringedit.h"

#define MAXLEN          101     /* longest possible string */

#define MATCH           0       /* enumerated type symbol for match */
#define INSERT          1       /* enumerated type symbol for insert */
#define DELETE          2       /* enumerated type symbol for delete */

typedef struct {
  int cost;               /* cost of reaching this cell */
  int parent;             /* parent cell */
} cell;

cell m[MAXLEN][MAXLEN];		/* dynamic programming table */

void print_matrix(const char *s, const char *t, bool costQ);
void reconstruct_path(char *s, char *t, int i, int j);
int string_compare(const char *s, const char *t, int i, int j);

#endif /* EDIT_BRUTE_H */
