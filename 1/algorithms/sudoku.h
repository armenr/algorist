/*see README for original credits */

#ifndef SUDOKU_H
#define SUDOKU_H

#include "bool.h"

#define	BASED	   3			/* base dimension, 3*3 blocks */
#define DIMENSION  BASED*BASED		/* 9*9 board */
#define NCELLS     DIMENSION*DIMENSION  /* 81 cells in a 9*9 problem */

typedef struct {
	int x, y;			/* x and y coordinates of point */
} point;

typedef struct {
   int m[DIMENSION+1][DIMENSION+1];	/* matrix of board contents */
   int freecount;			/* how many open squares remain? */

   point move[NCELLS+1];
} boardtype;

int steps;				/* how many total move insertions? */

bool fast;				/* fast or slow nextmove algorithm? */
bool smart;				/* quickly test for unfillable squares?*/

bool is_a_solution(const boardtype *board);
void process_solution(const boardtype *board);
void construct_candidates(int k, boardtype *board, int c[], 
  int *ncandidates);

int possible_count(int x, int y, const boardtype *board);
void possible_values(int x, int y, const boardtype *board, bool possible[]);
void print_possible(bool possible[]);

void fill_square(int x, int y, int v, boardtype *board);
void free_square(int x, int y, boardtype *board);
void next_square(int *x, int *y, const boardtype* board);

void copy_board(const boardtype *a, boardtype *b);
void init_board(boardtype* board);
void print_board(const boardtype *board);
void read_board(boardtype* board);

void make_move(const int a[], int k, boardtype *board);
void unmake_move(int k, boardtype *board);

#endif /* SUDOKU_H */

