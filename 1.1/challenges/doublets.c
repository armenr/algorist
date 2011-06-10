/*
 Copyright 2010 Osman Pub

 Licensed under the Apache License, Version 2.0 (the "License"); you may not use
 this file except in compliance with the License.
  
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software distributed
 under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied. See the License for the
 specific language governing permissions and limitations under the License.
 */

/*
3.8.7 Doublets
PC/UVa IDs: 110307/10150, Popularity: C, Success rate: average Level: 3

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input 

booster 
rooster 
roaster 
coasted 
roasted 
coastal 
postal 

booster roasted
coastal postal

Sample Output

booster
rooster
roaster
roasted

No solution.
*/

#include"../algorithms/edit-string.h"
#include"../ds/graph.h"
#include"../ds/hashtbl.h"
#include"../ds/stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char* dictionary[] = {"booster", "rooster", "roaster", "coasted", 
  "roasted", "coastal", "postal"};
#define DICT_SIZE (int)(sizeof(dictionary) / sizeof(dictionary[0]))

static char* pairs[][2] = {{"booster", "roasted"}, {"coastal", "postal"}};
#define PAIRS_SIZE (int)(sizeof(pairs) / sizeof(pairs[0]))

static HASHTBL *found;  /* discovered doublets*/
static graph g; /* only add unique doublets to graph, by checking first in found*/
static stack solution;		/* hold path from root to target in a stack */

static void print_item(const char* item) {
  printf("%s ", item);
}

static void init_graph(graph* g, const char* r) {
  initialize_graph(g, true);  /* directed graph */
  insert_vertex(g, 0, r, strlen(r)+1);
	hashtbl_insert(found, r, r);          
}

static void init_found(void) {
	found = hashtbl_create(DICT_SIZE, NULL);
}

static void init_solution(void) {
	init_stack(&solution);
}

static void add_candidate(const char* candidate, int v) {
  insert_vertex(&g, g.nvertices, candidate, (int)strlen(candidate)+1);      
  int n = g.nvertices-1;
  insert_edge(&g, v, n, 0);
	hashtbl_insert(found, candidate, &n);          
}

static bool find_target(int v, const char* m) {
	char* s, *r;		
  int i;
  bool success = false;
  
  
  /* s used in edit string to find doublet*/
  r = (char*)g.vertices[v].item; /* root item*/
  s = malloc((int)strlen(r)+2);
  /* append an initial space for edit string function*/
  s[0] = ' ';
  strcpy(&s[1], r);

  for(i = 0; i < DICT_SIZE; i++) {

    char* candidate = dictionary[i];
    char* t = malloc((int)strlen(candidate)+2);
    
	  t[0] = ' '; 
    strcpy(&t[1], candidate);
    
    if(string_compare(s, t) == 1) { /* doublet*/

      if(strcmp(candidate, m)) { /* unmatched*/
        if(hashtbl_get(found, candidate) == NULL)  /* not already added*/
          add_candidate(candidate, v);
          
      } else {
        add_candidate(candidate, v);
		    push_stack(&solution, candidate, (int)strlen(candidate)+1);
        free(t);
        success = true;
        break;
      }
    } 
         
    free(t);
  }

  free(s);
  
  /* iterate through graph edges to find target*/
  edgenode* p = g.vertices[v].edges;
  
  while(p != NULL && !success) 
  	if(!(success = find_target(p->y, m)))
  	  p = p->next;

  if(success)  /* add item to solution */
		push_stack(&solution, g.vertices[v].item, 
		  (int)strlen(g.vertices[v].item)+1);

  /* to save space we can delete processed vertices, so the path we find later
   on just contains the link from root to target*/
  else 
    delete_vertex(&g, v);
    
  return success;
}

static void clean_up(void) {
  clear_graph(&g);
	clear_stack(&solution);    
	hashtbl_destroy(found);
}

static void find_doublets(void) {
  int i;

  printf("\n==============================\n\n");    

  for(i = 0; i < PAIRS_SIZE; i++) {
    char* root = pairs[i][0];
    char* target = pairs[i][1];
    
    init_found();
    init_graph(&g, root);   
    init_solution();
        
    printf("%s to %s: \n", root, target);
    
  	if(find_target(0, target)) 
			print_stack(solution, print_item);
  	else
  	  printf("no solution\n");
  	    	  
    printf("\n==============================\n\n");    
  	clean_up();
  }
}

int main(void) {
  find_doublets();
  return 0;
}

/* test runs
osman@osman-desktop:~/src/algorist/1.1/challenges$ ./doublets-dfs 

==============================

booster to roasted: 

node: 0 booster edges: 1 
node: 1 rooster edges: 2 
node: 2 roaster edges: 3 
node: 3 roasted edges: 
entered vertex 0 at time 2
tree edge (0,1)
entered vertex 1 at time 4
tree edge (1,2)
entered vertex 2 at time 6
tree edge (2,3)
entered vertex 3 at time 8
exit vertex 3 at time 9
exit vertex 2 at time 11
exit vertex 1 at time 13
exit vertex 0 at time 15

booster rooster roaster roasted 

==============================

coastal to postal: 

entered vertex 0 at time 2
exit vertex 0 at time 3

(null) (null) (null) (null) 
no solution

==============================

*/

