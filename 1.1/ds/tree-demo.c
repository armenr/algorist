/*see README for original credits */

#include"tree.h"
#include<ctype.h>
#include<stdio.h>

static void print_item(tree* t) {
/*value not printing correctly, dereferencing a null pointer*/
/*  printf("node=%d value=%d\n", t->node, (int*)t->item);*/
  printf("node=%d\n", t->node);
}

int main(void) {
  const tree* tmp; /* returned tree from search */
  tree* t; /* tree under construction */
  init_tree(&t);
 
  char c; /* input character */

  printf("tree options: (p)rint, (s)earch, (i)nsert, (d)elete (q)uit\n");

	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) {
    int d; /* input item */
  
    if(tolower(c) == 'p') 
      print_tree(t, IN_ORDER, print_item);
  
    else if(tolower(c) == 'i') {
		  printf("insert item: ");
      scanf("%d", &d);
      printf("new item: %d\n", d);
      insert_tree(&t, d, &d, NULL, sizeof(int));

    } else if(tolower(c) == 's') {
		  printf("search for item: ");
      scanf("%d", &d);
      tmp = search_tree(t, d);
      
      printf("item %d ", d);
      if(tmp != NULL)
        printf("found\n");
      else
        printf("not found\n");

    } else if(tolower(c) == 'd') {
		  printf("delete item: ");
      scanf("%d", &d);
      tmp = search_tree(t, d);
      
      printf("item %d ", d);
      if(tmp != NULL) {
        delete_tree(&t, d);
				printf("deleted\n");
      }
      else
        printf("not found\n");
    }
  }
  
  clear_tree(&t);
  return 0;
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make tree-demo && valgrind --leak-check=yes -v ./tree-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o tree.o tree.c*/
/*tree.c: In function ‘insert_tree’:*/
/*tree.c:61: warning: cast discards qualifiers from pointer target type*/
/*tree.c: In function ‘find_minimum’:*/
/*tree.c:104: warning: cast discards qualifiers from pointer target type*/
/*tree.c: In function ‘delete_tree’:*/
/*tree.c:148: warning: cast discards qualifiers from pointer target type*/
/*tree.c: In function ‘delete_root’:*/
/*tree.c:183: warning: cast discards qualifiers from pointer target type*/
/*tree.c:185: warning: cast discards qualifiers from pointer target type*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o tree-demo.o tree-demo.c*/
/*tree-demo.c: In function ‘main’:*/
/*tree-demo.c:26: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘void (*)(void *)’ but argument is of type ‘void (*)(struct tree *)’*/
/*gcc -lm  -o tree-demo tree.o tree-demo.o */
/*==18622== Memcheck, a memory error detector*/
/*==18622== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==18622== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==18622== Command: ./tree-demo*/
/*==18622== */
/*--18622-- Valgrind options:*/
/*--18622--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--18622--    --leak-check=yes*/
/*--18622--    -v*/
/*--18622-- Contents of /proc/version:*/
/*--18622--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--18622-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--18622-- Page sizes: currently 4096, max supported 4096*/
/*--18622-- Valgrind library directory: /usr/lib/valgrind*/
/*--18622-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--18622-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--18622-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--18622-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--18622-- Reading syms from /home/osman/src/algorist/1.1/ds/tree-demo (0x8048000)*/
/*--18622-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--18622--    object doesn't have a dynamic symbol table*/
/*--18622-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--18622-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--18622-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--18622-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--18622-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==18622== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--18622--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--18622-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--18622-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--18622-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--18622-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--18622-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--18622-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--18622-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--18622-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--18622-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--18622-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--18622-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*tree options: (p)rint, (s)earch, (i)nsert, (d)elete (q)uit*/
/*i*/
/*--18622-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*insert item: 4*/
/*new item: 4*/
/*--18622-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--18622-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--18622-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*2*/
/*q*/
/*--18622-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*==18622== */
/*==18622== HEAP SUMMARY:*/
/*==18622==     in use at exit: 0 bytes in 0 blocks*/
/*==18622==   total heap usage: 2 allocs, 2 frees, 24 bytes allocated*/
/*==18622== */
/*==18622== All heap blocks were freed -- no leaks are possible*/
/*==18622== */
/*==18622== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--18622-- */
/*--18622-- used_suppression:     13 dl-hack3-cond-1*/
/*==18622== */
/*==18622== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*osman@osman-dev:~/src/algorist/1.1/ds$ make tree-demo && valgrind --leak-check=yes -v ./tree-demo*/
/*make: `tree-demo' is up to date.*/
/*==18632== Memcheck, a memory error detector*/
/*==18632== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==18632== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==18632== Command: ./tree-demo*/
/*==18632== */
/*--18632-- Valgrind options:*/
/*--18632--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--18632--    --leak-check=yes*/
/*--18632--    -v*/
/*--18632-- Contents of /proc/version:*/
/*--18632--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--18632-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--18632-- Page sizes: currently 4096, max supported 4096*/
/*--18632-- Valgrind library directory: /usr/lib/valgrind*/
/*--18632-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--18632-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--18632-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--18632-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--18632-- Reading syms from /home/osman/src/algorist/1.1/ds/tree-demo (0x8048000)*/
/*--18632-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--18632--    object doesn't have a dynamic symbol table*/
/*--18632-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--18632-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--18632-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--18632-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--18632-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==18632== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--18632--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--18632-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--18632-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--18632-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--18632-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--18632-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--18632-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--18632-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--18632-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--18632-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--18632-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--18632-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*tree options: (p)rint, (s)earch, (i)nsert, (d)elete (q)uit*/
/*i*/
/*--18632-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*insert item: 4*/
/*new item: 4*/
/*--18632-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--18632-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--18632-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*i*/
/*insert item: 2*/
/*new item: 2*/
/*i*/
/*insert item: 8*/
/*new item: 8*/
/*p*/
/*node=2*/
/*node=4*/
/*node=8*/
/*i*/
/*insert item: 3*/
/*new item: 3*/
/*i*/
/*insert item: 1*/
/*new item: 1*/
/*i*/
/*insert item: 9*/
/*new item: 9*/
/*i*/
/*insert item: 10*/
/*new item: 10*/
/*p*/
/*node=1*/
/*node=2*/
/*node=3*/
/*node=4*/
/*node=8*/
/*node=9*/
/*node=10*/
/*d*/
/*delete item: 4*/
/*--18632-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*item 4 deleted*/
/*p*/
/*node=1*/
/*node=2*/
/*node=3*/
/*node=8*/
/*node=9*/
/*node=10*/
/*d*/
/*delete item: 1*/
/*item 1 deleted*/
/*d*/
/*delete item: 3*/
/*item 3 deleted*/
/*p*/
/*node=2*/
/*node=8*/
/*node=9*/
/*node=10*/
/*d*/
/*delete item: 8*/
/*item 8 deleted*/
/*p*/
/*node=2*/
/*node=9*/
/*node=10*/
/*q*/
/*==18632== */
/*==18632== HEAP SUMMARY:*/
/*==18632==     in use at exit: 0 bytes in 0 blocks*/
/*==18632==   total heap usage: 16 allocs, 16 frees, 176 bytes allocated*/
/*==18632== */
/*==18632== All heap blocks were freed -- no leaks are possible*/
/*==18632== */
/*==18632== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--18632-- */
/*--18632-- used_suppression:     13 dl-hack3-cond-1*/
/*==18632== */
/*==18632== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

