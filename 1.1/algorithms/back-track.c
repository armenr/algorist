/*see README for original credits */

#include<stdlib.h>
#include"back-track.h"

/*
Backtrack-DFS(A, k)
  if A = (a1 , a2 , ..., ak ) is a solution, report it.

  else
    k =k+1
    compute Sk

    while Sk != ∅ do
      ak = an element in Sk
      Sk = Sk − ak
      Backtrack-DFS(A, k)
*/
void back_track(back_track_t* b, int k, int cand_sz, void* input) {
  if(b->is_a_solution(b, k, input))
    b->process_solution(b, k, input);

  else {
    int c[cand_sz];  /* candidates for next position */
    int ncandidates;  /* next position candidate count */

    b->construct_candidates(b, ++k, c, &ncandidates, input);

    int i;

    for(i = 0; i < ncandidates; i++) {
      b->solution[k] = c[i];

      b->make_move(b, k, input);
      back_track(b, k, ncandidates, input);

      if(b->finished) 
        return;	/* terminate early */

      b->unmake_move(b, k, input);
    }
  }
}

void clear_back_track(back_track_t* b) {
  free(b->solution);
}

void init_back_track(back_track_t* b, int size) {
  b->sol_sz = size;
  b->solution = calloc(b->sol_sz, sizeof(int));
  b->finished = false;
}
