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
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 2, 3, 0);
  insert_edge(g, 2, 4, 0);
  insert_edge(g, 2, 5, 0);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

static void print_components(const graph* g, const graph_search* gs) {
  int i;
  for(i = 0; i < g->nvertices; i++)
    printf("vertex %d in component %d\n", i, gs->component[i]);
}

int main(void) {
  graph g;
  init_demo(&g);
  print_graph(&g, print_item);
  graph_search gs;
  init_search(&g, &gs);
  connected_components(&g, &gs);
  print_components(&g, &gs);
  clear_search(&gs);
  clear_graph(&g);
  return 0;
}

/* test run 
(note that component number refers to first found vertex in each component)

osman@osman-dev:~/src/algorist/1.1/algorithms$ make connected && valgrind --leak-check=yes -v ./connected
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-search.o graph-search.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o connected.o connected.c
connected.c: In function ‘process_vertex_early’:
connected.c:7: warning: unused parameter ‘gs’
connected.c:7: warning: unused parameter ‘v’
connected.c: In function ‘process_vertex_late’:
connected.c:9: warning: unused parameter ‘gs’
connected.c:9: warning: unused parameter ‘v’
connected.c: In function ‘process_edge’:
connected.c:11: warning: unused parameter ‘gs’
connected.c:11: warning: unused parameter ‘x’
connected.c:11: warning: unused parameter ‘y’
connected.c: In function ‘main’:
connected.c:50: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:43: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o connected graph-search.o connected.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o ../ds/skip-list.o
==3772== Memcheck, a memory error detector
==3772== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==3772== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==3772== Command: ./connected
==3772== 
--3772-- Valgrind options:
--3772--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--3772--    --leak-check=yes
--3772--    -v
--3772-- Contents of /proc/version:
--3772--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--3772-- Arch and hwcaps: X86, x86-sse1-sse2
--3772-- Page sizes: currently 4096, max supported 4096
--3772-- Valgrind library directory: /usr/lib/valgrind
--3772-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--3772-- Reading debug info from /lib/ld-2.11.1.so ..
--3772-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--3772-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--3772-- Reading syms from /home/osman/src/algorist/1.1/algorithms/connected (0x8048000)
--3772-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--3772--    object doesn't have a dynamic symbol table
--3772-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--3772-- Reading suppressions file: /usr/lib/valgrind/default.supp
--3772-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--3772-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--3772-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==3772== WARNING: new redirection conflicts with existing -- ignoring it
--3772--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--3772-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--3772-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--3772-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--3772-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--3772-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--3772-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--3772-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--3772-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--3772-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--3772-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--3772-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--3772-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--3772-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--3772-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--3772-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--3772-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0  value: a edges: 1 
node: 1  value: b edges: 0 
node: 2  value: c edges: 5 4 3 
node: 3  value: d edges: 2 
node: 4  value: e edges: 2 
node: 5  value: f edges: 2 
vertex 0 in component 0
vertex 1 in component 0
vertex 2 in component 2
vertex 3 in component 2
vertex 4 in component 2
vertex 5 in component 2
==3772== 
==3772== HEAP SUMMARY:
==3772==     in use at exit: 0 bytes in 0 blocks
==3772==   total heap usage: 77 allocs, 77 frees, 846 bytes allocated
==3772== 
==3772== All heap blocks were freed -- no leaks are possible
==3772== 
==3772== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--3772-- 
--3772-- used_suppression:     13 dl-hack3-cond-1
==3772== 
==3772== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
