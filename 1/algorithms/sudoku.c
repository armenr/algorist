/*see README for original credits */

#include "bool.h"
#include "sudoku.h"
#include <stdio.h>

#define MAXCANDIDATES   100		/* max possible next extensions */
#define NMAX            100		/* maximum solution size */

static bool finished = FALSE;                  /* found all solutions yet? */

void back_track(int a[], int k, boardtype *board) {
  int c[MAXCANDIDATES];           /* candidates for next position */
  int ncandidates;                /* next position candidate count */
  int i;                          /* counter */

  steps++;

  if(is_a_solution(board)) 
    process_solution(board);
  else {
    k++;
    construct_candidates(k, board, c, &ncandidates);

    for(i = 0; i < ncandidates; i++) {
      a[k] = c[i];
      make_move(a, k, board);
      back_track(a, k, board);
      if(finished) return;	/* terminate early */
      unmake_move(k, board);
    }
  }
}

void possible_values(int x, int y, const boardtype *board, bool possible[]) {
  int i, j, xlow, ylow;			/* origin of box with (x,y) */
	bool init;			/* is anything/everthing possible? */

	if((board->m[x][y] != 0) || ((x<0)||(y<0)))
		init = FALSE;
	else
		init = TRUE;

  for(i = 1; i <= DIMENSION; i++) possible[i] = init;

	for(i = 0; i < DIMENSION; i++)
		if(board->m[x][i] != 0) possible[ board->m[x][i] ] = FALSE;

	for(i = 0; i < DIMENSION; i++)
		if(board->m[i][y] != 0) possible[ board->m[i][y] ] = FALSE;

	xlow = BASED * ((int) (x / BASED));	ylow = BASED * ((int) (y / BASED));

	for(i = xlow; i < xlow+BASED; i++)
		for(j = ylow; j < ylow+BASED; j++)
      if(board->m[i][j] != 0) possible[ board->m[i][j] ] = FALSE;
}

void print_possible(bool possible[]) {
	int i;				/* counter */

	for(i=0; i<=DIMENSION; i++)
		if(possible[i] == TRUE) printf(" %d",i);
	printf("\n");
}

int possible_count(int x, int y, const boardtype *board) {
	int i, cnt = 0;
	bool possible[DIMENSION+1];     /* what is possible for the square */

	possible_values(x, y ,board, possible);
	for(i = 0; i <= DIMENSION; i++)
		if(possible[i] == TRUE) cnt++;
	return cnt ;
}

void fill_square(int x, int y, int v, boardtype *board) {
	if(board->m[x][y] == 0)
		board->freecount--;
	else
		printf("Warning: filling already filled square (%d,%d)\n", x, y);

	board->m[x][y] = v;
}

void free_square(int x, int y, boardtype *board) {
	if(board->m[x][y] != 0)
		board->freecount++;
	else
		printf("Warning: freeing already empty square (%d,%d)\n", x, y);

	board->m[x][y] = 0;
}
	

void next_square(int *x, int *y, const boardtype* board) {
	int i, j;
	int bestcnt, newcnt;		/* the best and latest square counts */
	bool doomed;			/* some empty square without moves? */

	bestcnt = DIMENSION + 1; doomed = FALSE;
	*x = *y = -1;

	for(i = 0; i < DIMENSION; i++) {
		for(j = 0; j < DIMENSION; j++) {
			newcnt = possible_count(i, j, board);

			if((newcnt==0) && (board->m[i][j]==0))
				doomed = TRUE;
		    if(fast) {
    			if((newcnt < bestcnt) && (newcnt >= 1)) {
				    bestcnt = newcnt; *x = i; *y = j;
			    }
		    } else // !fast  
			    if((newcnt >= 1) && (board->m[i][j] == 0)) {
				    *x = i; *y = j;
			    }
		}
	}

	if(doomed && smart) {
		*x = *y = -1;		/* initialize to non-position */
	}
}


void print_board(const boardtype *board) {
	int i, j;

	printf("\nThere are %d free board positions.\n", board->freecount);

	for(i = 0; i < DIMENSION; i++) {
		for(j = 0; j < DIMENSION; j++) {

			if(board->m[i][j] == 0)
				printf(" ");
			else
				printf("%c", (char) '0'+board->m[i][j]);
				
			if((j+1)%BASED == 0)
				printf("|");
		}
		
		printf("\n");

		if((i+1)%BASED == 0) {
			for(j=0; j<(DIMENSION+BASED-1); j++)
				printf("-");

			printf("\n");

		}
	}
}

