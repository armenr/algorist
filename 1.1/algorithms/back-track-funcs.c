/*see README for original credits */

#include<stdio.h>
#include"back-track-funcs.h"
#include"../ds/graph1.h"

void paths_process_solution(back_track_t* b, int k, void* input) {
  int i;

  printf("{ ");
  for(i = 1; i <= k; i++)
    printf("%d ", b->solution[i]);
  printf(" }\n");
}

bool paths_is_a_solution(const back_track_t* b, int k, void* input) {
  int n = ((path_t*)input)->v;
	return b->solution[k] == n;
}

void paths_make_move(back_track_t* b, int k, void* input) {
}

void paths_unmake_move(back_track_t* b, int k, void* input) {
}

/*	What are possible elements of the next slot in the path
*/

void paths_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {

	bool in_sol[b->sol_sz];	
  int i;
  
	for(i = 1; i < b->sol_sz; i++) 
	  in_sol[i] = false;

	for(i = 1; i < k; i++) 
	  in_sol[b->solution[i]] = true;
	  
  if(k == 1) {
/*printf("init k = 1\n");*/
    c[0] = 1;
    *ncandidates = 1;

  } else	{
    *ncandidates = 0;
    int last = b->solution[k-1];
    
    const graph g = ((path_t*)input)->g;
    const vertex* v = find_vertex(&g, last);
    const edge_node* p = v->edges;

    /*build candidate list from adjacent vertices in list*/
    while(p != NULL) {
/*printf("%d %d %d\n", last, p->y, *ncandidates);    */
      if(!in_sol[p->y]) {
/*        c[*ncandidates] = p->y;*/
        *(ncandidates)++;
      }

      p = p->next;
    }
  }
}

/*
================================================================================
*/

void perm_process_solution(back_track_t* b, int k, void* input) {
	int i;

	for(i = 1; i <= k; i++) 
	  printf("%d ", b->solution[i]);
	printf("\n");
}

bool perm_is_a_solution(const back_track_t* b, int k, void* input) {
	return k == *(int*)input;
}

void perm_make_move(back_track_t* b, int k, void* input) {
}

void perm_unmake_move(back_track_t* b, int k, void* input){
}

/*	What are possible elements of the next slot in the permutation?  */
void perm_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {
	
	bool in_perm[b->sol_sz];		/* what is now in the permutation? */
  int i;
  
  /*create bitset for existing permutation members*/
	for(i = 1; i < b->sol_sz; i++) 
	  in_perm[i] = false;

	for(i = 1; i < k; i++) 
	  in_perm[b->solution[i]] = true;

  int n = *(int*)input;
	*ncandidates = 0;

  /*build list of candidates for next position*/
	for(i = 1; i <= n; i++) 
		if(!in_perm[i]) {
			c[*ncandidates] = i;
			(*ncandidates)++;
		}
}

/*
================================================================================
*/

void subset_process_solution(back_track_t* b, int k, void* input) {
	int i;

	printf("{");
	for(i = 1; i <= k; i++)
		if(b->solution[i]) 
		  printf(" %d", i);

	printf(" }\n");
}

bool subset_is_a_solution(const back_track_t* b, int k, void* input) {
	return k == *(int*)input;
}

void subset_make_move(back_track_t* b, int k, void* input) {
}

void subset_unmake_move(back_track_t* b, int k, void* input){
}

/*	What are possible elements of the next slot in the permutation?  */
void subset_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {
	
	c[0] = true; 
	c[1] = false; 
  *ncandidates = 2; /* next position candidate count */
}

/*
================================================================================
*/

static void init_board(board_t*  board);

static void fill_square(board_t* board, int x, int y, int v);
static void free_square(board_t* board, int x, int y);
static void next_square(const sudoku_game* game, int* x, int* y);

static int possible_values(const board_t* board, bool possible[], 
  int x, int y);
/*static void print_possible(bool possible[]);*/

void sudoku_process_solution(back_track_t* b, int k, void* input) {
	b->finished = true;
  printf("process solution\n");
  board_t board = ((sudoku_game*)input)->board;
	print_board(&board);
}

bool sudoku_is_a_solution(const back_track_t* b, int k, void* input) {
  board_t board = ((sudoku_game*)input)->board;
	if(board.freecount == EMPTY) 
		return true;

	return false;
}

void sudoku_make_move(back_track_t* b, int k, void* input) {
  board_t board = ((sudoku_game*)input)->board;
	fill_square(&(((sudoku_game*)input)->board), board.move[k].x, board.move[k].y, 
	  b->solution[k]);
}

void sudoku_unmake_move(back_track_t* b, int k, void* input) {
  board_t board = ((sudoku_game*)input)->board;
	free_square(&(((sudoku_game*)input)->board), board.move[k].x, board.move[k].y);
}

