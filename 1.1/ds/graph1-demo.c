/*see README for original credits */

#include<stdio.h>
#include"graph1.h"

static void init_demo(graph* g) {
  init_graph(g, false);

  char c = 'a';
  add_graph_item(g, &c, sizeof(char));
  insert_vertex(g); /*0*/
  c = 'b';
  add_graph_item(g, &c, sizeof(char));
  insert_vertex(g); /*1*/
  c = 'c';
  add_graph_item(g, &c, sizeof(char));
  insert_vertex(g); /*2*/
  c = 'd';
  add_graph_item(g, &c, sizeof(char));
  insert_vertex(g); /*3*/
  c = 'e';
  add_graph_item(g, &c, sizeof(char));
  insert_vertex(g); /*4*/
  c = 'f';
  add_graph_item(g, &c, sizeof(char));
  insert_vertex(g); /*5*/
  c = 'g';
  add_graph_item(g, &c, sizeof(char));
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

  /*deletion tests  */
  int v = insert_vertex(g); /*7*/
  insert_edge(g, 7, 6, 0);
  delete_edge(g, 7, 6);  
  delete_vertex(g, v);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
	graph g;
  init_demo(&g);    
	print_graph(&g, print_item);
	clear_graph(&g);
  return 0;
}
 
/* 
osman@osman-dev:~/src/algorist/1.1/ds$ make graph1-demo && valgrind --leak-check=yes -v ./graph1-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph1.o graph1.c
graph1.c: In function ‘delete_vertex’:
graph1.c:43: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:40: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
graph1.c:43: warning: initialization discards qualifiers from pointer target type
graph1.c: In function ‘find_vertex’:
graph1.c:67: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:40: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
graph1.c:67: warning: initialization discards qualifiers from pointer target type
graph1.c: In function ‘insert_vertex’:
graph1.c:95: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:42: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
graph1.c: In function ‘delete_undirected_edge’:
graph1.c:199: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:40: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
graph1.c:199: warning: initialization discards qualifiers from pointer target type
graph1.c: In function ‘insert_undirected_edge’:
graph1.c:227: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:40: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
graph1.c:227: warning: initialization discards qualifiers from pointer target type
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph1-demo.o graph1-demo.c
graph1-demo.c: In function ‘main’:
graph1-demo.c:59: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o graph1-demo graph1.o graph1-demo.o skip-list.o
==10004== Memcheck, a memory error detector
==10004== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==10004== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==10004== Command: ./graph1-demo
==10004== 
--10004-- Valgrind options:
--10004--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--10004--    --leak-check=yes
--10004--    -v
--10004-- Contents of /proc/version:
--10004--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--10004-- Arch and hwcaps: X86, x86-sse1-sse2
--10004-- Page sizes: currently 4096, max supported 4096
--10004-- Valgrind library directory: /usr/lib/valgrind
--10004-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--10004-- Reading debug info from /lib/ld-2.11.1.so ..
--10004-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--10004-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--10004-- Reading syms from /home/osman/src/algorist/1.1/ds/graph1-demo (0x8048000)
--10004-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--10004--    object doesn't have a dynamic symbol table
--10004-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--10004-- Reading suppressions file: /usr/lib/valgrind/default.supp
--10004-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--10004-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--10004-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==10004== WARNING: new redirection conflicts with existing -- ignoring it
--10004--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--10004-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--10004-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--10004-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--10004-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--10004-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--10004-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--10004-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--10004-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--10004-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--10004-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--10004-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--10004-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--10004-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--10004-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--10004-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--10004-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0  value: a edges: 5 4 1 
node: 1  value: b edges: 5 2 0 
node: 2  value: c edges: 6 5 3 1 
node: 3  value: d edges: 6 5 4 2 
node: 4  value: e edges: 5 3 0 
node: 5  value: f edges: 4 3 2 1 0 
node: 6  value: g edges: 3 2 
==10004== 
==10004== HEAP SUMMARY:
==10004==     in use at exit: 0 bytes in 0 blocks
==10004==   total heap usage: 94 allocs, 94 frees, 1,042 bytes allocated
==10004== 
==10004== All heap blocks were freed -- no leaks are possible
==10004== 
==10004== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--10004-- 
--10004-- used_suppression:     13 dl-hack3-cond-1
==10004== 
==10004== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

