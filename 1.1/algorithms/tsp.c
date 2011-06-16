/*see README for original credits */

#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include"random.h"
#include"tsp.h"

static double distance(const tsp_solution* s, const tsp_instance* t, 
  int x, int y);
static int sq(int x);

void tsp_copy_solution(const void* s, void* t) {
  const tsp_solution* ts = (const tsp_solution*)s;
  tsp_solution* tt = (tsp_solution*)t;

	tt->n = ts->n;
	int i;
	for(i = 1; i <= ts->n; i++)
		tt->p[i] = ts->p[i];
}

void tsp_initialize_solution(void* s, int n) {
  tsp_solution* ts = (tsp_solution*)s;
	ts->n = n;
	int i;
	for(i = 1; i <= n; i++)
		ts->p[i] = i;
}

void tsp_random_solution(void* s) {
  tsp_solution* ts = (tsp_solution*)s;
	random_permutation(&(ts->p[1]), (ts->n)-1);
}

double tsp_solution_cost(const void* s, const void* t) {
  const tsp_solution* ts = (const tsp_solution*)s;
  const tsp_instance* tt = (const tsp_instance*)t;

	double cost = distance(ts, tt, tt->n, 1);
  int i;
	for(i = 1; i < tt->n; i++)
		cost += distance(ts, tt, i, i+1);
	return cost;
}

double tsp_transition(void* s, const void* t, int i, int j) {
  tsp_solution* ts = (tsp_solution*)s;
  const tsp_instance* tt = (const tsp_instance*)t;
  
	if(i == j) 
		return(0.0);

	if(i > j) 
	  return tsp_transition(ts, tt, j, i);

	bool neighbors = false;			/* i,j neighboring tour positions? */

	if(i == j-1) 
	  neighbors = true;

	if(i == 1 && j == ts->n) {
		swap(&i, &j); 
		neighbors = true;
	}

	double was, willbe;		/* before and after costs */

	if(neighbors) {
		was = distance(ts, tt, i-1, i) + distance(ts, tt, j, j+1);
	} else {
  	was = distance(ts, tt, i-1, i) + distance(ts, tt, i, i+1)	+ 
  	distance(ts, tt, j-1, j) + distance(ts, tt, j, j+1);
	}

	swap(&(ts->p[i]), &(ts->p[j]));

	if(neighbors) {
		willbe = distance(ts, tt, i-1, i) + distance(ts, tt, j, j+1);
	} else {
  	willbe = distance(ts, tt, i-1, i) + distance(ts, tt, i, i+1)
	  	+ distance(ts, tt, j-1, j) + distance(ts, tt, j, j+1);
	}

	return willbe - was;
}

void print_solution(const tsp_solution* s) {
  int i;
  for(i = 1; i <= s->n; i++)
    printf(" %d", s->p[i]);
  printf("\n------------------------------------------------------\n");
}

void read_solution(tsp_solution* s) {
	scanf("%d\n", &(s->n));
  int i;
	for(i = 1; i <= s->n; i++)
		scanf("%d", &(s->p[i]));
}

void print_tsp(const tsp_instance* t) {
  int i;
	for(i = 1; i <= t->n; i++)
		printf("%d %d %d\n", i, (t->p[i].x), (t->p[i].y));
}

void read_tsp(tsp_instance* t) {
	scanf("%d\n", &(t->n));
	int i, j;
	for(i = 1; i <= t->n; i++)
		scanf("%d %d %d\n", &j, &(t->p[i].x), &(t->p[i].y));
}

static double distance(const tsp_solution* s, const tsp_instance* t, 
  int x, int y) {
  
	int i = x, j = y;

	if(i == (t->n)+1) 
	  i = 1;
	if(j == (t->n)+1) 
	  j = 1;

	if(i == 0) 
	  i = t->n;
	  
	if(j == 0) 
	  j = t->n;

	return sqrt((double) 
	  (sq(t->p[(s->p[i])].x - t->p[(s->p[j])].x) +
     sq(t->p[(s->p[i])].y - t->p[(s->p[j])].y)));
}

static int sq(int x) {
	return x*x;
}
