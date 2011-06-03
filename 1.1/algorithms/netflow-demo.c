/*see README for original credits */

#include<stdio.h>
#include"netflow.h"

static void init_demo(graph* g) {
  init_graph(g, true);  /*directed*/

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  insert_vertex(g); /*6*/

  flow_node f;
  f.flow = 0;
  
  f.residual = 5;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 0, 1, f.residual);

  f.residual = 12;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 0, 2, f.residual);

  f.residual = 7;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 1, 3, f.residual);

  f.residual = 9;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 1, 4, f.residual);

  f.residual = 4;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 2, 4, f.residual);

  f.residual = 7;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 2, 5, f.residual);

  f.residual = 3;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 3, 4, f.residual);

  f.residual = 5;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 3, 6, f.residual);

  f.residual = 3;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 4, 5, f.residual);

  f.residual = 2;
  add_graph_item(g, &f, sizeof(flow_node));
  insert_edge(g, 5, 6, f.residual);
}

static void print_item(const char* item) {
  printf(" value: %c ", *item);
}

int main(void) {
	graph g;
  init_demo(&g);    
	print_graph(&g, print_item);
	int source = 0, sink = 6;	
  printf("\nsource = %d sink = %d\n\n", source, sink);
	netflow(&g, source, sink);
	print_flow_graph(&g, source);
	clear_graph(&g);
	return 0;
}

/* test run
see fig 6.13 pp 219 "The Algorithm Design Manual" by Steve S. Skiena

7 vertices, 10 edges

               *(3)
                        *(6)
                                                                        
              
     (1)*       *(4)    *(5)

                
        
          *         *                          
         (0)        (2)

osman@osman-dev:~/src/algorist/1.1/algorithms$ make netflow-demo && valgrind --leak-check=yes -v ./netflow-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o netflow-demo.o netflow-demo.c
netflow-demo.c: In function ‘main’:
netflow-demo.c:69: warning: passing argument 2 of ‘print_graph’ from incompatible pointer type
../ds/graph-ops.h:17: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o netflow.o netflow.c
gcc -lm  -o netflow-demo netflow-demo.o netflow.o graph-search.o \
	../ds/graph1.o ../ds/list.o ../ds/queue.o ../ds/skip-list.o
==30387== Memcheck, a memory error detector
==30387== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==30387== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==30387== Command: ./netflow-demo
==30387== 
--30387-- Valgrind options:
--30387--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--30387--    --leak-check=yes
--30387--    -v
--30387-- Contents of /proc/version:
--30387--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--30387-- Arch and hwcaps: X86, x86-sse1-sse2
--30387-- Page sizes: currently 4096, max supported 4096
--30387-- Valgrind library directory: /usr/lib/valgrind
--30387-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--30387-- Reading debug info from /lib/ld-2.11.1.so ..
--30387-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--30387-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--30387-- Reading syms from /home/osman/src/algorist/1.1/algorithms/netflow-demo (0x8048000)
--30387-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--30387--    object doesn't have a dynamic symbol table
--30387-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--30387-- Reading suppressions file: /usr/lib/valgrind/default.supp
--30387-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--30387-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--30387-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==30387== WARNING: new redirection conflicts with existing -- ignoring it
--30387--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--30387-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--30387-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--30387-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--30387-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--30387-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--30387-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--30387-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--30387-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--30387-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--30387-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--30387-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--30387-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--30387-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--30387-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--30387-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--30387-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
node: 0 edges: 2 1 
node: 1 edges: 4 3 
node: 2 edges: 5 4 
node: 3 edges: 6 4 
node: 4 edges: 5 
node: 5 edges: 6 
node: 6 edges: 

source = 0 sink = 6

0:  2(12, 2, 10) 1(5, 5, 0)
1:  0(0, 0, 5) 4(9, 0, 9) 3(7, 5, 2)
2:  0(0, 0, 2) 5(7, 2, 5) 4(4, 0, 4)
3:  1(0, 0, 5) 6(5, 5, 0) 4(3, 0, 3)
4:  3(0, 0, 0) 2(0, 0, 0) 1(0, 0, 0) 5(3, 0, 3)
5:  4(0, 0, 0) 2(0, 0, 2) 6(2, 2, 0)
6:  5(0, 0, 2) 3(0, 0, 5)

total flow = 7
==30387== 
==30387== HEAP SUMMARY:
==30387==     in use at exit: 0 bytes in 0 blocks
==30387==   total heap usage: 180 allocs, 180 frees, 2,206 bytes allocated
==30387== 
==30387== All heap blocks were freed -- no leaks are possible
==30387== 
==30387== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--30387-- 
--30387-- used_suppression:     13 dl-hack3-cond-1
==30387== 
==30387== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
