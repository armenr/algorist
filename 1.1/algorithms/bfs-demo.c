/*see README for original credits */

#include"graph-search.h"
#include<stdio.h>

void process_vertex_early(graph_search* gs, int v) {
  printf("processed vertex %d\n", v);
}

void process_vertex_late(graph_search* gs, int v) {
}

void process_edge(graph_search* gs, int x, int y) {
  printf("processed edge (%d,%d)\n", x, y);
}

static void init_demo(graph* g) {
  init_graph(g, false);

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

static void print_bfs(const graph* g, graph_search* gs) {
  int i;

  for(i = 0; i < g->nvertices; i++)
    printf("%d ", gs->parent[i]);
  printf("\n");

  for(i = 0; i < g->nvertices; i++) {
    find_path(g, gs, 0, i);

    int j;
    for(j = 0; j < g->nvertices; j++) {
      int v = gs->path[j];
      if(v == NONE)
        break;
      printf("%d ", v);
    }
    
    printf("\n");
  }
}

int main(void) {
  graph g;
  init_demo(&g);
  print_graph(&g, print_item);
  graph_search gs;
  init_search(&g, &gs);
  bfs(&g, &gs, 0);
  print_bfs(&g, &gs);
  clear_search(&gs);
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
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-search.o graph-search.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o bfs-demo.o bfs-demo.c
bfs-demo.c: In function ‘process_vertex_early’:
bfs-demo.c:6: warning: unused parameter ‘gs’
bfs-demo.c: In function ‘process_vertex_late’:
bfs-demo.c:10: warning: unused parameter ‘gs’
bfs-demo.c:10: warning: unused parameter ‘v’
bfs-demo.c: In function ‘process_edge’:
bfs-demo.c:13: warning: unused parameter ‘gs’
bfs-demo.c: In function ‘main’:
bfs-demo.c:71: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:43: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o bfs-demo graph-search.o bfs-demo.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o ../ds/skip-list.o
==3051== Memcheck, a memory error detector
==3051== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==3051== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==3051== Command: ./bfs-demo
==3051== 
--3051-- Valgrind options:
--3051--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--3051--    --leak-check=yes
--3051--    -v
--3051-- Contents of /proc/version:
--3051--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--3051-- Arch and hwcaps: X86, x86-sse1-sse2
--3051-- Page sizes: currently 4096, max supported 4096
--3051-- Valgrind library directory: /usr/lib/valgrind
--3051-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--3051-- Reading debug info from /lib/ld-2.11.1.so ..
--3051-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--3051-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--3051-- Reading syms from /home/osman/src/algorist/1.1/algorithms/bfs-demo (0x8048000)
--3051-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--3051--    object doesn't have a dynamic symbol table
--3051-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--3051-- Reading suppressions file: /usr/lib/valgrind/default.supp
--3051-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--3051-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--3051-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==3051== WARNING: new redirection conflicts with existing -- ignoring it
--3051--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--3051-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--3051-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--3051-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--3051-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--3051-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--3051-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--3051-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--3051-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--3051-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--3051-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--3051-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--3051-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--3051-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--3051-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--3051-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--3051-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
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
==3051== 
==3051== HEAP SUMMARY:
==3051==     in use at exit: 0 bytes in 0 blocks
==3051==   total heap usage: 83 allocs, 83 frees, 918 bytes allocated
==3051== 
==3051== All heap blocks were freed -- no leaks are possible
==3051== 
==3051== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--3051-- 
--3051-- used_suppression:     13 dl-hack3-cond-1
==3051== 
==3051== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/ 
