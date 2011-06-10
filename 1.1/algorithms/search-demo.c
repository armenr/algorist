/*see README for original credits */

#include<stdio.h>
#include"graph-print.h"
#include"graph-search.h"
#include"graph-vertex.h"

static void bi_conn_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  char c = 'a';
  insert_vertex(g); /*0*/
  c = 'b';
  insert_vertex(g); /*1*/
  c = 'c';
  insert_vertex(g); /*2*/
  c = 'd';
  insert_vertex(g); /*3*/
  c = 'e';
  insert_vertex(g); /*4*/
  c = 'f';
  insert_vertex(g); /*5*/
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 0, 5, 0);
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 2, 3, 0);
  insert_edge(g, 3, 4, 0);
  insert_edge(g, 4, 1, 0);
}

static void bi_part_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
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
}

static void bi_part_demo2(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 0, 2, 0);
}

static void connection_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 2, 3, 0);
  insert_edge(g, 2, 4, 0);
  insert_edge(g, 2, 5, 0);
}

/*
static void cycle_demo(graph* g) {
  init_graph(g, false);

  insert_vertex(g); 
  insert_vertex(g); 
  insert_vertex(g); 
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 0, 2, 0);  
}
*/

static void fs_demo(graph* g) {
  init_graph(g, false);

  /*refer to graph diagram below for structure*/
  int v = insert_vertex(g);  /*0*/
  v = insert_vertex(g);  /*1*/
  insert_edge(g, 0, v, 0);
  v = insert_vertex(g);  /*2*/
  insert_edge(g, 0, v, 0);
  insert_edge(g, 1, v, 0);
  v = insert_vertex(g);  /*3*/
  insert_edge(g, 0, v, 0);
  v = insert_vertex(g);  /*4*/
  insert_edge(g, 1, v, 0);
  v = insert_vertex(g);  /*5*/
  insert_edge(g, 4, v, 0);
  insert_edge(g, 2, v, 0);
}

static void strong_demo(graph* g) {
  init_graph(g, true);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  insert_vertex(g); /*6*/
  insert_vertex(g); /*7*/
  
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 1, 3, 0);
  insert_edge(g, 3, 5, 0);
  insert_edge(g, 3, 7, 0);
  insert_edge(g, 7, 5, 0);
  insert_edge(g, 5, 6, 0);
  insert_edge(g, 6, 4, 0);
  insert_edge(g, 4, 5, 0);
  insert_edge(g, 1, 4, 0);
  insert_edge(g, 3, 0, 0);
  insert_edge(g, 2, 0, 0);
}

static void top_sort_demo(graph* g) {
  init_graph(g, true);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  insert_vertex(g); /*6*/
  
  insert_edge(g, 6, 0, 0);
  insert_edge(g, 6, 5, 0);
  insert_edge(g, 0, 2, 0);
  insert_edge(g, 2, 5, 0);
  insert_edge(g, 0, 1, 0);
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 2, 4, 0);
  insert_edge(g, 5, 4, 0);
  insert_edge(g, 1, 3, 0);
  insert_edge(g, 4, 3, 0);
}

