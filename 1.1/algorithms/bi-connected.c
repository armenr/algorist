/*see README for original credits */

#include"graph-search.h"
#include"../ds/graph.h"
#include<stdio.h>

void process_vertex_early(graph_search* gs, int v) {
  gs->reachable_ancestor[v] = v;
}

void process_vertex_late(graph_search* gs, int v) {
  if(gs->parent[v] < 1) { /* test if v is the root */
    if(gs->tree_out_degree[v] > 1)
      printf("root articulation vertex: %d \n", v);
    return;
  }

  /* is a given vertex the root of the DFS tree? */
  bool root = gs->parent[gs->parent[v]] < 1; /* test if parent[v] is root */
  if(gs->reachable_ancestor[v] == gs->parent[v] && root)
    printf("parent articulation vertex: %d \n", gs->parent[v]);

  if(gs->reachable_ancestor[v] == v) {
    printf("bridge articulation vertex: %d \n", gs->parent[v]);

    if(gs->tree_out_degree[v] > 0) /* test if v is not a leaf */
      printf("bridge articulation vertex: %d \n", v);
  }

  /* earliest reachable time for v */
  int time_v = gs->entry_time[gs->reachable_ancestor[v]];
  /* earliest reachable time for parent[v] */
  int time_parent = gs->entry_time[gs->reachable_ancestor[gs->parent[v]]];

  if(time_v < time_parent)
    gs->reachable_ancestor[gs->parent[v]] = gs->reachable_ancestor[v];
}

void process_edge(graph_search* gs, int x, int y) {
  int class = edge_classification(gs, x, y);

  if(class == TREE)
    gs->tree_out_degree[x]++;

  if(class == BACK && gs->parent[x] != y) 
    if(gs->entry_time[y] < gs->entry_time[gs->reachable_ancestor[x]])
      gs->reachable_ancestor[x] = y;
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
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 0, 5, 0);
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 2, 3, 0);
  insert_edge(g, 3, 4, 0);
  insert_edge(g, 4, 1, 0);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
  graph g;
  init_demo(&g);
  print_graph(&g, print_item);
  graph_search gs;
  init_search(&g, &gs);
  articulation_vertices(&g, &gs);
  clear_search(&gs);
  clear_graph(&g);
  return 0;
}

/* test run 
see fig 5.12 pp 174 "The Algorithm Design Manual" by Steve S. Skiena

          0

        T   T

  B   1        5

  B   T

  B   2

  B   T

  B   3

  B   T

  B   4
      
osman@osman-dev:~/src/algorist/1.1/algorithms$ make bi-connected && valgrind --leak-check=yes -v ./bi-connected
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-search.o graph-search.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o bi-connected.o bi-connected.c
bi-connected.c: In function ‘main’:
bi-connected.c:82: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:43: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o bi-connected graph-search.o bi-connected.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o ../ds/skip-list.o
==14911== Memcheck, a memory error detector
==14911== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==14911== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==14911== Command: ./bi-connected
==14911== 
--14911-- Valgrind options:
--14911--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--14911--    --leak-check=yes
--14911--    -v
--14911-- Contents of /proc/version:
--14911--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--14911-- Arch and hwcaps: X86, x86-sse1-sse2
--14911-- Page sizes: currently 4096, max supported 4096
--14911-- Valgrind library directory: /usr/lib/valgrind
--14911-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--14911-- Reading debug info from /lib/ld-2.11.1.so ..
--14911-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--14911-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--14911-- Reading syms from /home/osman/src/algorist/1.1/algorithms/bi-connected (0x8048000)
--14911-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--14911--    object doesn't have a dynamic symbol table
--14911-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--14911-- Reading suppressions file: /usr/lib/valgrind/default.supp
--14911-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--14911-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--14911-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==14911== WARNING: new redirection conflicts with existing -- ignoring it
--14911--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--14911-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--14911-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--14911-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--14911-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--14911-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--14911-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--14911-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--14911-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--14911-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--14911-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--14911-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--14911-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--14911-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--14911-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--14911-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--14911-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0  value: a edges: 5 1 
node: 1  value: b edges: 4 2 0 
node: 2  value: c edges: 3 1 
node: 3  value: d edges: 4 2 
node: 4  value: e edges: 1 3 
node: 5  value: f edges: 0 
parent articulation vertex: 1 
root articulation vertex: 0 
==14911== 
==14911== HEAP SUMMARY:
==14911==     in use at exit: 0 bytes in 0 blocks
==14911==   total heap usage: 67 allocs, 67 frees, 774 bytes allocated
==14911== 
==14911== All heap blocks were freed -- no leaks are possible
==14911== 
==14911== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--14911-- 
--14911-- used_suppression:     13 dl-hack3-cond-1
==14911== 
==14911== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
