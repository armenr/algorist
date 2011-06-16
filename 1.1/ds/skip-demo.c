/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include"skip-list.h"
#include"util.h"

static void print_item_int(const skipnode* s) {
  printf("%d", *(int*)s->key);
}

static void print_item_str(const skipnode* s) {
  printf("%s", (char*)s->key);
}

static void int_test(skipset* ss) {
  print_skipset(ss, print_item_int);

  int i = 5;
  insert_skipnode(ss, &i, sizeof(i), compare_keys_int);
  i = 10;
  insert_skipnode(ss, &i, sizeof(i), compare_keys_int);
  i = 7;
  insert_skipnode(ss, &i, sizeof(i), compare_keys_int);
  insert_skipnode(ss, &i, sizeof(i), compare_keys_int);
  i = 6;
  insert_skipnode(ss, &i, sizeof(i), compare_keys_int);

  print_skipset(ss, print_item_int);

  i = 7;
  if(contains_skipnode(ss, &i, compare_keys_int) != NULL) 
    printf("7 is in the list\n");

  delete_skipnode(ss, &i, compare_keys_int);
  print_skipset(ss, print_item_int);

  if(contains_skipnode(ss, &i, compare_keys_int) == NULL) 
    printf("7 has been deleted\n");

  i = 5;
  delete_skipnode(ss, &i, compare_keys_int);
  i = 6;
  delete_skipnode(ss, &i, compare_keys_int);
  i = 10;
  delete_skipnode(ss, &i, compare_keys_int);
  
  print_skipset(ss, print_item_int);
}

static void str_test(skipset* ss) {
  print_skipset(ss, print_item_str);

  char* s[] = {"hello", "world!", "goodbye", "for now!", "still", "here?"};
  int i, sz = sizeof(s) / sizeof(s[0]);
  
  for(i = 0; i < sz; i++ ) {
    add_skipset_item(ss, s[i], strlen(s[i])+1);
    insert_skipnode(ss, s[i], strlen(s[i])+1, compare_keys_str);
  }

  /*duplicate not added*/
  insert_skipnode(ss, s[2], strlen(s[2])+1, compare_keys_str);

  print_skipset(ss, print_item_str);

  if(contains_skipnode(ss, s[2], compare_keys_str) != NULL) 
    printf("%s is in the list\n", s[2]);

  delete_skipnode(ss, s[2], compare_keys_str);
  print_skipset(ss, print_item_str);

  if(contains_skipnode(ss, s[2], compare_keys_str) == NULL) 
    printf("%s has been deleted\n", s[2]);

  for(i = 0; i < sz; i++ )
    delete_skipnode(ss, s[i], compare_keys_str);

  print_skipset(ss, print_item_str);
}

int main(void) {
  skipset* ss;
  init_skipset(&ss);
  int_test(ss);
  str_test(ss);
  clear_skipset(ss);
  return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make skip-demo && valgrind --leak-check=yes -v ./skip-demo 
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o skip-list.o skip-list.c
skip-list.c: In function ‘delete_skipnode’:
skip-list.c:149: warning: cast discards qualifiers from pointer target type
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o skip-demo.o skip-demo.c
skip-demo.c: In function ‘int_test’:
skip-demo.c:43: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c:46: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:48: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:50: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:51: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:53: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:55: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c:58: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:43: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:61: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type
skip-list.h:47: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:62: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c:64: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:43: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:68: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type
skip-list.h:47: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:70: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type
skip-list.h:47: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:72: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type
skip-list.h:47: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
skip-demo.c:74: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c: In function ‘str_test’:
skip-demo.c:78: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c:80: warning: initialization discards qualifiers from pointer target type
skip-demo.c:80: warning: initialization discards qualifiers from pointer target type
skip-demo.c:80: warning: initialization discards qualifiers from pointer target type
skip-demo.c:80: warning: initialization discards qualifiers from pointer target type
skip-demo.c:80: warning: initialization discards qualifiers from pointer target type
skip-demo.c:80: warning: initialization discards qualifiers from pointer target type
skip-demo.c:84: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
skip-demo.c:87: warning: passing argument 4 of ‘insert_skipnode’ from incompatible pointer type
skip-list.h:45: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
skip-demo.c:89: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c:91: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:43: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
skip-demo.c:94: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type
skip-list.h:47: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
skip-demo.c:95: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
skip-demo.c:97: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type
skip-list.h:43: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
skip-demo.c:101: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type
skip-list.h:47: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
skip-demo.c:103: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type
skip-list.h:52: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’
gcc -lm  -o skip-demo skip-list.o skip-demo.o
==12746== Memcheck, a memory error detector
==12746== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==12746== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==12746== Command: ./skip-demo
==12746== 
--12746-- Valgrind options:
--12746--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--12746--    --leak-check=yes
--12746--    -v
--12746-- Contents of /proc/version:
--12746--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--12746-- Arch and hwcaps: X86, x86-sse1-sse2
--12746-- Page sizes: currently 4096, max supported 4096
--12746-- Valgrind library directory: /usr/lib/valgrind
--12746-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--12746-- Reading debug info from /lib/ld-2.11.1.so ..
--12746-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--12746-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--12746-- Reading syms from /home/osman/src/algorist/1.1/ds/skip-demo (0x8048000)
--12746-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--12746--    object doesn't have a dynamic symbol table
--12746-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--12746-- Reading suppressions file: /usr/lib/valgrind/default.supp
--12746-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--12746-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--12746-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==12746== WARNING: new redirection conflicts with existing -- ignoring it
--12746--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--12746-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--12746-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--12746-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--12746-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--12746-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--12746-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--12746-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--12746-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--12746-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--12746-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--12746-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--12746-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--12746-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--12746-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--12746-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
level 0:
{}
level 3:
{10}
level 2:
{7, 10}
level 1:
{7, 10}
level 0:
{5, 6, 7, 10}
7 is in the list
--12746-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
level 3:
{10}
level 2:
{10}
level 1:
{10}
level 0:
{5, 6, 10}
7 has been deleted
level 0:
{}
level 0:
{}
--12746-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--12746-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)
--12746-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--12746-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)
level 1:
{for now!, hello, here?, world!}
level 0:
{for now!, goodbye, hello, here?, still, world!}
goodbye is in the list
level 1:
{for now!, hello, here?, world!}
level 0:
{for now!, hello, here?, still, world!}
goodbye has been deleted
level 0:
{}
==12746== 
==12746== HEAP SUMMARY:
==12746==     in use at exit: 0 bytes in 0 blocks
==12746==   total heap usage: 45 allocs, 45 frees, 514 bytes allocated
==12746== 
==12746== All heap blocks were freed -- no leaks are possible
==12746== 
==12746== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--12746-- 
--12746-- used_suppression:     13 dl-hack3-cond-1
==12746== 
==12746== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
