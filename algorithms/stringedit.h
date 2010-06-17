/*see README for original credits */

#ifndef STRING_EDIT_H
#define STRING_EDIT_H

void goal_cell(const char *s, const char *t, int *i, int *j);
int match(char c, char d);
int indel(char c);
void row_init(int i);		/* what is m[0][i]? */
void column_init(int i);	/* what is m[i][0]? */
void match_out(const char *s, const char *t, int i, int j);
void insert_out(const char *t, int j);
void delete_out(const char *s, int i);

#endif /* STRING_EDIT_H */
