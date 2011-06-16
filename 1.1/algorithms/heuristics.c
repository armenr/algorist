/*see README for original credits */

#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include"heuristics.h"
#include"random.h"

static void print_solution_count(const void* prob, const void* sol, 
  const heuristic* h);

void clear_heuristic(heuristic* h) {
  free(h->best_solution);
}

void init_heuristic(heuristic* h, int samples, int runs, int sol_sz) {
  h->solution_count = 0;
  h->runs = runs;
  h->sol_size = sol_sz;
  h->best_solution = malloc(sol_sz);
  h->samples = samples;
  h->initialize_solution(h->best_solution, samples);
}

/*	
  These routines implement simulated annealing.  Pairs of components of the 
  same type will be swapped at random, and the new arrangment	accepted either 
  if(1) it is an improvement, or (2) the penalty is	less than a random number, 
  which is a function of the temperature	of the system.
	We are seeking to *minimize* the current_value.
*/
/*
Simulated-Annealing()
  Create initial solution S
  Initialize temperature t

  repeat
    for i = 1 to iteration-length do
      Generate a random transition from S to Si

      If (C(S) ≥ C(Si )) then 
        S = Si
      else if (e(C(S)−C(Si ))/(k·t) > random[0, 1)) then 
        S = Si

    Reduce temperature t
  until (no change in C(S))

Return S
*/
void repeated_heuristic(const void* prob, heuristic* h,
  void (*heuristic_fn)(const void* prob, void* sol, heuristic* h)) {
  
  double best_cost = h->solution_cost(h->best_solution, prob);  
  int i;
  
  for(i = 1; i <= h->runs; i++) {
    void* sol = malloc(h->sol_size);
    heuristic_fn(prob, sol, h);
    double cost_now = h->solution_cost(sol, prob);

    if(cost_now < best_cost) {
      best_cost = cost_now;
      h->copy_solution(sol, h->best_solution);
    }

    free(sol);
  }
}

void anneal(const void* prob, void* sol, heuristic* h) {
  h->initialize_solution(sol, h->samples);

	double temperature = INITIAL_TEMPERATURE;			/* the current system temp */
	double current_value = h->solution_cost(sol, prob);	/* value of current state */

	int i;

	for(i = 1; i <= COOLING_STEPS; i++) {
		temperature *= COOLING_FRACTION;

		double start_value = current_value;	
		
		int j; 
		
		for(j = 1; j <= STEPS_PER_TEMP; j++) {

      /* pick indices of elements to swap */
      int i1 = random_int(1, h->samples); 
      int i2 = random_int(1, h->samples);
      double delta = h->transition(sol, prob, i1, i2);  /* value after swap */
      /* exponent for energy funct*/
      double exponent = (-delta / current_value) / (K * temperature);
      double merit = pow(E, exponent); 
      double flip = random_float(0, 1); /* hold swap accept conditions*/

      if(delta < 0) { /*ACCEPT-WIN*/
        current_value += delta;

        if(TRACE_OUTPUT) 
          printf("swap WIN %d--%d value %f  temp=%f i=%d j=%d\n",
          i1, i2, current_value, temperature, i, j);
	      
      } else { 

        if(merit > flip) {  /*ACCEPT-LOSS*/
          current_value += delta;

          if(TRACE_OUTPUT) 
            printf("swap LOSS %d--%d value %f merit=%f flip=%f i=%d j=%d\n",
            i1, i2, current_value, merit, flip, i, j);

        } else  /* REJECT */
          h->transition(sol, prob, i1, i2);
      }
      
      (h->solution_count)++;
      print_solution_count(prob, sol, h);
		}
		
		if((current_value - start_value) < 0.0){ /* rerun at this temp */
			temperature /= COOLING_FRACTION;
			
			if(TRACE_OUTPUT) 
			  printf("rerun at temperature %f\n", temperature);
		}
	}
}

void hill_climbing(const void* prob, void* sol, heuristic* h) {
  h->initialize_solution(sol, h->samples);
	h->random_solution(sol);
	double cost = h->solution_cost(sol, prob);  /* best cost so far */
  bool stuck;			/* did I get a better solution? */

	do {
		stuck = true;

    int i, j;
    
		for(i = 1; i < h->samples; i++)
			for(j = i+1; j <= h->samples; j++) {
				double delta = h->transition(sol, prob, i, j);  /* swap cost */

				if(delta < 0) {
					stuck = false; 
					cost += delta;
				} else
					h->transition(sol, prob, j, i);

        (h->solution_count)++;
        print_solution_count(prob, sol, h);
			}
			
	} while(!stuck);
}

/*      
  Use random sampling to provide a heuristic solution to a given optimization 
  problem.
*/
void random_sampling(const void* prob, void* sol, heuristic* h) {
  h->initialize_solution(sol, h->samples);
	h->random_solution(sol);
  (h->solution_count)++;
  print_solution_count(prob, sol, h);
}

static void print_solution_count(const void* prob, const void* sol, 
  const heuristic* h) {

  if(h->solution_count % PRINT_FREQUENCY == 0)
    printf("%d %7.1f\n", h->solution_count, h->solution_cost(sol, prob));
}

