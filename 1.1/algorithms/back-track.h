/*see README for original credits */

#ifndef BACK_TRACK_H
#define BACK_TRACK_H

#include<stdbool.h>
#include"../ds/graph1.h"

typedef struct back_track_t {
	int* solution;			          /* solution vector */
	int sol_sz;
  bool finished;    /* found all solutions yet? */
  /*user supplied functions*/
  void (*construct_candidates)(const struct back_track_t* b, int k, int* c, 
    int* ncandidates, void* input);
  bool (*is_a_solution)(const struct back_track_t* b, int k, void* input);
  void (*make_move)(struct back_track_t* b, int k, void* input);
  void (*process_solution)(struct back_track_t* b, int k, void* input);
  void (*unmake_move)(struct back_track_t* b, int k, void* input);
} back_track_t;

/*library functions*/
void back_track(back_track_t* b, int k, int cand_sz, void* input);
void clear_back_track(back_track_t* b);
void init_back_track(back_track_t* b, int size);

#endif /* BACK_TRACK_H */

