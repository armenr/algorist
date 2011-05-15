/*see README for original credits */

#include"kruskal.h"
#include<stdio.h>

void process_vertex_early(int v) {}
void process_vertex_late(int v) {}
void process_edge(int x, int y) {}

static void init_graph(graph* g) {
  char c;
  initialize_graph(g, false);

  /*should check for return values of insert vertex*/
  c = 'a';
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

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
	graph g;
  init_graph(&g);    
	print_graph(&g, print_item);
	kruskal(&g);
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

osman@osman-dev:~/src/algorithms$ ./kruskal-demo 
node: 1  value: a edges: 6 5 2 
node: 2  value: b edges: 6 3 1 
node: 3  value: c edges: 7 6 4 2 
node: 4  value: d edges: 7 6 5 3 
node: 5  value: e edges: 6 4 1 
node: 6  value: f edges: 5 4 3 2 1 
node: 7  value: g edges: 4 3 
1 set=1 size=1 
2 set=2 size=1 
3 set=3 size=1 
4 set=4 size=1 
5 set=5 size=1 
6 set=6 size=1 
7 set=7 size=1 

edge (3, 7) of weight 2 in MST
1 set=1 size=1 
2 set=2 size=1 
3 set=3 size=2 
4 set=4 size=1 
5 set=5 size=1 
6 set=6 size=1 
7 set=3 size=1 

edge (3, 4) of weight 2 in MST
1 set=1 size=1 
2 set=2 size=1 
3 set=3 size=3 
4 set=3 size=1 
5 set=5 size=1 
6 set=6 size=1 
7 set=3 size=1 

edge (3, 6) of weight 3 in MST
1 set=1 size=1 
2 set=2 size=1 
3 set=3 size=4 
4 set=3 size=1 
5 set=5 size=1 
6 set=3 size=1 
7 set=3 size=1 

edge (2, 6) of weight 4 in MST
1 set=1 size=1 
2 set=3 size=1 
3 set=3 size=5 
4 set=3 size=1 
5 set=5 size=1 
6 set=3 size=1 
7 set=3 size=1 

1 set=1 size=1 
2 set=3 size=1 
3 set=3 size=5 
4 set=3 size=1 
5 set=5 size=1 
6 set=3 size=1 
7 set=3 size=1 

edge (1, 5) of weight 5 in MST
1 set=1 size=2 
2 set=3 size=1 
3 set=3 size=5 
4 set=3 size=1 
5 set=1 size=1 
6 set=3 size=1 
7 set=3 size=1 

1 set=1 size=2 
2 set=3 size=1 
3 set=3 size=5 
4 set=3 size=1 
5 set=1 size=1 
6 set=3 size=1 
7 set=3 size=1 

edge (1, 6) of weight 7 in MST
1 set=3 size=2 
2 set=3 size=1 
3 set=3 size=7 
4 set=3 size=1 
5 set=1 size=1 
6 set=3 size=1 
7 set=3 size=1 

1 set=3 size=2 
2 set=3 size=1 
3 set=3 size=7 
4 set=3 size=1 
5 set=1 size=1 
6 set=3 size=1 
7 set=3 size=1 

1 set=3 size=2 
2 set=3 size=1 
3 set=3 size=7 
4 set=3 size=1 
5 set=1 size=1 
6 set=3 size=1 
7 set=3 size=1 

1 set=3 size=2 
2 set=3 size=1 
3 set=3 size=7 
4 set=3 size=1 
5 set=1 size=1 
6 set=3 size=1 
7 set=3 size=1 
*/

/*osman@osman-dev:~/src/algorist/1.1/ds$ make kruskal-demo && valgrind --leak-check=yes -v ./kruskal-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o kruskal-demo.o kruskal-demo.c*/
/*kruskal-demo.c:6: warning: no previous prototype for ‘process_vertex_early’*/
/*kruskal-demo.c: In function ‘process_vertex_early’:*/
/*kruskal-demo.c:6: warning: unused parameter ‘v’*/
/*kruskal-demo.c: At top level:*/
/*kruskal-demo.c:7: warning: no previous prototype for ‘process_vertex_late’*/
/*kruskal-demo.c: In function ‘process_vertex_late’:*/
/*kruskal-demo.c:7: warning: unused parameter ‘v’*/
/*kruskal-demo.c: At top level:*/
/*kruskal-demo.c:8: warning: no previous prototype for ‘process_edge’*/
/*kruskal-demo.c: In function ‘process_edge’:*/
/*kruskal-demo.c:8: warning: unused parameter ‘x’*/
/*kruskal-demo.c:8: warning: unused parameter ‘y’*/
/*kruskal-demo.c: In function ‘main’:*/
/*kruskal-demo.c:50: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type*/
/*../ds/graph.h:44: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o kruskal.o kruskal.c*/
/*kruskal.c: In function ‘kruskal’:*/
/*kruskal.c:30: warning: passing argument 4 of ‘qsort’ from incompatible pointer type*/
/*/usr/include/stdlib.h:756: note: expected ‘__compar_fn_t’ but argument is of type ‘int (*)(const struct edge_pair *, const struct edge_pair *)’*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o set-union.o set-union.c*/
/*gcc -lm  -o kruskal-demo kruskal-demo.o kruskal.o set-union.o \*/
/*	../ds/graph.o ../ds/list.o 	../ds/queue.o */
/*==22652== Memcheck, a memory error detector*/
/*==22652== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==22652== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==22652== Command: ./kruskal-demo*/
/*==22652== */
/*--22652-- Valgrind options:*/
/*--22652--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--22652--    --leak-check=yes*/
/*--22652--    -v*/
/*--22652-- Contents of /proc/version:*/
/*--22652--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--22652-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--22652-- Page sizes: currently 4096, max supported 4096*/
/*--22652-- Valgrind library directory: /usr/lib/valgrind*/
/*--22652-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--22652-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--22652-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--22652-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--22652-- Reading syms from /home/osman/src/algorist/1.1/ds/kruskal-demo (0x8048000)*/
/*--22652-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--22652--    object doesn't have a dynamic symbol table*/
/*--22652-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--22652-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--22652-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--22652-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--22652-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==22652== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--22652--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--22652-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--22652-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--22652-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--22652-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--22652-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--22652-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--22652-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--22652-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--22652-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--22652-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--22652-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--22652-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--22652-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--22652-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*node: 1  value: a edges: 6 5 2 */
/*node: 2  value: b edges: 6 3 1 */
/*node: 3  value: c edges: 7 6 4 2 */
/*node: 4  value: d edges: 7 6 5 3 */
/*node: 5  value: e edges: 6 4 1 */
/*node: 6  value: f edges: 5 4 3 2 1 */
/*node: 7  value: g edges: 4 3 */
/*--22652-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*#1 edge: (3, 7) of weight 2 in MST*/
/*#2 edge: (3, 4) of weight 2 in MST*/
/*#3 edge: (3, 6) of weight 3 in MST*/
/*#4 edge: (2, 6) of weight 4 in MST*/
/*#5 edge: (1, 5) of weight 5 in MST*/
/*#6 edge: (1, 6) of weight 7 in MST*/
/*==22652== */
/*==22652== HEAP SUMMARY:*/
/*==22652==     in use at exit: 0 bytes in 0 blocks*/
/*==22652==   total heap usage: 77 allocs, 77 frees, 479 bytes allocated*/
/*==22652== */
/*==22652== All heap blocks were freed -- no leaks are possible*/
/*==22652== */
/*==22652== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--22652-- */
/*--22652-- used_suppression:     13 dl-hack3-cond-1*/
/*==22652== */
/*==22652== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

