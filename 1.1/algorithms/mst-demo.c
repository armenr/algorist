/*see README for original credits */

#include<stdio.h>
#include"kruskal.h"
#include"prim.h"

static void init_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  insert_vertex(g); /*6*/
  
  insert_edge(g, 0, 1, 12);
  insert_edge(g, 0, 4, 5);
  insert_edge(g, 0, 5, 7);
  insert_edge(g, 1, 2, 7);
  insert_edge(g, 1, 5, 4);
  insert_edge(g, 2, 3, 2);
  insert_edge(g, 2, 5, 3);
  insert_edge(g, 2, 6, 2);
  insert_edge(g, 3, 4, 7);
  insert_edge(g, 3, 5, 4);
  insert_edge(g, 3, 6, 5);
  insert_edge(g, 4, 5, 9);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

static void kruskal_test(graph* g, mst* m) {
  printf("\nkruskal mst\n");
  init_mst(m, g->nedges / 2);
  kruskal(g, m);
  print_mst(m);
  clear_mst(m);
}

static void prim_test(graph* g, mst* m) {
  int i;

  for(i = 0; i < g->nvertices; i++) {
	  printf("\nprim mst starting @ %d:\n", i);
	  init_mst(m, g->nvertices);
	  prim(g, i, m, prim_cost);
    print_mst(m);
	  clear_mst(m);
  }
}

static void sp_test(graph* g, mst* m) {
  int i;

  for(i = 0; i < g->nvertices; i++) {
	  printf("\nsp mst starting @ %d:\n", i);
	  init_mst(m, g->nvertices);
	  prim(g, i, m, sp_cost);
    print_sp(m, i);
	  clear_mst(m);
  }
}

int main(void) {
	graph g;
  init_demo(&g);    
	print_graph(&g, print_item);
	mst m;
	prim_test(&g, &m);
	sp_test(&g, &m);
	kruskal_test(&g, &m);
	clear_graph(&g);
  return 0;
}

