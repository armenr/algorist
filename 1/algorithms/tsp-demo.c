/*see README for original credits */

#include "random.h"
#include "tsp.h"
#include <stdio.h>
#include <string.h>

extern int solution_count;

int main(void) {
	tsp_instance t;			/* tsp points */
	tsp_solution s;			/* tsp solution */

	read_tsp(&t);

	read_solution(&s);
	printf("OPTIMAL SOLUTION COST = %7.1f\n", solution_cost(&s, &t));
  print_solution(&s);

	initialize_solution(t.n, &s);
	printf("solution_cost = %7.1f\n", solution_cost(&s, &t));
	print_solution(&s);
	
/*
	solution_count=0;
	random_sampling(&t,1500000,&s);
        printf("random sampling %d iterations, cost = %7.1f\n",
			solution_count,solution_cost(&s,&t));
       	print_solution(&s);

	solution_count=0;
        repeated_hill_climbing(&t,195,&s);
        printf("repeated hill climbing %d iterations, cost = %7.1f\n",
                        solution_count,solution_cost(&s,&t));
        print_solution(&s);
*/

	solution_count = 0;
	repeated_annealing(&t, 3, &s);
	printf("repeated annealing %d iterations, cost = %7.1f\n", 
	  solution_count, solution_cost(&s, &t));
	print_solution(&s);
  return 0;
}

/* run with data in tsp-examples */


