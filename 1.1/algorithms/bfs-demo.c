/*see README for original credits */

#include"bfs-dfs.h"
#include<stdio.h>

void process_vertex_early(int v) {
  printf("processed vertex %d\n", v);
}

void process_vertex_late(int v) {
}

void process_edge(int x, int y) {
  printf("processed edge (%d,%d)\n", x, y);
}

static void init_graph(graph* g) {
  initialize_graph(g, false);

  /*refer to graph diagram below for structure*/
  char c = 'a';
  int v = insert_vertex(g, &c, sizeof (char));  /*0*/
  c = 'b';
  v = insert_vertex(g, &c, sizeof (char));  /*1*/
  insert_edge(g, 0, v, 0);
  c = 'e';
  v = insert_vertex(g, &c, sizeof (char));  /*2*/
  insert_edge(g, 0, v, 0);
  insert_edge(g, 1, v, 0);
  c = 'f';
  v = insert_vertex(g, &c, sizeof (char));  /*3*/
  insert_edge(g, 0, v, 0);
  c = 'c';
  v = insert_vertex(g, &c, sizeof (char));  /*4*/
  insert_edge(g, 1, v, 0);
  c = 'd';
  v = insert_vertex(g, &c, sizeof (char));  /*5*/
  insert_edge(g, 4, v, 0);
  insert_edge(g, 2, v, 0);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

static void print_bfs(graph* g) {
  int i;

  for(i = 0; i < g->nvertices; i++)
    printf(" %d", parent[i]);
  printf("\n");

  for(i = 0; i < g->nvertices; i++)
    find_path(0, i, parent);
  printf("\n");
}

int main(void) {
  graph g;
  init_graph(&g);
  print_graph(&g, print_item);
  initialize_search(&g);
  bfs(&g, 0);
  print_bfs(&g);
  clear_search();
  clear_graph(&g);
  return 0;
}

/*
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

6 vertices, 7 edges

               *
              (0)
                        
              
       *       *      *
      (1)     (2)    (3)


       *       *
      (4)     (5)

osman@osman-dev:~/src/algorist/1.1/algorithms$ make bfs-demo && valgrind --leak-check=yes -v ./bfs-demo 
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o bfs-dfs.o bfs-dfs.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o bfs-demo.o bfs-demo.c
bfs-demo.c: In function ‘process_vertex_late’:
bfs-demo.c:11: warning: unused parameter ‘v’
bfs-demo.c: In function ‘main’:
bfs-demo.c:62: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:44: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o bfs-demo bfs-dfs.o bfs-demo.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o ../ds/skip-list.o
==29546== Memcheck, a memory error detector
==29546== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==29546== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==29546== Command: ./bfs-demo
==29546== 
--29546-- Valgrind options:
--29546--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--29546--    --leak-check=yes
--29546--    -v
--29546-- Contents of /proc/version:
--29546--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--29546-- Arch and hwcaps: X86, x86-sse1-sse2
--29546-- Page sizes: currently 4096, max supported 4096
--29546-- Valgrind library directory: /usr/lib/valgrind
--29546-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--29546-- Reading debug info from /lib/ld-2.11.1.so ..
--29546-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--29546-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--29546-- Reading syms from /home/osman/src/algorist/1.1/algorithms/bfs-demo (0x8048000)
--29546-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--29546--    object doesn't have a dynamic symbol table
--29546-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--29546-- Reading suppressions file: /usr/lib/valgrind/default.supp
--29546-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--29546-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--29546-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==29546== WARNING: new redirection conflicts with existing -- ignoring it
--29546--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--29546-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--29546-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--29546-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--29546-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--29546-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--29546-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--29546-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--29546-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--29546-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--29546-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--29546-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--29546-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--29546-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--29546-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--29546-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--29546-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0  value: a edges: 3 2 1 
node: 1  value: b edges: 4 2 0 
node: 2  value: e edges: 5 1 0 
node: 3  value: f edges: 0 
node: 4  value: c edges: 5 1 
node: 5  value: d edges: 2 4 
processed vertex 0
processed edge (0,3)
processed edge (0,2)
processed edge (0,1)
processed vertex 3
processed vertex 2
processed edge (2,5)
processed edge (2,1)
processed vertex 1
processed edge (1,4)
processed vertex 5
processed edge (5,4)
processed vertex 4
 -1 0 0 0 1 2

0
0 1
0 2
0 3
0 1 4
0 2 5
==29546== 
==29546== HEAP SUMMARY:
==29546==     in use at exit: 0 bytes in 0 blocks
==29546==   total heap usage: 79 allocs, 79 frees, 822 bytes allocated
==29546== 
==29546== All heap blocks were freed -- no leaks are possible
==29546== 
==29546== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--29546-- 
--29546-- used_suppression:     13 dl-hack3-cond-1
==29546== 
==29546== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
