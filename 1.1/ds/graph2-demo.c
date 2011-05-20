/*see README for original credits */

#include"graph2.h"
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
 
/*osman@osman-dev:~/src/algorist/1.1/ds$ make graph-demo2 && valgrind --leak-check=yes -v ./graph-demo2*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph2.o graph2.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-demo2.o graph-demo2.c*/
/*graph-demo2.c: In function ‘main’:*/
/*graph-demo2.c:52: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type*/
/*graph2.h:45: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’*/
/*gcc -lm  -o graph-demo2 graph2.o graph-demo2.o */
/*==2405== Memcheck, a memory error detector*/
/*==2405== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==2405== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==2405== Command: ./graph-demo2*/
/*==2405== */
/*--2405-- Valgrind options:*/
/*--2405--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--2405--    --leak-check=yes*/
/*--2405--    -v*/
/*--2405-- Contents of /proc/version:*/
/*--2405--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--2405-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--2405-- Page sizes: currently 4096, max supported 4096*/
/*--2405-- Valgrind library directory: /usr/lib/valgrind*/
/*--2405-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--2405-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--2405-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--2405-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--2405-- Reading syms from /home/osman/src/algorist/1.1/ds/graph-demo2 (0x8048000)*/
/*--2405-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--2405--    object doesn't have a dynamic symbol table*/
/*--2405-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--2405-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--2405-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--2405-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--2405-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==2405== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--2405--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--2405-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--2405-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--2405-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--2405-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--2405-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--2405-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--2405-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--2405-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--2405-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--2405-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--2405-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)*/
/*--2405-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--2405-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--2405-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--2405-- REDIR: 0x40d2ec0 (realloc) redirected to 0x4024f4a (realloc)*/
/*--2405-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*--2405-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*node: 0  value: a edges: 5 4 1 */
/*node: 1  value: b edges: 5 2 0 */
/*node: 2  value: c edges: 6 5 3 1 */
/*node: 3  value: d edges: 6 5 4 2 */
/*node: 4  value: e edges: 5 3 0 */
/*node: 5  value: f edges: 4 3 2 1 0 */
/*node: 6  value: g edges: 3 2 */
/*==2405== */
/*==2405== HEAP SUMMARY:*/
/*==2405==     in use at exit: 0 bytes in 0 blocks*/
/*==2405==   total heap usage: 44 allocs, 44 frees, 464 bytes allocated*/
/*==2405== */
/*==2405== All heap blocks were freed -- no leaks are possible*/
/*==2405== */
/*==2405== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--2405-- */
/*--2405-- used_suppression:     13 dl-hack3-cond-1*/
/*==2405== */
/*==2405== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