int main(void) {
  graph g;
  graph_search gs;

  fs_demo(&g);

  printf("\n===\n");
  printf("BFS");
  printf("\n===\n\n");
  print_graph(&g, print_item);
  printf("\n");
  init_search(&g, &gs);
  bfs(&g, &gs, 0, bfs_early, NULL, bfs_edge);
  printf("\n");
  print_fs(&g, &gs);
  clear_search(&gs);

  printf("\n===\n");
  printf("DFS");
  printf("\n===\n\n");
  print_graph(&g, print_item);
  printf("\n");
  init_search(&g, &gs);
  dfs(&g, &gs, 0, dfs_early, dfs_late, dfs_edge);
  printf("\n");
  print_fs(&g, &gs);

  clear_search(&gs);
  clear_graph(&g);
  
  printf("\n====================\n");
  printf("Connected components");
  printf("\n====================\n\n");
  connection_demo(&g);
  print_graph(&g, print_item);
  printf("\n");  
  init_search(&g, &gs);
  connected_components(&g, &gs, NULL, NULL, NULL);
  print_components(&g, &gs);

  clear_search(&gs);
  clear_graph(&g);
  
  printf("\n=====================\n");
  printf("Bi-connected vertices");
  printf("\n=====================\n\n");
  bi_conn_demo(&g);
  print_graph(&g, print_item);
  printf("\n");  
  init_search(&g, &gs);
  articulation_vertices(&g, &gs, bi_conn_early, bi_conn_late, bi_conn_edge);
  
  clear_search(&gs);
  clear_graph(&g);
  
  printf("\n===================\n");
  printf("Bi-partite coloring");
  printf("\n===================\n\n");
  bi_part_demo(&g);
  print_graph(&g, print_item);
  printf("\n");  
  init_search(&g, &gs);
  two_color(&g, &gs, NULL, NULL, bi_part_edge);
  print_colors(&g, &gs);
  printf("\n");  

  clear_search(&gs);
  clear_graph(&g);

  bi_part_demo2(&g);
  print_graph(&g, print_item);
  printf("\n");  
  init_search(&g, &gs);
  two_color(&g, &gs, NULL, NULL, bi_part_edge);
  print_colors(&g, &gs);

  clear_search(&gs);
  clear_graph(&g);

  printf("\n============\n");
  printf("Top sort DAG");
  printf("\n============\n\n");
  top_sort_demo(&g);
  print_graph(&g, print_item);
  printf("\n");  
  init_search(&g, &gs);
  top_sort(&g, &gs);
  printf("\n");  
  print_top_sort(&gs);
  
  clear_search(&gs);
  clear_graph(&g);

  printf("\n=================\n");
  printf("Strong components");
  printf("\n=================\n\n");
  strong_demo(&g);
  print_graph(&g, print_item);
  printf("\n");  
  init_search(&g, &gs);
  strong_components(&g, &gs);
  printf("\n");  
  
  clear_search(&gs);
  clear_graph(&g);

/*  printf("\n==========\n");*/
/*  printf("Find cycle");*/
/*  printf("\n==========\n\n");*/
/*  cycle_demo(&g);*/
/*  print_graph(&g, print_item);*/
/*  printf("\n");*/
/*  init_search(&g, &gs);*/
/*  dfs(&g, &gs, 0, dfs_early, dfs_late, cycle_edge);*/
/*  printf("\n");*/
/*  print_fs(&g, &gs);*/

/*  clear_search(&gs);*/
/*  clear_graph(&g);*/
  
  return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/algorithms$ gedit graph-search.h graph-search.c
osman@osman-dev:~/src/algorist/1.1/algorithms$ make search-demo && valgrind --leak-check=yes -v ./search-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o graph-search.o graph-search.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o search-demo.o search-demo.c
search-demo.c: In function ‘bfs_early’:
search-demo.c:49: warning: unused parameter ‘gs’
search-demo.c: In function ‘bfs_edge’:
search-demo.c:53: warning: unused parameter ‘gs’
search-demo.c: In function ‘main’:
search-demo.c:235: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
search-demo.c:246: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
search-demo.c:260: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
search-demo.c:273: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
search-demo.c:285: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
search-demo.c:296: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -lm  -o search-demo graph-search.o search-demo.o \
	../ds/graph1.o ../ds/list.o ../ds/queue.o ../ds/skip-list.o
==11443== Memcheck, a memory error detector
==11443== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==11443== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==11443== Command: ./search-demo
==11443== 
--11443-- Valgrind options:
--11443--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--11443--    --leak-check=yes
--11443--    -v
--11443-- Contents of /proc/version:
--11443--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--11443-- Arch and hwcaps: X86, x86-sse1-sse2
--11443-- Page sizes: currently 4096, max supported 4096
--11443-- Valgrind library directory: /usr/lib/valgrind
--11443-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--11443-- Reading debug info from /lib/ld-2.11.1.so ..
--11443-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--11443-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--11443-- Reading syms from /home/osman/src/algorist/1.1/algorithms/search-demo (0x8048000)
--11443-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--11443--    object doesn't have a dynamic symbol table
--11443-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--11443-- Reading suppressions file: /usr/lib/valgrind/default.supp
--11443-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--11443-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--11443-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==11443== WARNING: new redirection conflicts with existing -- ignoring it
--11443--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--11443-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--11443-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--11443-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--11443-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--11443-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--11443-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--11443-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--11443-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--11443-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--11443-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--11443-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--11443-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--11443-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--11443-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--11443-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--11443-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)

===
BFS
===

see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

