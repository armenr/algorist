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

/*heuristic functions*/
void tsp_copy_solution(const void* s, void* t);
void tsp_initialize_solution(void* s, int n);
void tsp_random_solution(void* s);
double tsp_solution_cost(const void* s, const void* t);
double tsp_transition(void* s, const void* t, int i, int j);

void print_solution(const tsp_solution* s);
void read_solution(tsp_solution* s);

void print_tsp(const tsp_instance* t);
void read_tsp(tsp_instance* t);

#endif /* TSP_H */

