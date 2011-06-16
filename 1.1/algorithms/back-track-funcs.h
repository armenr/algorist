/*see README for original credits */

#ifndef BACK_TRACK_FUNCS_H
#define BACK_TRACK_FUNCS_H

#include<stdbool.h>
#include"back-track.h"

/*path functions*/
typedef struct path_t {
  graph g;
  int v;  /*destination vertex*/
} path_t;

void paths_process_solution(back_track_t* b, int k, void* input);
bool paths_is_a_solution(const back_track_t* b, int k, void* input);
void paths_make_move(back_track_t* b, int k, void* input);
void paths_unmake_move(back_track_t* b, int k, void* input);
void paths_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

/*permutation functions*/
void perm_process_solution(back_track_t* b, int k, void* input);
bool perm_is_a_solution(const back_track_t* b, int k, void* input);
void perm_make_move(back_track_t* b, int k, void* input);
void perm_unmake_move(back_track_t* b, int k, void* input);
void perm_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

/*subset functions*/
void subset_process_solution(back_track_t* b, int k, void* input);
bool subset_is_a_solution(const back_track_t* b, int k, void* input);
void subset_make_move(back_track_t* b, int k, void* input);
void subset_unmake_move(back_track_t* b, int k, void* input);
void subset_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

/*sudoku*/
#define	BASED	   3			/* base dimension, 3*3 blocks */
#define DIMENSION  BASED*BASED		/* 9*9 board */
#define	EMPTY	   0			/* empty square */
#define NCELLS     DIMENSION*DIMENSION  /* 81 cells in a 9*9 problem */
#define	NONE	   -1			/* not possible to fill */

typedef struct point {
	int x, y;			/* x and y coordinates of point */
} point;

typedef struct board_t {
   int m[DIMENSION+1][DIMENSION+1];	/* matrix of board contents */
   int freecount;			/* how many open squares remain? */

   point move[NCELLS+1];
} board_t;

typedef struct sudoku_game {
  board_t board;
  
  int steps;				/* how many total move insertions? */
  bool fast;				/* fast or slow nextmove algorithm? */
  bool smart;				/* quickly test for unfillable squares?*/
} sudoku_game;

void sudoku_process_solution(back_track_t* b, int k, void* input);
bool sudoku_is_a_solution(const back_track_t* b, int k, void* input);
void sudoku_make_move(back_track_t* b, int k, void* input);
void sudoku_unmake_move(back_track_t* b, int k, void* input);
void sudoku_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input);

void copy_board(const board_t* a, board_t* b);
void print_board(const board_t* board);
void read_board(board_t* board);

#endif /* BACK_TRACK_FUNCS_H */