6 vertices, 7 edges

               *
              (0)
                        
              
       *       *      *
      (1)     (2)    (3)


       *       *
      (4)     (5)

node: 0 edges: 3 2 1 
node: 1 edges: 4 2 0 
node: 2 edges: 5 1 0 
node: 3 edges: 0 
node: 4 edges: 5 1 
node: 5 edges: 2 4 

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

===
DFS
===

see fig 5.9 pp 162 "The Algorithm Design Manual" by Steve S. Skiena

6 vertices, 7 edges

               *
              (0)
                        
              
       *       *      *
      (1)     (2)    (3)


       *       *
      (4)     (5)

node: 0 edges: 3 2 1 
node: 1 edges: 4 2 0 
node: 2 edges: 5 1 0 
node: 3 edges: 0 
node: 4 edges: 5 1 
node: 5 edges: 2 4 

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

====================
Connected components
====================

(note that component number refers to first found vertex in each component)

node: 0 edges: 1 
node: 1 edges: 0 
node: 2 edges: 5 4 3 
node: 3 edges: 2 
node: 4 edges: 2 
node: 5 edges: 2 

vertex 0 in component 0
vertex 1 in component 0
vertex 2 in component 2
vertex 3 in component 2
vertex 4 in component 2
vertex 5 in component 2

======================
Bi-connected vertices
======================

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

node: 0 edges: 5 1 
node: 1 edges: 4 2 0 
node: 2 edges: 3 1 
node: 3 edges: 4 2 
node: 4 edges: 1 3 
node: 5 edges: 0 

bridge articulation vertex: 3   
bridge articulation vertex: 4 
bridge articulation vertex: 3 
bridge articulation vertex: 1 
bridge articulation vertex: 4 
root articulation vertex: 0 

====================
Bi-partite coloring
====================

see fig 6.3 pp 196 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 12 edges

                 *(3)
                          *(6)
                                                                        
                
       (4)*       *(5)    *(2)

                
        
            *         *                          
           (0)        (1)

node: 0 edges: 5 4 1 
node: 1 edges: 5 2 0 
node: 2 edges: 6 5 3 1 
node: 3 edges: 6 5 4 2 
node: 4 edges: 5 3 0 
node: 5 edges: 4 3 2 1 0 
node: 6 edges: 3 2 

vertex 0 color 1
vertex 1 color 1
vertex 2 color 1
vertex 3 color 2
vertex 4 color 1
vertex 5 color 2
vertex 6 color 2
graph two colored is FALSE


node: 0 edges: 2 1 
node: 1 edges: 0 
node: 2 edges: 0 

vertex 0 color 1
vertex 1 color 2
vertex 2 color 2
graph two colored is TRUE

============
Top sort DAG
============

see fig 5.15 pp 179 "The Algorithm Design Manual" by Steve S. Skiena

node: 0 edges: 1 2 
node: 1 edges: 3 2 
node: 2 edges: 4 5 
node: 3 edges: 
node: 4 edges: 3 
node: 5 edges: 4 
node: 6 edges: 5 0 

entered vertex 0 at time 0
entered vertex 1 at time 1
entered vertex 3 at time 2
entered vertex 2 at time 3
entered vertex 4 at time 4
entered vertex 5 at time 5
entered vertex 6 at time 6

6 0 1 2 5 4 3  = G A B C F E D

=================
Strong components
=================

see fig 5.16 pp 182 "The Algorithm Design Manual" by Steve S. Skiena

node: 0 edges: 1 
node: 1 edges: 4 3 2 
node: 2 edges: 0 
node: 3 edges: 0 7 5 
node: 4 edges: 5 
node: 5 edges: 6 
node: 6 edges: 4 
node: 7 edges: 5 

4 is in component 1 
6 is in component 1 with 4 
5 is in component 1 with 4 
7 is in component 2 
0 is in component 3 
2 is in component 3 with 0 
3 is in component 3 with 0 
1 is in component 3 with 0 

==11443== 
==11443== HEAP SUMMARY:
==11443==     in use at exit: 0 bytes in 0 blocks
==11443==   total heap usage: 364 allocs, 364 frees, 4,744 bytes allocated
==11443== 
==11443== All heap blocks were freed -- no leaks are possible
==11443== 
==11443== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--11443-- 
--11443-- used_suppression:     13 dl-hack3-cond-1
==11443== 
==11443== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/ 
