/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include"heuristics.h"
#include"random.h"
#include"tsp.h"

int main(void) {
	tsp_instance t;			/* tsp points */
	tsp_solution s;			/* tsp solution */

	read_tsp(&t);
	read_solution(&s);
	printf("OPTIMAL SOLUTION COST = %7.1f\n", tsp_solution_cost(&s, &t));
  print_solution(&s);

	tsp_initialize_solution(&s, t.n);
	printf("solution_cost = %7.1f\n", tsp_solution_cost(&s, &t));
	print_solution(&s);
	
  heuristic h;

  h.copy_solution = tsp_copy_solution;
  /*initialization depends on init function being set first*/
  h.initialize_solution = tsp_initialize_solution;
  h.random_solution = tsp_random_solution;
  h.solution_cost = tsp_solution_cost;
  h.transition = tsp_transition;

  init_heuristic(&h, t.n, 1500000, sizeof(s));  
	repeated_heuristic(&t, &h, random_sampling);
  printf("random sampling %d iterations, cost = %7.1f\n",
    h.solution_count, h.solution_cost(h.best_solution, &t));
  print_solution(h.best_solution);
  clear_heuristic(&h);  

  init_heuristic(&h, t.n, 3, sizeof(s));  
	repeated_heuristic(&t, &h, anneal);
	printf("repeated annealing %d iterations, cost = %7.1f\n", 
    h.solution_count, h.solution_cost(h.best_solution, &t));
  print_solution(h.best_solution);
  clear_heuristic(&h);  

  init_heuristic(&h, t.n, 200, sizeof(s));  
	repeated_heuristic(&t, &h, hill_climbing);
	printf("repeated hill climbing %d iterations, cost = %7.1f\n", 
    h.solution_count, h.solution_cost(h.best_solution, &t));
  print_solution(h.best_solution);
  clear_heuristic(&h);  

  return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/algorithms$ make heuristics-demo && valgrind --leak-check=yes -v ./heuristics-demo < datafiles/tsp48
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o heuristics-demo.o heuristics-demo.c
gcc -lm  -o heuristics-demo heuristics-demo.o heuristics.o random.o tsp.o 
==16888== Memcheck, a memory error detector
==16888== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==16888== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==16888== Command: ./heuristics-demo
==16888== 
--16888-- Valgrind options:
--16888--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--16888--    --leak-check=yes
--16888--    -v
--16888-- Contents of /proc/version:
--16888--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--16888-- Arch and hwcaps: X86, x86-sse1-sse2
--16888-- Page sizes: currently 4096, max supported 4096
--16888-- Valgrind library directory: /usr/lib/valgrind
--16888-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--16888-- Reading debug info from /lib/ld-2.11.1.so ..
--16888-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--16888-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--16888-- Reading syms from /home/osman/src/algorist/1.1/algorithms/heuristics-demo (0x8048000)
--16888-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--16888--    object doesn't have a dynamic symbol table
--16888-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--16888-- Reading suppressions file: /usr/lib/valgrind/default.supp
--16888-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--16888-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--16888-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==16888== WARNING: new redirection conflicts with existing -- ignoring it
--16888--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--16888-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--16888-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--16888-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--16888-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--16888-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--16888-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--16888-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--16888-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--16888-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--16888-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--16888-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
--16888-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)
OPTIMAL SOLUTION COST = 33523.7
 1 8 38 31 44 18 7 28 6 37 19 27 17 43 30 36 46 33 20 47 21 32 39 48 5 42 24 10 45 35 4 26 2 29 34 41 16 22 3 23 14 25 13 11 12 15 40 9
------------------------------------------------------
solution_cost = 157530.2
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48
------------------------------------------------------
--16888-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--16888-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
random sampling 1500000 iterations, cost = 98566.0
 25 14 3 34 39 35 32 44 17 8 12 33 7 16 24 2 26 42 4 45 40 36 20 18 19 37 6 46 1 41 22 28 9 47 15 23 38 31 21 10 13 30 43 27 11 29 5 48
------------------------------------------------------
repeated annealing 1500000 iterations, cost = 45730.1
 10 41 16 40 46 31 38 9 8 1 22 3 34 14 23 11 15 33 12 13 25 48 5 29 2 4 26 42 39 21 47 44 18 7 30 43 17 27 19 37 6 28 36 20 32 24 45 35
------------------------------------------------------
repeated hill climbing 1540848 iterations, cost = 39953.1
 47 21 13 14 34 41 16 22 3 25 39 32 48 5 42 24 10 45 35 4 26 2 29 43 17 27 19 37 6 30 28 7 18 36 46 15 12 11 23 40 1 8 9 38 31 44 33 20
------------------------------------------------------
==16888== 
==16888== HEAP SUMMARY:
==16888==     in use at exit: 0 bytes in 0 blocks
==16888==   total heap usage: 1,500,206 allocs, 1,500,206 frees, 6,012,825,648 bytes allocated
==16888== 
==16888== All heap blocks were freed -- no leaks are possible
==16888== 
==16888== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--16888-- 
--16888-- used_suppression:     13 dl-hack3-cond-1
==16888== 
==16888== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
