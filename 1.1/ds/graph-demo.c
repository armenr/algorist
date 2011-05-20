/*see README for original credits */

#include"graph.h"
#include<stdio.h>

static void init_demo(graph* g) {
  init_graph(g, false);

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

  /*deletion tests  */
  c = 'h';
  int v = insert_vertex(g, &c, sizeof(char)); /*7*/
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
 
/*osman@osman-dev:~/src/algorist/1.1/ds$ make graph-demo && valgrind --leak-check=yes -v ./graph-demo */
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph.o graph.c*/
/*graph.c: In function ‘delete_vertex’:*/
/*graph.c:27: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:42: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*graph.c:27: warning: initialization discards qualifiers from pointer target type*/
/*graph.c: In function ‘insert_vertex’:*/
/*graph.c:65: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:44: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*graph.c: In function ‘delete_undirected_edge’:*/
/*graph.c:166: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:42: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*graph.c:166: warning: initialization discards qualifiers from pointer target type*/
/*graph.c: In function ‘insert_undirected_edge’:*/
/*graph.c:193: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:42: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*graph.c:193: warning: initialization discards qualifiers from pointer target type*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-demo.o graph-demo.c*/
/*graph-demo.c: In function ‘main’:*/
/*graph-demo.c:52: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type*/
/*graph.h:43: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’*/
/*gcc -lm  -o graph-demo graph.o graph-demo.o skip-list.o*/
/*==23231== Memcheck, a memory error detector*/
/*==23231== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==23231== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==23231== Command: ./graph-demo*/
/*==23231== */
/*--23231-- Valgrind options:*/
/*--23231--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--23231--    --leak-check=yes*/
/*--23231--    -v*/
/*--23231-- Contents of /proc/version:*/
/*--23231--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--23231-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--23231-- Page sizes: currently 4096, max supported 4096*/
/*--23231-- Valgrind library directory: /usr/lib/valgrind*/
/*--23231-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--23231-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--23231-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--23231-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--23231-- Reading syms from /home/osman/src/algorist/1.1/ds/graph-demo (0x8048000)*/
/*--23231-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--23231--    object doesn't have a dynamic symbol table*/
/*--23231-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--23231-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--23231-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--23231-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--23231-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==23231== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--23231--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--23231-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--23231-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--23231-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--23231-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--23231-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--23231-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--23231-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--23231-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--23231-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--23231-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--23231-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--23231-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)*/
/*--23231-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--23231-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--23231-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*--23231-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*node: 0  value: a edges: 5 4 1 */
/*node: 1  value: b edges: 5 2 0 */
/*node: 2  value: c edges: 6 5 3 1 */
/*node: 3  value: d edges: 6 5 4 2 */
/*node: 4  value: e edges: 5 3 0 */
/*node: 5  value: f edges: 4 3 2 1 0 */
/*node: 6  value: g edges: 3 2 */
/*==23231== */
/*==23231== HEAP SUMMARY:*/
/*==23231==     in use at exit: 0 bytes in 0 blocks*/
/*==23231==   total heap usage: 88 allocs, 88 frees, 956 bytes allocated*/
/*==23231== */
/*==23231== All heap blocks were freed -- no leaks are possible*/
/*==23231== */
/*==23231== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--23231-- */
/*--23231-- used_suppression:     13 dl-hack3-cond-1*/
/*==23231== */
/*==23231== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

