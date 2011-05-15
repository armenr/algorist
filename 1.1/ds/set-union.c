/*see README for original credits */

#include"set-union.h"
#include<stdio.h>

#define ROOT 0

void init_set_union(set_union *s, int n) {
	int i;

	for(i = 0; i < n; i++) {
		s->p[i] = ROOT;
		s->size[i] = 1;
	}
  s->n = n;
}

int find_set_union(const set_union *s, int x) {
  if(s->p[x] == ROOT)
		return x;
	else
		return find_set_union(s, s->p[x]);
}

void merge_set_union(set_union *s, int r1, int r2) {
/*	int r1, r2;			 roots of sets */

/*already found during same_comp_set_union search*/
/*	r1 = find_set_union(s, s1);*/
/*	r2 = find_set_union(s, s2);*/

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
bool same_comp_set_union(const set_union *s, int s1, int s2, int* r1, int*r2) {
	*r1 = find_set_union(s, s1);
	*r2 = find_set_union(s, s2);
	return *r1 == *r2;
}

void print_set_union(const set_union *s) {
  int i;

  for(i = 0; i < s->n; i++)
    printf("%i set=%d size=%d \n", i, s->p[i], s->size[i]);

  printf("\n");
}

