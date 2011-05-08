/*see README for original credits */

#ifndef SET_UNION_H
#define SET_UNION_H

#include<stdbool.h>

#define SET_SIZE       1000

typedef struct {
  int p[SET_SIZE+1];  /* parent element */
  int size[SET_SIZE+1]; /* number of elements in subtree i */
  int n;				/* number of elements in set */
} set_union;

int find_set_union(const set_union *s, int x);
void print_set_union(const set_union *s);
void init_set_union(set_union *s, int n);
bool same_comp_set_union(const set_union *s, int s1, int s2, int* r1, int*r2);
void merge_set_union(set_union *s, int r1, int r2);

#endif /* SET_UNION_H */


