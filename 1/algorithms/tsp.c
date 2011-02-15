/*see README for original credits */

#include "bool.h"
#include "random.h"
#include "tsp.h"			/* type declarations for TSP */
#include <math.h>
#include <stdio.h>

void initialize_solution(int n, tsp_solution *s) {
	int i;				

	s->n = n;
	for(i = 1; i <= n; i++)
		s->p[i] = i;
}

void copy_solution(const tsp_solution *s, tsp_solution *t) {
	int i;				
	
	t->n = s->n;
	for(i = 1; i <= s->n; i++)
		t->p[i] = s->p[i];
}
		

void print_solution(const tsp_solution *s) {
  int i;

  for(i = 1; i <= s->n; i++)
    printf(" %d", s->p[i]);
  printf("\n------------------------------------------------------\n");
}

void read_solution(tsp_solution *s) {
	int i;				

	scanf("%d\n", &(s->n));

	for(i = 1; i <= s->n; i++)
		scanf("%d", &(s->p[i]));
}

void random_solution(tsp_solution *s) {
	random_permutation(&(s->p[1]), (s->n)-1);
}

double transition(tsp_solution *s, tsp_instance *t, int i, int j) {
	double was, willbe;		/* before and after costs */
	bool neighbors = FALSE;			/* i,j neighboring tour positions? */

	if(i == j) 
		/*printf("Warning: null transition i=%d j=%d\n",i,j);*/
		return(0.0);

	if(i > j) return transition(s, t, j, i);

	if(i==(j-1)) neighbors = TRUE;

	if((i==1) && (j==(s->n))) {
		swap(&i, &j); neighbors = TRUE;
	}

	if(neighbors) {
		was = distance(s, i-1, i, t) + distance(s, j, j+1, t);
	} else {
  	was = distance(s, i-1, i, t) + distance(s, i, i+1, t)	+ 
  	distance(s, j-1, j, t) + distance(s, j, j+1, t);
	}

	swap(&(s->p[i]), &(s->p[j]));

	if(neighbors) {
		willbe = distance(s, i-1, i, t) + distance(s, j, j+1, t);
	} else {
  	willbe = distance(s, i-1, i, t) + distance(s, i, i+1, t)
	  	+ distance(s, j-1, j, t) + distance(s, j, j+1, t);
	}

	return(willbe - was);
}

double solution_cost(tsp_solution *s,  tsp_instance *t) {
	int i;				
	double cost;			/* cost of solution */

	cost = distance(s, t->n, 1, t);
	for(i = 1; i < t->n; i++)
		cost += distance(s, i, i+1, t);

	return cost;
}

void print_tsp(const tsp_instance *t) {
	int i;				

	for(i = 1; i <= t->n; i++)
		printf("%d %d %d\n", i, (t->p[i].x), (t->p[i].y));
}

void read_tsp(tsp_instance *t) {
	int i, j;

	scanf("%d\n", &(t->n));

	for(i = 1; i <= t->n; i++)
		scanf("%d %d %d\n", &j, &(t->p[i].x), &(t->p[i].y));
}

static int sq(int x) {
	return x*x;
}

double distance(tsp_solution *s, int x, int y, tsp_instance *t) {
	int i = x, j = y;

	if(i == ((t->n)+1)) i = 1;
	if(j == ((t->n)+1)) j = 1;

	if(i==0) i=(t->n);
	if(j==0) j=(t->n);

	return ( sqrt( (double) (sq(t->p[(s->p[i])].x - t->p[(s->p[j])].x) +
			         sq(t->p[(s->p[i])].y - t->p[(s->p[j])].y) ) ) );
}
