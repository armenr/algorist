/*see README for original credits */

#ifndef TSP_H
#define TSP_H

#define	NMAX	1000			/* maximum number of points */

typedef struct {
	int x, y;			/* x and y coordinates of point */
} point;

typedef struct {
   int n;				/* how many points in problem? */
   point p[NMAX+1];			/* array of points */
} tsp_instance;

typedef struct {
   int n;				/* how many elements in permutation? */	
   int p[NMAX+1];			/* array if indices */
} tsp_solution;

void copy_solution(const tsp_solution *s, tsp_solution *t);
void initialize_solution(int n, tsp_solution *s);
void print_solution(const tsp_solution *s);
void random_solution(tsp_solution *s);
void read_solution(tsp_solution *s);
double solution_cost(tsp_solution *s, tsp_instance *t);
double transition(tsp_solution *s, tsp_instance *t, int i, int j);

double distance(tsp_solution *s, int x, int y, tsp_instance *t);
void random_sampling(tsp_instance *t, int nsamples, tsp_solution *bestsol);
void print_tsp(const tsp_instance *t);
void read_tsp(tsp_instance *t);

#endif /* TSP_H */