/* test run 
see fig 6.3 pp 196 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 12 edges

                 *(3)
                          *(6)
                                                                        
                
       (4)*       *(5)    *(2)

                
        
            *         *                          
           (0)        (1)

osman@osman-dev:~/src/algorist/1.1/algorithms$ make mst-demo && valgrind --leak-check=yes -v ./mst-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o mst-demo.o mst-demo.c
mst-demo.c: In function ‘main’:
mst-demo.c:72: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o mst-demo mst-demo.o kruskal.o prim.o \
	../ds/graph1.o ../ds/mst.o ../ds/set-union.o ../ds/skip-list.o
==11291== Memcheck, a memory error detector
==11291== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==11291== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==11291== Command: ./mst-demo
==11291== 
--11291-- Valgrind options:
--11291--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--11291--    --leak-check=yes
--11291--    -v
--11291-- Contents of /proc/version:
--11291--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--11291-- Arch and hwcaps: X86, x86-sse1-sse2
--11291-- Page sizes: currently 4096, max supported 4096
--11291-- Valgrind library directory: /usr/lib/valgrind
--11291-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--11291-- Reading debug info from /lib/ld-2.11.1.so ..
--11291-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--11291-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--11291-- Reading syms from /home/osman/src/algorist/1.1/algorithms/mst-demo (0x8048000)
--11291-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--11291--    object doesn't have a dynamic symbol table
--11291-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--11291-- Reading suppressions file: /usr/lib/valgrind/default.supp
--11291-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--11291-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--11291-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==11291== WARNING: new redirection conflicts with existing -- ignoring it
--11291--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--11291-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--11291-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--11291-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--11291-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--11291-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--11291-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--11291-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--11291-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--11291-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--11291-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--11291-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--11291-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--11291-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--11291-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--11291-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--11291-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0 edges: 5 4 1 
node: 1 edges: 5 2 0 
node: 2 edges: 6 5 3 1 
node: 3 edges: 6 5 4 2 
node: 4 edges: 5 3 0 
node: 5 edges: 4 3 2 1 0 
node: 6 edges: 3 2 

prim mst starting @ 0:
--11291-- REDIR: 0x40d6930 (memset) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--11291-- REDIR: 0x4170ef0 (__memset_sse2) redirected to 0x4027420 (memset)
#1 edge: (5, 1) of weight 4 in MST
#2 edge: (3, 2) of weight 2 in MST
#3 edge: (4, 3) of weight 7 in MST
#4 edge: (0, 4) of weight 5 in MST
#5 edge: (2, 5) of weight 3 in MST
#6 edge: (2, 6) of weight 2 in MST
no edges: 6
total cost: 23

prim mst starting @ 1:
#0 edge: (5, 0) of weight 7 in MST
#2 edge: (5, 2) of weight 3 in MST
#3 edge: (2, 3) of weight 2 in MST
#4 edge: (0, 4) of weight 5 in MST
#5 edge: (1, 5) of weight 4 in MST
#6 edge: (2, 6) of weight 2 in MST
no edges: 6
total cost: 23

prim mst starting @ 2:
#0 edge: (5, 0) of weight 7 in MST
#1 edge: (5, 1) of weight 4 in MST
#3 edge: (2, 3) of weight 2 in MST
#4 edge: (0, 4) of weight 5 in MST
#5 edge: (2, 5) of weight 3 in MST
#6 edge: (2, 6) of weight 2 in MST
no edges: 6
total cost: 23

prim mst starting @ 3:
#0 edge: (5, 0) of weight 7 in MST
#1 edge: (5, 1) of weight 4 in MST
#2 edge: (3, 2) of weight 2 in MST
#4 edge: (0, 4) of weight 5 in MST
#5 edge: (2, 5) of weight 3 in MST
#6 edge: (2, 6) of weight 2 in MST
no edges: 6
total cost: 23

prim mst starting @ 4:
#0 edge: (4, 0) of weight 5 in MST
#1 edge: (5, 1) of weight 4 in MST
#2 edge: (3, 2) of weight 2 in MST
#3 edge: (4, 3) of weight 7 in MST
#5 edge: (2, 5) of weight 3 in MST
#6 edge: (2, 6) of weight 2 in MST
no edges: 6
total cost: 23

prim mst starting @ 5:
#0 edge: (5, 0) of weight 7 in MST
#1 edge: (5, 1) of weight 4 in MST
#2 edge: (5, 2) of weight 3 in MST
#3 edge: (2, 3) of weight 2 in MST
#4 edge: (0, 4) of weight 5 in MST
#6 edge: (2, 6) of weight 2 in MST
no edges: 6
total cost: 23

prim mst starting @ 6:
#0 edge: (5, 0) of weight 7 in MST
#1 edge: (5, 1) of weight 4 in MST
#2 edge: (6, 2) of weight 2 in MST
#3 edge: (2, 3) of weight 2 in MST
#4 edge: (0, 4) of weight 5 in MST
#5 edge: (2, 5) of weight 3 in MST
no edges: 6
total cost: 23

sp mst starting @ 0:
#1 path: (0, 1) of cost 11
#2 path: (0, 2) of cost 10
#3 path: (0, 3) of cost 11
#4 path: (0, 4) of cost 5
#5 path: (0, 5) of cost 7
#6 path: (0, 6) of cost 12

sp mst starting @ 1:
#0 path: (1, 0) of cost 11
#2 path: (1, 2) of cost 7
#3 path: (1, 3) of cost 8
#4 path: (1, 4) of cost 13
#5 path: (1, 5) of cost 4
#6 path: (1, 6) of cost 9

sp mst starting @ 2:
#0 path: (2, 0) of cost 10
#1 path: (2, 1) of cost 7
#3 path: (2, 3) of cost 2
#4 path: (2, 4) of cost 9
#5 path: (2, 5) of cost 3
#6 path: (2, 6) of cost 2

sp mst starting @ 3:
#0 path: (3, 0) of cost 11
#1 path: (3, 1) of cost 8
#2 path: (3, 2) of cost 2
#4 path: (3, 4) of cost 7
#5 path: (3, 5) of cost 4
#6 path: (3, 6) of cost 4

sp mst starting @ 4:
#0 path: (4, 0) of cost 5
#1 path: (4, 1) of cost 13
#2 path: (4, 2) of cost 9
#3 path: (4, 3) of cost 7
#5 path: (4, 5) of cost 9
#6 path: (4, 6) of cost 11

sp mst starting @ 5:
#0 path: (5, 0) of cost 7
#1 path: (5, 1) of cost 4
#2 path: (5, 2) of cost 3
#3 path: (5, 3) of cost 4
#4 path: (5, 4) of cost 9
#6 path: (5, 6) of cost 5

sp mst starting @ 6:
#0 path: (6, 0) of cost 12
#1 path: (6, 1) of cost 9
#2 path: (6, 2) of cost 2
#3 path: (6, 3) of cost 4
#4 path: (6, 4) of cost 11
#5 path: (6, 5) of cost 5

kruskal mst
#0 edge: (2, 6) of weight 2 in MST
#1 edge: (2, 3) of weight 2 in MST
#2 edge: (2, 5) of weight 3 in MST
#3 edge: (1, 5) of weight 4 in MST
#5 edge: (0, 4) of weight 5 in MST
#7 edge: (0, 5) of weight 7 in MST
no edges: 7
total cost: 23
==11291== 
==11291== HEAP SUMMARY:
==11291==     in use at exit: 0 bytes in 0 blocks
==11291==   total heap usage: 128 allocs, 128 frees, 2,884 bytes allocated
==11291== 
==11291== All heap blocks were freed -- no leaks are possible
==11291== 
==11291== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--11291-- 
--11291-- used_suppression:     13 dl-hack3-cond-1
==11291== 
==11291== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

