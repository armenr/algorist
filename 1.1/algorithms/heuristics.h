/*see README for original credits */

#ifndef HEURISTICS_H
#define HEURISTICS_H

/* print the swaps as they happen */
#define TRACE_OUTPUT	false		

/* how often we report progress */
#define PRINT_FREQUENCY 10000             

/**************** Simulated Annealing Constants **************************/

/* how many solution attempts do you want?  More than 1 enables you to eyeball 
the output and pick the best. If you are getting stuck in local optima, 
this good to try. */
#define REPEAT_COUNT		1	

/* start temperature -- probably leave intact */
#define	INITIAL_TEMPERATURE	1	

/* how many times do we cool -- make higher to improve quality, lower to speed 
the program up.  Move in tandem with the COOLING_FRACTION */
#define COOLING_STEPS		500	

/* how much to cool each time -- make higher to improve quality, lower to speed 
the program up. */
#define COOLING_FRACTION	0.97	

/* lower makes it faster, higher makes it potentially better. */
#define STEPS_PER_TEMP		1000	

#define E 2.718   /* number e -- probably leave intact*/

/* problem specific Boltzman's constant May have to adjust if your global value 
function changes the sizes of the numbers it produces.  It is important that 
jumps seem random at the begining of the run, and rare at the end of a run, and 
this is a knob to tweak that. */
#define K			0.01	

/*	The stuff below is less likely to change in adapting to new 	problems, 
    but look for yourself before leaping.
*/

#define ERROR		"ERROR"		/* string denoting error id */
#define ERROR_VALUE	0.0		/* float denoting error value */

/*=========================================================================*/

typedef struct heuristic {
  void* best_solution;  /* best solution so far*/
  int sol_size; 
	int solution_count; /* how many solutions evaluated */
  int runs; /*number of iterations to perform*/
  int samples;  /*sample size*/
  
  /*user supplied functions*/
  void (*copy_solution)(const void* s, void* t);
  void (*initialize_solution)(void* s, int n);
  void (*random_solution)(void* s);
  double (*solution_cost)(const void* s, const void* t);
  double (*transition)(void* s, const void* t, int i, int j);
} heuristic;

void clear_heuristic(heuristic* h);
void init_heuristic(heuristic* h, int samples, int runs, int sol_sz);
void repeated_heuristic(const void* prob, heuristic* h,
  void (*heuristic_fn)(const void* prob, void* sol, heuristic* h));

/*user supplied heuristic functions*/
void anneal(const void* prob, void* sol, heuristic* h);
void hill_climbing(const void* prob, void* sol, heuristic* h);
void random_sampling(const void* prob, void* sol, heuristic* h);

#endif /* HEURISTICS_H */

