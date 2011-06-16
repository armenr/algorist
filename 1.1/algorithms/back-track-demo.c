/*see README for original credits */

#include<stdbool.h>
#include<stdio.h>
#include"back-track.h"
#include"back-track-funcs.h"
#include"../ds/graph1.h"
#include"graph-print.h"

static void paths_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0 - sentinel*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  insert_vertex(g); /*6*/
  
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 1, 3, 0);
  insert_edge(g, 1, 4, 0);
  insert_edge(g, 1, 5, 0);
  insert_edge(g, 2, 6, 0);
  insert_edge(g, 3, 6, 0);
  insert_edge(g, 4, 6, 0);
  insert_edge(g, 5, 6, 0);
  insert_edge(g, 3, 4, 0);
}

int main(void) {
  back_track_t b;

  printf("\n============\n");
  printf("Permutations");
  printf("\n============\n\n");

  b.process_solution = perm_process_solution;
  b.is_a_solution = perm_is_a_solution;
  b.construct_candidates = perm_construct_candidates;
  b.make_move = perm_make_move;
  b.unmake_move = perm_unmake_move;

  int i = 3;
  init_back_track(&b, i+1); 
	back_track(&b, 0, i, &i); 
  clear_back_track(&b);
  
  printf("\n=======\n");
  printf("Subsets");
  printf("\n=======\n\n");

  b.process_solution = subset_process_solution;
  b.is_a_solution = subset_is_a_solution;
  b.construct_candidates = subset_construct_candidates;
  b.make_move = subset_make_move;
  b.unmake_move = subset_unmake_move;

  i = 3;
  init_back_track(&b, i+1); 
	back_track(&b, 0, 2, &i);
  clear_back_track(&b);
  
  printf("\n======\n");
  printf("Sudoku");
  printf("\n======\n");

  b.process_solution = sudoku_process_solution;
  b.is_a_solution = sudoku_is_a_solution;
  b.construct_candidates = sudoku_construct_candidates;
  b.make_move = sudoku_make_move;
  b.unmake_move = sudoku_unmake_move;

	sudoku_game game;
  board_t temp;
  
	read_board(&temp); 
	print_board(&temp); 
  
  int f, s;
	for(f = 1; f >= 0; f--) 
  	for(s = 1; s >= 0; s--) {
	    printf("\n----------------------------------\n");

      game.fast = (bool)f;
      game.smart = (bool)s;
	    game.steps = 0; 
      copy_board(&temp, &(game.board));

      init_back_track(&b, NCELLS); 
	    back_track(&b, 0, DIMENSION+1, &game);
      clear_back_track(&b);

	    printf("It took %d steps to find this solution ", game.steps);
	    printf("for fast = %d smart = %d\n", game.fast, game.smart);
  	}
  
/*  printf("\n=====\n");*/
/*  printf("Paths");*/
/*  printf("\n=====\n\n");*/

/*  b.process_solution = paths_process_solution;*/
/*  b.is_a_solution = paths_is_a_solution;*/
/*  b.construct_candidates = paths_construct_candidates;*/
/*  b.make_move = paths_make_move;*/
/*  b.unmake_move = paths_unmake_move;*/
/*  */
/*  path_t p;*/
/*  paths_demo(&(p.g));*/
/*  print_graph(&(p.g), print_item);*/

/*  p.v = 3;*/
/*  init_back_track(&b, p.v); */
/*	back_track(&b, 0, p.v, &p);*/

/*  clear_back_track(&b);*/
/*  clear_graph(&(p.g));*/
	return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/algorithms$ make back-track-demo && valgrind --leak-check=yes -v ./back-track-demo < sudoku-examples/puzzle
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o back-track-demo.o back-track-demo.c
back-track-demo.c:10: warning: ‘paths_demo’ defined but not used
gcc -lm  -o back-track-demo back-track-demo.o back-track.o back-track-funcs.o \
	graph-print.o graph-search.o 	graph-vertex.o \
	../ds/graph1.o ../ds/list.o ../ds/queue.o ../ds/skip-list.o ../ds/stack.o
==23280== Memcheck, a memory error detector
==23280== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==23280== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==23280== Command: ./back-track-demo
==23280== 
--23280-- Valgrind options:
--23280--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--23280--    --leak-check=yes
--23280--    -v
--23280-- Contents of /proc/version:
--23280--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--23280-- Arch and hwcaps: X86, x86-sse1-sse2
--23280-- Page sizes: currently 4096, max supported 4096
--23280-- Valgrind library directory: /usr/lib/valgrind
--23280-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--23280-- Reading debug info from /lib/ld-2.11.1.so ..
--23280-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--23280-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--23280-- Reading syms from /home/osman/src/algorist/1.1/algorithms/back-track-demo (0x8048000)
--23280-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--23280--    object doesn't have a dynamic symbol table
--23280-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--23280-- Reading suppressions file: /usr/lib/valgrind/default.supp
--23280-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--23280-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--23280-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==23280== WARNING: new redirection conflicts with existing -- ignoring it
--23280--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--23280-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--23280-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--23280-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--23280-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--23280-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--23280-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--23280-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--23280-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--23280-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--23280-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--23280-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)

