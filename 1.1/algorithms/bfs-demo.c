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
  char c;
  initialize_graph(g, false);

  c = 'a';
  insert_vertex(g, 1, &c, sizeof (char));
  c = 'b';
  insert_vertex(g, 2, &c, sizeof (char));
  insert_edge(g, 1, 2, 0);
  c = 'e';
  insert_vertex(g, 5, &c, sizeof (char));
  insert_edge(g, 1, 5, 0);
  insert_edge(g, 2, 5, 0);
  c = 'f';
  insert_vertex(g, 6, &c, sizeof (char));
  insert_edge(g, 1, 6, 0);
  c = 'c';
  insert_vertex(g, 3, &c, sizeof (char));
  insert_edge(g, 2, 3, 0);
  c = 'd';
  insert_vertex(g, 4, &c, sizeof (char));
  insert_edge(g, 5, 4, 0);
  insert_edge(g, 3, 4, 0);
  
  /*delete edge test  */
  insert_edge(g, 5, 6, 0);
  delete_edge(g, 5, 6);  
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
  graph g;

  init_graph(&g);
  print_graph(&g, print_item);
  printf("\n");

  initialize_search(&g);
  bfs(&g, 1);
  printf("\n");

  int i;

  for(i = 1; i <= g.nvertices; i++)
    printf(" %d", parent[i]);
  printf("\n");

  for(i = 1; i <= g.nvertices; i++)
    find_path(1, i, parent);
  printf("\n");

  clear_graph(&g);
  return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

6 vertices, 7 edges

 *
              (1)
                        
              
 *       *      *
       (2)     (5)    (6)
                
        
 *        *
      (3)      (4)
         
osman@osman-vbox-l32:~/src/ds$ ./bfs-demo 
node: 1  value: a edges: 6 5 2 
node: 2  value: b edges: 3 5 1 
node: 3  value: c edges: 4 2 
node: 4  value: d edges: 3 5 
node: 5  value: e edges: 4 2 1 
node: 6  value: f edges: 1 

processed vertex 1
processed edge (1,6)
processed edge (1,5)
processed edge (1,2)
processed vertex 6
processed vertex 5
processed edge (5,4)
processed edge (5,2)
processed vertex 2
processed edge (2,3)
processed vertex 4
processed edge (4,3)
processed vertex 3

 -1 1 2 5 1 1

1
1 2
1 2 3
1 5 4
1 5
1 6
 */

/*osman@osman-dev:~/src/algorist/1.1/ds$ make bfs-demo && valgrind --leak-check=yes -v ./bfs-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o bfs-dfs.o bfs-dfs.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o bfs-demo.o bfs-demo.c*/
/*bfs-demo.c: In function ‘process_vertex_late’:*/
/*bfs-demo.c:10: warning: unused parameter ‘v’*/
/*bfs-demo.c: In function ‘main’:*/
/*bfs-demo.c:54: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type*/
/*../ds/graph.h:43: note: expected ‘void (*)(void *)’ but argument is of type ‘void (*)(const char *)’*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o ../ds/graph.o ../ds/graph.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o ../ds/list.o ../ds/list.c*/
/*../ds/list.c: In function ‘delete_list’:*/
/*../ds/list.c:18: warning: cast discards qualifiers from pointer target type*/
/*../ds/list.c:23: warning: cast discards qualifiers from pointer target type*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o ../ds/queue.o ../ds/queue.c*/
/*gcc -lm  -o bfs-demo bfs-dfs.o bfs-demo.o \*/
/*	../ds/graph.o ../ds/list.o 	../ds/queue.o */
/*==3912== Memcheck, a memory error detector*/
/*==3912== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==3912== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==3912== Command: ./bfs-demo*/
/*==3912== */
/*--3912-- Valgrind options:*/
/*--3912--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--3912--    --leak-check=yes*/
/*--3912--    -v*/
/*--3912-- Contents of /proc/version:*/
/*--3912--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--3912-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--3912-- Page sizes: currently 4096, max supported 4096*/
/*--3912-- Valgrind library directory: /usr/lib/valgrind*/
/*--3912-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--3912-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--3912-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--3912-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--3912-- Reading syms from /home/osman/src/algorist/1.1/ds/bfs-demo (0x8048000)*/
/*--3912-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--3912--    object doesn't have a dynamic symbol table*/
/*--3912-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--3912-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--3912-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--3912-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--3912-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==3912== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--3912--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--3912-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--3912-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--3912-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--3912-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--3912-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--3912-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--3912-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--3912-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--3912-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--3912-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--3912-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--3912-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--3912-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--3912-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*--3912-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*node: 1  value: a edges: 6 5 2 */
/*node: 2  value: b edges: 3 5 1 */
/*node: 3  value: c edges: 4 2 */
/*node: 4  value: d edges: 3 5 */
/*node: 5  value: e edges: 4 2 1 */
/*node: 6  value: f edges: 1 */

/*processed vertex 1*/
/*processed edge (1,6)*/
/*processed edge (1,5)*/
/*processed edge (1,2)*/
/*processed vertex 6*/
/*processed vertex 5*/
/*processed edge (5,4)*/
/*processed edge (5,2)*/
/*processed vertex 2*/
/*processed edge (2,3)*/
/*processed vertex 4*/
/*processed edge (4,3)*/
/*processed vertex 3*/

/* -1 1 2 5 1 1*/

/*1*/
/*1 2*/
/*1 2 3*/
/*1 5 4*/
/*1 5*/
/*1 6*/
/*==3912== */
/*==3912== HEAP SUMMARY:*/
/*==3912==     in use at exit: 0 bytes in 0 blocks*/
/*==3912==   total heap usage: 34 allocs, 34 frees, 270 bytes allocated*/
/*==3912== */
/*==3912== All heap blocks were freed -- no leaks are possible*/
/*==3912== */
/*==3912== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--3912-- */
/*--3912-- used_suppression:     13 dl-hack3-cond-1*/
/*==3912== */
/*==3912== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

