/*see README for original credits */

#include"graph-search.h"
#include"../ds/graph.h"
#include<stdio.h>

void process_vertex_early(graph_search* gs, int v) {
}
void process_vertex_late(graph_search* gs, int v) {
}
void process_edge(graph_search* gs, int x, int y) {
}

static void init_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  char c = 'a';
  insert_vertex(g, &c, sizeof(char)); /*0*/
  c = 'b';
  insert_vertex(g, &c, sizeof(char)); /*1*/
  c = 'c';
  insert_vertex(g, &c, sizeof(char)); /*2*/
  c = 'd';
  insert_vertex(g, &c, sizeof(char)); /*3*/
  c = 'e';
  insert_vertex(g, &c, sizeof(char)); /*4*/
  c = 'f';
  insert_vertex(g, &c, sizeof(char)); /*5*/
  c = 'g';
  insert_vertex(g, &c, sizeof(char)); /*6*/
  
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

static void init_demo2(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  char c = 'a';
  insert_vertex(g, &c, sizeof(char)); /*0*/
  c = 'b';
  insert_vertex(g, &c, sizeof(char)); /*1*/
  c = 'c';
  insert_vertex(g, &c, sizeof(char)); /*2*/
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 0, 2, 0);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

static void print_colors(const graph* g, const graph_search* gs) {
  int i;
	for(i = 0; i < g->nvertices; i++)
    printf("vertex %d color %d\n", i, gs->color[i]);
  printf("graph two colored is %s\n\n", (gs->bipartite) ? "TRUE" : "FALSE");    
}

int main(void) {
  graph g;
  graph_search gs;

  init_demo(&g);
  print_graph(&g, print_item);
  init_search(&g, &gs);
  twocolor(&g, &gs);
  print_colors(&g, &gs);
  clear_search(&gs);
  clear_graph(&g);

  init_demo2(&g);
  print_graph(&g, print_item);
  init_search(&g, &gs);
  twocolor(&g, &gs);
  print_colors(&g, &gs);
  clear_search(&gs);
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

osman@osman-dev:~/src/algorist/1.1/algorithms$ make bi-partite && valgrind --leak-check=yes -v ./bi-partite
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-search.o graph-search.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o bi-partite.o bi-partite.c
bi-partite.c: In function ‘process_vertex_early’:
bi-partite.c:7: warning: unused parameter ‘gs’
bi-partite.c:7: warning: unused parameter ‘v’
bi-partite.c: In function ‘process_vertex_late’:
bi-partite.c:9: warning: unused parameter ‘gs’
bi-partite.c:9: warning: unused parameter ‘v’
bi-partite.c: In function ‘process_edge’:
bi-partite.c:11: warning: unused parameter ‘gs’
bi-partite.c:11: warning: unused parameter ‘x’
bi-partite.c:11: warning: unused parameter ‘y’
bi-partite.c: In function ‘main’:
bi-partite.c:78: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:43: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
bi-partite.c:86: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:43: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o bi-partite graph-search.o bi-partite.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o ../ds/skip-list.o
==5200== Memcheck, a memory error detector
==5200== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==5200== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==5200== Command: ./bi-partite
==5200== 
--5200-- Valgrind options:
--5200--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--5200--    --leak-check=yes
--5200--    -v
--5200-- Contents of /proc/version:
--5200--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--5200-- Arch and hwcaps: X86, x86-sse1-sse2
--5200-- Page sizes: currently 4096, max supported 4096
--5200-- Valgrind library directory: /usr/lib/valgrind
--5200-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--5200-- Reading debug info from /lib/ld-2.11.1.so ..
--5200-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--5200-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--5200-- Reading syms from /home/osman/src/algorist/1.1/algorithms/bi-partite (0x8048000)
--5200-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--5200--    object doesn't have a dynamic symbol table
--5200-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--5200-- Reading suppressions file: /usr/lib/valgrind/default.supp
--5200-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--5200-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--5200-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==5200== WARNING: new redirection conflicts with existing -- ignoring it
--5200--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--5200-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--5200-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--5200-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--5200-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--5200-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--5200-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--5200-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--5200-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--5200-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--5200-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--5200-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--5200-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--5200-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--5200-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--5200-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--5200-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0  value: a edges: 5 4 1 
node: 1  value: b edges: 5 2 0 
node: 2  value: c edges: 6 5 3 1 
node: 3  value: d edges: 6 5 4 2 
node: 4  value: e edges: 5 3 0 
node: 5  value: f edges: 4 3 2 1 0 
node: 6  value: g edges: 3 2 
vertex 0 color 1
vertex 1 color 1
vertex 2 color 1
vertex 3 color 2
vertex 4 color 1
vertex 5 color 2
vertex 6 color 2
graph two colored is FALSE

node: 0  value: a edges: 2 1 
node: 1  value: b edges: 0 
node: 2  value: c edges: 0 
vertex 0 color 1
vertex 1 color 2
vertex 2 color 2
graph two colored is TRUE

==5200== 
==5200== HEAP SUMMARY:
==5200==     in use at exit: 0 bytes in 0 blocks
==5200==   total heap usage: 150 allocs, 150 frees, 1,638 bytes allocated
==5200== 
==5200== All heap blocks were freed -- no leaks are possible
==5200== 
==5200== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--5200-- 
--5200-- used_suppression:     13 dl-hack3-cond-1
==5200== 
==5200== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
