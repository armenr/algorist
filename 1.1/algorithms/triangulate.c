/*see README for original credits */

#include "triangulate.h"
#include <math.h>
#include <stdio.h>

void triangulate(const polygon *p, triangulation *t) {
	int l[MAXPOLY], r[MAXPOLY];	/* left/right neighbor indices */
	int i;				/* counter */

	for(i = 0; i < p->n; i++) {	/* initialization */
		l[i] = ((i-1) + p->n) % p->n;
		r[i] = ((i+1) + p->n) % p->n;
	}

	t->n = 0;
	i = p->n-1;
	
	while(t->n < (p->n-2)) {
		i = r[i];
		if(ear_Q(l[i], i, r[i],p)) {
			add_triangle(t, l[i], i, r[i]);
			l[ r[i] ] = l[i];
			r[ l[i] ] = r[i];
		}
	}
}

void add_triangle(triangulation *t, int i, int j, int k) {
	int n;				/* number of triangles in t */

	n = t->n;
	t->t[n][0] = i;
	t->t[n][1] = j;
	t->t[n][2] = k;
	t->n = n + 1;
}

bool ear_Q(int i, int j, int k, const polygon *p) {
	triangle t;			/* coordinates for points i,j,k */
	int m;				/* counter */
	bool cw();

	copy_point(p->p[i], t[0]);
	copy_point(p->p[j], t[1]);
	copy_point(p->p[k], t[2]);

	if(cw(t[0], t[1], t[2])) return FALSE;

	for(m = 0; m < p->n; m++) 
		if((m!=i) && (m!=j) && (m!=k))
			if(point_in_triangle(p->p[m], t)) return FALSE;

	return TRUE;
}


bool point_in_triangle(const point p, triangle t) {
	int i;				/* counter */
	bool cw();

	for(i = 0; i < 3; i++)
		if(cw(t[i], t[(i+1)%3], p)) return FALSE;

	return TRUE;
}

double area_triangulation(const polygon *p) {
	triangulation t;                /* output triangulation */
	double total = 0.0;		/* total area so far */
  int i;                          /* counter */

	triangulate(p, &t);
	for(i = 0; i < t.n; i++)
		total += triangle_area(p->p[t.t[i][0]],	p->p[t.t[i][1]], p->p[t.t[i][2]]);

	return(total);
}

double area(const polygon *p) {
	double total = 0.0;		/* total area so far */
	int i, j;			/* counters */

	for(i = 0; i < p->n; i++) {
		j = (i+1) % p->n;
		total += (p->p[i][X]*p->p[j][Y]) - (p->p[j][X]*p->p[i][Y]);
	}

	return(total / 2.0);
}

void print_triangulation(const triangulation *t) {
	int i, j;			/* counters */

	for(i = 0; i < t->n; i++) {
		for(j = 0; j < 3; j++)
      printf(" %d ", t->t[i][j]);
		printf("\n");
	}
}