/*osman@osman-dev:~/src/algorist/1.1/challenges$ make doublets && valgrind --leak-check=yes -v ./doublets  */
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o doublets.o doublets.c*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:55: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:55: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:55: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c: In function ‘init_graph’:*/
/*doublets.c:72: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*../ds/hashtbl.h:27: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*doublets.c: At top level:*/
/*doublets.c:75: warning: no previous prototype for ‘init_found’*/
/*doublets.c:79: warning: no previous prototype for ‘init_solution’*/
/*doublets.c: In function ‘init_solution’:*/
/*doublets.c:80: error: too few arguments to function ‘init_stack’*/
/*doublets.c: In function ‘add_candidate’:*/
/*doublets.c:86: error: too many arguments to function ‘insert_edge’*/
/*doublets.c: In function ‘find_doublets’:*/
/*doublets.c:172: warning: passing argument 2 of ‘print_stack’ from incompatible pointer type*/
/*../ds/stack.h:16: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’*/
/*make: *** [doublets.o] Error 1*/
/*osman@osman-dev:~/src/algorist/1.1/challenges$ make doublets && valgrind --leak-check=yes -v ./doublets  */
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o doublets.o doublets.c*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:54: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:55: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:55: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:55: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c:58: warning: initialization discards qualifiers from pointer target type*/
/*doublets.c: In function ‘init_graph’:*/
/*doublets.c:72: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*../ds/hashtbl.h:27: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*doublets.c: In function ‘find_doublets’:*/
/*doublets.c:172: warning: passing argument 2 of ‘print_stack’ from incompatible pointer type*/
/*../ds/stack.h:16: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const char *)’*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o ../algorithms/edit-string.o ../algorithms/edit-string.c*/
/*../algorithms/edit-string.c: In function ‘indel’:*/
/*../algorithms/edit-string.c:23: warning: unused parameter ‘c’*/
/*../algorithms/edit-string.c: In function ‘insert_out’:*/
/*../algorithms/edit-string.c:51: warning: unused parameter ‘t’*/
/*../algorithms/edit-string.c:51: warning: unused parameter ‘j’*/
/*../algorithms/edit-string.c: In function ‘delete_out’:*/
/*../algorithms/edit-string.c:55: warning: unused parameter ‘s’*/
/*../algorithms/edit-string.c:55: warning: unused parameter ‘i’*/
/*gcc -lm -o doublets doublets.o ../algorithms/edit-string.o ../ds/graph.o \*/
/*	../ds/hashtbl.o  ../ds/stack.o ../ds/list.o */
/*==15699== Memcheck, a memory error detector*/
/*==15699== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==15699== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==15699== Command: ./doublets*/
/*==15699== */
/*--15699-- Valgrind options:*/
/*--15699--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--15699--    --leak-check=yes*/
/*--15699--    -v*/
/*--15699-- Contents of /proc/version:*/
/*--15699--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--15699-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--15699-- Page sizes: currently 4096, max supported 4096*/
/*--15699-- Valgrind library directory: /usr/lib/valgrind*/
/*--15699-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--15699-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--15699-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--15699-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--15699-- Reading syms from /home/osman/src/algorist/1.1/challenges/doublets (0x8048000)*/
/*--15699-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--15699--    object doesn't have a dynamic symbol table*/
/*--15699-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--15699-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--15699-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--15699-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--15699-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==15699== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--15699--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--15699-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--15699-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--15699-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--15699-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--15699-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--15699-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--15699-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--15699-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--15699-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--15699-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--15699-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/

/*==============================*/

/*--15699-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--15699-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)*/
/*--15699-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--15699-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)*/
/*--15699-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--15699-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--15699-- REDIR: 0x40d5200 (strcpy) redirected to 0x40260b0 (strcpy)*/
/*booster to roasted: */
/*--15699-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*--15699-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--15699-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)*/
/*booster rooster roaster roasted */

/*==============================*/

/*coastal to postal: */
/*no solution*/

/*==============================*/

/*==15699== */
/*==15699== HEAP SUMMARY:*/
/*==15699==     in use at exit: 0 bytes in 0 blocks*/
/*==15699==   total heap usage: 60 allocs, 60 frees, 587 bytes allocated*/
/*==15699== */
/*==15699== All heap blocks were freed -- no leaks are possible*/
/*==15699== */
/*==15699== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--15699-- */
/*--15699-- used_suppression:     13 dl-hack3-cond-1*/
/*==15699== */
/*==15699== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