============
Permutations
============

--23280-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1 
--23280-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)

=======
Subsets
=======

{ 1 2 3 }
{ 1 2 }
{ 1 3 }
{ 1 }
{ 2 3 }
{ 2 }
{ 3 }
{ }

======
Sudoku
======

There are 46 free board positions.

-------------
|8  |   |32 |
| 7 |3 4|968|
|3  | 6 |5  |
-------------
|   |831|4  |
|4  | 9 |  2|
|  1|425|   |
-------------
|  8| 5 |  6|
|123|6 7| 5 |
| 57|   |  4|
-------------

----------------------------------
process solution

There are 0 free board positions.

-------------
|864|579|321|
|572|314|968|
|319|268|547|
-------------
|296|831|475|
|435|796|182|
|781|425|693|
-------------
|948|152|736|
|123|647|859|
|657|983|214|
-------------
It took 46 steps to find this solution for fast = 1 smart = 1

----------------------------------
process solution

There are 0 free board positions.

-------------
|864|579|321|
|572|314|968|
|319|268|547|
-------------
|296|831|475|
|435|796|182|
|781|425|693|
-------------
|948|152|736|
|123|647|859|
|657|983|214|
-------------
It took 46 steps to find this solution for fast = 1 smart = 0

----------------------------------
process solution

There are 0 free board positions.

-------------
|864|579|321|
|572|314|968|
|319|268|547|
-------------
|296|831|475|
|435|796|182|
|781|425|693|
-------------
|948|152|736|
|123|647|859|
|657|983|214|
-------------
It took 55 steps to find this solution for fast = 0 smart = 1

----------------------------------
process solution

There are 0 free board positions.

-------------
|864|579|321|
|572|314|968|
|319|268|547|
-------------
|296|831|475|
|435|796|182|
|781|425|693|
-------------
|948|152|736|
|123|647|859|
|657|983|214|
-------------
It took 1589 steps to find this solution for fast = 0 smart = 0
==23280== 
==23280== HEAP SUMMARY:
==23280==     in use at exit: 0 bytes in 0 blocks
==23280==   total heap usage: 6 allocs, 6 frees, 1,328 bytes allocated
==23280== 
==23280== All heap blocks were freed -- no leaks are possible
==23280== 
==23280== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--23280-- 
--23280-- used_suppression:     13 dl-hack3-cond-1
==23280== 
==23280== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

/*
osman@osman-dev:~/src/algorist/1.1/algorithms$ ./back-track-demo < datafiles/minimum1

======
Sudoku
======

There are 64 free board positions.

-------------
|   |   | 1 |
|4  |   |   |
| 2 |   |   |
-------------
|   | 5 |4 7|
|  8|   |3  |
|  1| 9 |   |
-------------
|3  |4  |2  |
| 5 |1  |   |
|   |8 6|   |
-------------

----------------------------------
process solution

There are 0 free board positions.

-------------
|693|784|512|
|487|512|936|
|125|963|874|
-------------
|932|651|487|
|568|247|391|
|741|398|625|
-------------
|319|475|268|
|856|129|743|
|274|836|159|
-------------
It took 4835 steps to find this solution for fast = 1 smart = 1

----------------------------------
process solution

There are 0 free board positions.

-------------
|693|784|512|
|487|512|936|
|125|963|874|
-------------
|932|651|487|
|568|247|391|
|741|398|625|
-------------
|319|475|268|
|856|129|743|
|274|836|159|
-------------
It took 4987327 steps to find this solution for fast = 1 smart = 0

----------------------------------
process solution

There are 0 free board positions.

-------------
|693|784|512|
|487|512|936|
|125|963|874|
-------------
|932|651|487|
|568|247|391|
|741|398|625|
-------------
|319|475|268|
|856|129|743|
|274|836|159|
-------------
It took 114209 steps to find this solution for fast = 0 smart = 1

----------------------------------

still going for fast = 0 smart = 0

*/