void init_board(boardtype* board) {
	int i, j;

	for(i = 0; i < DIMENSION; i++)
		for(j = 0; j < DIMENSION; j++)
			board->m[i][j] = 0;
	board->freecount = DIMENSION*DIMENSION;
}

void read_board(boardtype* board) {
	int i, j, value;		
	char c;

	init_board(board);

	for(i = 0; i < DIMENSION; i++) {
    for(j = 0; j < DIMENSION; j++) {
			scanf("%c", &c);
			value = (int) (c - '0');
			if(value != 0)
				fill_square(i, j, value, board);
		}
		scanf("\n"); 
	}
}

void copy_board(const boardtype *a, boardtype *b) {
	int i, j;

	b->freecount = a->freecount;

	for(i = 0; i < DIMENSION; i++)
		for(j = 0; j < DIMENSION; j++)
			b->m[i][j] = a->m[i][j];
}
	

void process_solution(const boardtype *board) {
	finished = TRUE;
  printf("process solution\n");
	print_board(board);
}

bool is_a_solution(const boardtype *board) {
	if(board->freecount == 0) 
		return TRUE;
	else
		return FALSE;
}

void make_move(const int a[], int k, boardtype *board) {
	fill_square(board->move[k].x, board->move[k].y, a[k], board);
}

void unmake_move(int k, boardtype *board) {
	free_square(board->move[k].x, board->move[k]. y, board);
}

void construct_candidates(int k, boardtype *board, int c[], 
  int *ncandidates) {
	int x, y;			/* position of next move */
	int i;				/* counter */
	bool possible[DIMENSION+1];     /* what is possible for the square */

	next_square(&x, &y, board);	/* which square should we fill next? */

	board->move[k].x = x;		/* store our choice of next position */
	board->move[k].y = y;

	*ncandidates = 0;

	if((x<0) && (y<0)) return;	/* error condition, no moves possible */

	possible_values(x, y, board, possible);
	for(i=1; i<=DIMENSION; i++)
    if(possible[i] == TRUE) {
			c[*ncandidates] = i;
			(*ncandidates)++;
		}
}

int main(void) {
	int a[DIMENSION * DIMENSION+1];
	
	boardtype board, temp;
	read_board(&board); print_board(&board); copy_board(&board, &temp);

	for(fast = TRUE; fast >= FALSE; fast--) 
		for(smart = TRUE; smart >= FALSE; smart--) {

			printf("----------------------------------\n");

			steps = 0; copy_board(&temp, &board); finished = FALSE;	
			back_track(a, 0, &board);

			printf("It took %d steps to find this solution ", steps);
			printf("for fast=%d  smart=%d\n", fast, smart);
		}
	return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms$ ./sudoku < sudoku-examples/puzzle

There are 46 free board positions.
8  |   |32 |
 7 |3 4|968|
3  | 6 |5  |
-----------
   |831|4  |
4  | 9 |  2|
  1|425|   |
-----------
  8| 5 |  6|
123|6 7| 5 |
 57|   |  4|
-----------
----------------------------------
process solution

There are 0 free board positions.
864|579|321|
572|314|968|
319|268|547|
-----------
296|831|475|
435|796|182|
781|425|693|
-----------
948|152|736|
123|647|859|
657|983|214|
-----------
It took 47 steps to find this solution for fast=1  smart=1
----------------------------------
process solution

There are 0 free board positions.
864|579|321|
572|314|968|
319|268|547|
-----------
296|831|475|
435|796|182|
781|425|693|
-----------
948|152|736|
123|647|859|
657|983|214|
-----------
It took 47 steps to find this solution for fast=1  smart=0
----------------------------------
process solution

There are 0 free board positions.
864|579|321|
572|314|968|
319|268|547|
-----------
296|831|475|
435|796|182|
781|425|693|
-----------
948|152|736|
123|647|859|
657|983|214|
-----------
It took 56 steps to find this solution for fast=0  smart=1
----------------------------------
process solution

There are 0 free board positions.
864|579|321|
572|314|968|
319|268|547|
-----------
296|831|475|
435|796|182|
781|425|693|
-----------
948|152|736|
123|647|859|
657|983|214|
-----------
It took 1590 steps to find this solution for fast=0  smart=0
*/
