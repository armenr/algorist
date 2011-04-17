/*see README for original credits */

#ifndef SET_UNION_H
#define SET_UNION_H

#define SET_SIZE       1000

typedef struct {
  int p[SET_SIZE+1];  /* parent element */
  int size[SET_SIZE+1]; /* number of elements in subtree i */
  int n;				/* number of elements in set */
} set_union;

void set_union_init(set_union *s, int n);
int find(const set_union *s, int x);
void print_set_union(const set_union *s);
void set_union_init(set_union *s, int n);
bool same_component(const set_union *s, int s1, int s2);
void union_sets(set_union *s, int s1, int s2);

#endif /* SET_UNION_H */


