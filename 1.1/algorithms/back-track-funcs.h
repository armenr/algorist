/*see README for original credits */

#ifndef BACK_TRACK_FUNCS_H
#define BACK_TRACK_FUNCS_H

#include<stdbool.h>
#include"back-track.h"

/*path functions*/
void paths_process_solution(const back_track_t* b, int k, void* input);
bool paths_is_a_solution(const back_track_t* b, int k, void* input);
void paths_make_move(back_track_t* b, int k, void* input);
void paths_unmake_move(back_track_t* b, int k, void* input);
void paths_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

/*permutation functions*/
void perm_process_solution(const back_track_t* b, int k, void* input);
bool perm_is_a_solution(const back_track_t* b, int k, void* input);
void perm_make_move(back_track_t* b, int k, void* input);
void perm_unmake_move(back_track_t* b, int k, void* input);
void perm_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

/*subset functions*/
void subset_process_solution(const back_track_t* b, int k, void* input);
bool subset_is_a_solution(const back_track_t* b, int k, void* input);
void subset_make_move(back_track_t* b, int k, void* input);
void subset_unmake_move(back_track_t* b, int k, void* input);
void subset_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

#endif /* BACK_TRACK_FUNCS_H */