void sudoku_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {

  sudoku_game* g = (sudoku_game*)input;
  g->steps++;

	int x, y;			/* position of next move */
  /* which square should we fill next? */
	next_square(g, &x, &y);	
	*ncandidates = 0;

	if(x == NONE && y == NONE) 
	  return;	/* error condition, no moves possible */

	bool possible[DIMENSION+1];     /* what is possible for the square? */
  if(!possible_values(&(g->board), possible, x, y))
    return;

  /* store our choice of next position */
	g->board.move[k].x = x;
	g->board.move[k].y = y;

  int i;

	for(i = 1; i <= DIMENSION; i++)
    if(possible[i]) {
			c[*ncandidates] = i;
			(*ncandidates)++;
		}
}

void copy_board(const board_t* a, board_t* b) {
	b->freecount = a->freecount;

	int i, j;

	for(i = 0; i < DIMENSION; i++)
		for(j = 0; j < DIMENSION; j++)
			b->m[i][j] = a->m[i][j];
}

void print_board(const board_t* board) {
	printf("\nThere are %d free board positions.\n\n", board->freecount);

	int i, j;

	for(i = 0; i < DIMENSION+BASED+1; i++) 
	  printf("-");
  printf("\n");
  
	for(i = 0; i < DIMENSION; i++) {
	  printf("|");
		for(j = 0; j < DIMENSION; j++) {

			if(board->m[i][j] == EMPTY)
				printf(" ");
			else
				printf("%d", board->m[i][j]);
				
			if((j+1) % BASED == 0)
				printf("|");
		}
		
		printf("\n");

		if((i+1) % BASED == 0) {
			for(j = 0; j < (DIMENSION+BASED+1); j++)
				printf("-");

			printf("\n");
		}
	}
}

void read_board(board_t*  board) {
	init_board(board);

	int i, j;

	for(i = 0; i < DIMENSION; i++) {
    for(j = 0; j < DIMENSION; j++) {
    	char c;
			scanf("%c", &c);
			int v = (int) (c - '0');

			if(v != EMPTY)
				fill_square(board, i, j, v);
		}
		scanf("\n"); 
	}
}

static void init_board(board_t*  board) {
	int i, j;

	for(i = 0; i < DIMENSION; i++)
		for(j = 0; j < DIMENSION; j++)
			board->m[i][j] = EMPTY;

	board->freecount = DIMENSION * DIMENSION;
}

static int possible_values(const board_t* board, bool possible[], 
  int x, int y) {
  
  /*check square is empty or not invalid*/
	if(board->m[x][y] != EMPTY || x < 0 || y < 0)
    return 0;

  int i;
  
  for(i = 1; i <= DIMENSION; i++) 
    possible[i] = true;
    
	for(i = 0; i < DIMENSION; i++) {
    /*check row of x*/
	  int square = board->m[x][i];
		if(square != EMPTY) 
		  possible[square] = false;

    /*check column of y*/
    square = board->m[i][y];
	  if(square != EMPTY) 
	    possible[square] = false;
	}

  /*(xlow, ylow) top left origin of 3x3 containing sector*/
	int xlow = BASED * (x / BASED);	
	int ylow = BASED * (y / BASED);
  int j;
  
  /*check sector*/
	for(i = xlow; i < xlow+BASED; i++)
		for(j = ylow; j < ylow+BASED; j++) {
	    int square = board->m[i][j];
		  if(square != EMPTY) 
		    possible[square] = false;
		}

  int c = 0;
  
  for(i = 1; i <= DIMENSION; i++) 
    if(possible[i])
      c++;
  
	return c;
}

/*static void print_possible(bool possible[]) {*/
/*	int i;*/

/*	for(i = 1; i <= DIMENSION; i++)*/
/*		if(possible[i]) */
/*		  printf("%d ", i);*/
/*	printf("\n");*/
/*}*/

static void fill_square(board_t* board, int x, int y, int v) {
	if(board->m[x][y] == EMPTY)
		board->freecount--;
	else
		printf("Warning: filling already filled square (%d,%d)\n", x, y);

	board->m[x][y] = v;
}

static void free_square(board_t* board, int x, int y) {
	if(board->m[x][y] != EMPTY)
		board->freecount++;
	else
		printf("Warning: freeing already empty square (%d,%d)\n", x, y);

	board->m[x][y] = EMPTY;
}

static void next_square(const sudoku_game* game, int* x, int* y) {
  const board_t board = game->board;
	int bestcnt = DIMENSION+1; 
	int i, j;

	*x = *y = NONE;

	for(i = 0; i < DIMENSION; i++) 
		for(j = 0; j < DIMENSION; j++) {
	  	bool possible[DIMENSION+1];     /* what is possible for the square? */
  		int newcnt = possible_values(&board, possible, i, j);

			if(newcnt > 0) {
	      if(game->fast) {
    			if(newcnt < bestcnt) {  /*pick most constrained square*/
			      *x = i; 
			      *y = j;
			      bestcnt = newcnt; 
		      }
		      
	      } else if(board.m[i][j] == EMPTY) { /*slow*/
		      *x = i; 
		      *y = j;
	      }

      } else  /*no possible moves*/
        if(board.m[i][j] == EMPTY && game->smart) {
          /*initialize to non-position */
		      *x = *y = NONE;
		      return;
        }
		}
}
