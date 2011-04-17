/*see README for original credits */

#ifndef EDIT_STRING_H
#define EDIT_STRING_H

#include<stdbool.h>

#define MAXLEN          101     /* longest possible string */

#define MATCH           0       /* enumerated type symbol for match */
#define INSERT          1       /* enumerated type symbol for insert */
#define DELETE          2       /* enumerated type symbol for delete */

typedef struct {
  int cost;               /* cost of reaching this cell */
  int parent;             /* parent cell */
} cell;

void print_matrix(const char *s, const char *t, bool costQ);
void reconstruct_path(char *s, char *t, int i, int j);
int string_compare(char *s, char *t);

void goal_cell(const char *s, const char *t, int *i, int *j);
int match(char c, char d);
int indel(char c);
void row_init(int i);		/* what is m[0][i]? */
void column_init(int i);	/* what is m[i][0]? */
void match_out(const char *s, const char *t, int i, int j);
void insert_out(const char *t, int j);
void delete_out(const char *s, int i);

#endif /* EDIT_STRING_H */
