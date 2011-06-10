/*see README for original credits */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"set-union.h"

void clear_set_union(set_union* s) {
  free(s->p);
  free(s->size);
}

void init_set_union(set_union* s, int n) {
  int l = n * sizeof(int);
  s->p = malloc(l);
  memset(s->p, 0, l);
  s->size = malloc(l);
  memset(s->size, 0, l);
  
	int i;
	for(i = 0; i < n; i++) {
		s->p[i] = i;
		s->size[i] = 1;
	}
  s->n = n;
}

int find_set_union(const set_union* s, int x) {
  if(s->p[x] == x)
		return x;
	else
		return find_set_union(s, s->p[x]);
}

void merge_set_union(set_union* s, int r1, int r2) {
	if(r1 == r2) 
	  return;		/* already in same set */

  int sz = s->size[r1] + s->size[r2];
  
	if(s->size[r1] >= s->size[r2]) {
		s->size[r1] = sz;
		s->p[r2] = r1;
	}	else {
		s->size[r2] = sz;
    s->p[r1] = r2;
	}
}

/*side effect in search*/
bool same_comp_set_union(const set_union* s, int s1, int s2, int* r1, int*r2) {
	*r1 = find_set_union(s, s1);
	*r2 = find_set_union(s, s2);
	return *r1 == *r2;
}

void print_set_union(const set_union* s) {
  int i;
  for(i = 0; i < s->n; i++)
    printf("%i set=%d size=%d \n", i, s->p[i], s->size[i]);

  printf("\n");
}

