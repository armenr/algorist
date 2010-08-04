/*see README for original credits */

#include "backtrack.h"
#include "bool.h"

#define MAXCANDIDATES   100		/* max possible next extensions */
#define NMAX            100		/* maximum solution size */

extern void process_solution(const int a[], int k, data input);
extern bool is_a_solution(const int a[], int k, data input);
extern void make_move(const int a[], int k, data input);
extern void unmake_move(const int a[], int k, data input);
extern void construct_candidates(const int a[], int k, data input, int c[], int *ncandidates);

bool finished = FALSE;                  /* found all solutions yet? */

void back_track(int a[], int k, data input) {
  int c[MAXCANDIDATES];           /* candidates for next position */
  int ncandidates;                /* next position candidate count */
  int i;                          /* counter */

  if(is_a_solution(a, k, input))
    process_solution(a, k, input);
  else {
    k++;
    construct_candidates(a, k, input, c, &ncandidates);

    for(i = 0; i < ncandidates; i++) {
      a[k] = c[i];
      make_move(a, k, input);

      back_track(a, k, input);
      if(finished) return;	/* terminate early */

      unmake_move(a, k, input);
    }
  }
}
