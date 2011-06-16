/*see README for original credits */

#ifndef SET_UNION_H
#define SET_UNION_H

#include<stdbool.h>

typedef struct {
  int* p;  /* parent element */
  int* size; /* number of elements in subtree i */
  int n;				/* number of elements in set */
} set_union;

void clear_set_union(set_union* s);
int find_set_union(const set_union* s, int x);
void init_set_union(set_union* s, int n);
void print_set_union(const set_union* s);
void merge_set_union(set_union* s, int r1, int r2);
bool same_comp_set_union(const set_union* s, int s1, int s2, int* r1, int*r2);

#endif /* SET_UNION_H */
