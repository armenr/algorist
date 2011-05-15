/*see README for original credits */

#include"bfs-dfs.h"
#include<stdio.h>

void process_vertex_early(int v) {
	entry_time[v] = ++time;
	printf("entered vertex %d at time %d\n", v, entry_time[v]);
}

void process_vertex_late(int v) {
	exit_time[v] = ++time;
  printf("exit vertex %d at time %d\n", v, exit_time[v]);
}

void process_edge(int x, int y) {
	int class = edge_classification(x, y);

	switch(class) {
	  case BACK:
  	  printf("back edge (%d, %d)\n", x, y);
	    break;
	  case TREE:
	  printf("tree edge (%d,%d)\n", x, y);
	    break;
	  case FORWARD:
  	  printf("forward edge (%d,%d)\n", x, y);
	    break;
	  case CROSS:
  	  printf("cross edge (%d,%d)\n", x, y);
	    break;
	  default:
  	  printf("edge (%d,%d)\n not in valid class=%d", x, y, class);
	}  
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

static void print_dfs(graph* g) {
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
  dfs(&g, 0);
  print_dfs(&g);
  clear_search();
  clear_graph(&g);
  return 0;
}

/* test run 
see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

6 vertices, 7 edges

               *
              (0)
                        
              
       *       *      *
      (1)     (2)    (3)


       *       *
      (4)     (5)

osman@osman-dev:~/src/algorist/1.1/algorithms$ make dfs-demo && valgrind --leak-check=yes -v ./dfs-demo 
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o dfs-demo.o dfs-demo.c
dfs-demo.c: In function ‘main’:
dfs-demo.c:81: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph.h:44: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o dfs-demo bfs-dfs.o dfs-demo.o \
	../ds/graph.o ../ds/list.o 	../ds/queue.o ../ds/skip-list.o
==30556== Memcheck, a memory error detector
==30556== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==30556== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==30556== Command: ./dfs-demo
==30556== 
--30556-- Valgrind options:
--30556--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--30556--    --leak-check=yes
--30556--    -v
--30556-- Contents of /proc/version:
--30556--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--30556-- Arch and hwcaps: X86, x86-sse1-sse2
--30556-- Page sizes: currently 4096, max supported 4096
--30556-- Valgrind library directory: /usr/lib/valgrind
--30556-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--30556-- Reading debug info from /lib/ld-2.11.1.so ..
--30556-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--30556-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--30556-- Reading syms from /home/osman/src/algorist/1.1/algorithms/dfs-demo (0x8048000)
--30556-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--30556--    object doesn't have a dynamic symbol table
--30556-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--30556-- Reading suppressions file: /usr/lib/valgrind/default.supp
--30556-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--30556-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--30556-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==30556== WARNING: new redirection conflicts with existing -- ignoring it
--30556--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--30556-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--30556-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--30556-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--30556-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--30556-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--30556-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--30556-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--30556-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--30556-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--30556-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--30556-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--30556-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--30556-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--30556-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--30556-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--30556-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0  value: a edges: 3 2 1 
node: 1  value: b edges: 4 2 0 
node: 2  value: e edges: 5 1 0 
node: 3  value: f edges: 0 
node: 4  value: c edges: 5 1 
node: 5  value: d edges: 2 4 
entered vertex 0 at time 2
tree edge (0,3)
entered vertex 3 at time 4
back edge (3, 0)
exit vertex 3 at time 5
tree edge (0,2)
entered vertex 2 at time 8
tree edge (2,5)
entered vertex 5 at time 10
back edge (5, 2)
tree edge (5,4)
entered vertex 4 at time 12
back edge (4, 5)
tree edge (4,1)
entered vertex 1 at time 14
back edge (1, 4)
back edge (1, 2)
back edge (1, 0)
exit vertex 1 at time 15
exit vertex 4 at time 17
exit vertex 5 at time 19
back edge (2, 0)
exit vertex 2 at time 21
exit vertex 0 at time 23
 -1 4 0 0 5 2

0
0 2 5 4 1
0 2
0 3
0 2 5 4
0 2 5
==30556== 
==30556== HEAP SUMMARY:
==30556==     in use at exit: 0 bytes in 0 blocks
==30556==   total heap usage: 67 allocs, 67 frees, 750 bytes allocated
==30556== 
==30556== All heap blocks were freed -- no leaks are possible
==30556== 
==30556== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--30556-- 
--30556-- used_suppression:     13 dl-hack3-cond-1
==30556== 
==30556== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

