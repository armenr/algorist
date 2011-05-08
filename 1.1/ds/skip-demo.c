/*see README for original credits */

#include"skip-list.h"
#include <stdio.h>
#include <string.h>

static void print_item_int(const skipnode* s) {
  printf("%d", *(int*)s->key);
}

static void print_item_str(const skipnode* s) {
  printf("%s", (char*)s->key);
}

static int compare_keys_int(const int* key1, const int* key2) {
  if(key1 == NULL && key2 == NULL)
    return 0;
  else if(key1 == NULL)
    return -1;
  else if(key2 == NULL)
    return 1;

  int k1 = *key1, k2 = *key2;

  if(k1 == k2)
    return 0;

  return k1 - k2;
}

static int compare_keys_str(const char* key1, const char* key2) {
  if(key1 == NULL && key2 == NULL)
    return 0;
  else if(key1 == NULL)
    return -1;
  else if(key2 == NULL)
    return 1;

  return strcmp(key1, key2);
}

static void int_test(skipset* ss) {
  print_skipset(ss, print_item_int);

  int i = 5;
  insert_skipnode(ss, &i, sizeof(i), &i, sizeof(i), compare_keys_int);
  i = 10;
  insert_skipnode(ss, &i, sizeof(i), &i, sizeof(i), compare_keys_int);
  i = 7;
  insert_skipnode(ss, &i, sizeof(i), &i, sizeof(i), compare_keys_int);
  insert_skipnode(ss, &i, sizeof(i), &i, sizeof(i), compare_keys_int);
  i = 6;
  insert_skipnode(ss, &i, sizeof(i), &i, sizeof(i), compare_keys_int);

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
  
  for(i = 0; i < sz; i++ )
    insert_skipnode(ss, s[i], strlen(s[i])+1, s[i], strlen(s[i]+1), 
      compare_keys_str);

  /*duplicate not added*/
  insert_skipnode(ss, s[2], strlen(s[2])+1, s[2], strlen(s[2]+1), 
    compare_keys_str);

  print_skipset(ss, print_item_str);

  if(contains_skipnode(ss, s[2], compare_keys_int) != NULL) 
    printf("%s is in the list\n", s[2]);

  delete_skipnode(ss, s[2], compare_keys_str);
  print_skipset(ss, print_item_str);

  if(contains_skipnode(ss, s[2], compare_keys_int) == NULL) 
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
  clear_skipset(&ss);
  return 0;
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make skip-demo && valgrind --leak-check=yes -v ./skip-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o skip-list.o skip-list.c*/
/*skip-list.c: In function ‘contains_skipnode’:*/
/*skip-list.c:98: warning: pointer/integer type mismatch in conditional expression*/
/*skip-list.c:98: warning: initialization makes integer from pointer without a cast*/
/*skip-list.c:103: warning: pointer/integer type mismatch in conditional expression*/
/*skip-list.c:103: warning: assignment makes integer from pointer without a cast*/
/*skip-list.c: In function ‘delete_skipnode’:*/
/*skip-list.c:141: warning: passing argument 2 of ‘contains_skipnode’ makes pointer from integer without a cast*/
/*skip-list.c:89: note: expected ‘const void *’ but argument is of type ‘int’*/
/*skip-list.c:141: warning: cast discards qualifiers from pointer target type*/
/*skip-list.c: In function ‘insert_node’:*/
/*skip-list.c:226: warning: pointer/integer type mismatch in conditional expression*/
/*skip-list.c:226: warning: initialization makes integer from pointer without a cast*/
/*skip-list.c:231: warning: pointer/integer type mismatch in conditional expression*/
/*skip-list.c:231: warning: assignment makes integer from pointer without a cast*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o skip-demo.o skip-demo.c*/
/*skip-demo.c: In function ‘int_test’:*/
/*skip-demo.c:43: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c:46: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:48: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:50: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:51: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:53: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:55: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c:58: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:41: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:61: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘int *’*/
/*skip-demo.c:61: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:62: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c:64: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:41: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:68: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘int *’*/
/*skip-demo.c:68: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:70: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘int *’*/
/*skip-demo.c:70: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:72: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘int *’*/
/*skip-demo.c:72: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:74: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c: In function ‘str_test’:*/
/*skip-demo.c:78: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c:80: warning: initialization discards qualifiers from pointer target type*/
/*skip-demo.c:80: warning: initialization discards qualifiers from pointer target type*/
/*skip-demo.c:80: warning: initialization discards qualifiers from pointer target type*/
/*skip-demo.c:80: warning: initialization discards qualifiers from pointer target type*/
/*skip-demo.c:82: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:84: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:86: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:89: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:91: warning: passing argument 6 of ‘insert_skipnode’ from incompatible pointer type*/
/*skip-list.h:43: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:93: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c:95: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:41: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:98: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘char *’*/
/*skip-demo.c:98: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:99: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*skip-demo.c:101: warning: passing argument 3 of ‘contains_skipnode’ from incompatible pointer type*/
/*skip-list.h:41: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*skip-demo.c:104: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘char *’*/
/*skip-demo.c:104: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:105: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘char *’*/
/*skip-demo.c:105: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:106: warning: passing argument 2 of ‘delete_skipnode’ makes integer from pointer without a cast*/
/*skip-list.h:46: note: expected ‘int’ but argument is of type ‘char *’*/
/*skip-demo.c:106: warning: passing argument 3 of ‘delete_skipnode’ from incompatible pointer type*/
/*skip-list.h:46: note: expected ‘int * (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*skip-demo.c:108: warning: passing argument 2 of ‘print_skipset’ from incompatible pointer type*/
/*skip-list.h:50: note: expected ‘void * (*)(const void *)’ but argument is of type ‘void (*)(const struct skipnode *)’*/
/*gcc -lm  -o skip-demo skip-list.o skip-demo.o*/
/*==22197== Memcheck, a memory error detector*/
/*==22197== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==22197== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==22197== Command: ./skip-demo*/
/*==22197== */
/*--22197-- Valgrind options:*/
/*--22197--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--22197--    --leak-check=yes*/
/*--22197--    -v*/
/*--22197-- Contents of /proc/version:*/
/*--22197--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--22197-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--22197-- Page sizes: currently 4096, max supported 4096*/
/*--22197-- Valgrind library directory: /usr/lib/valgrind*/
/*--22197-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--22197-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--22197-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--22197-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--22197-- Reading syms from /home/osman/src/algorist/1.1/ds/skip-demo (0x8048000)*/
/*--22197-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--22197--    object doesn't have a dynamic symbol table*/
/*--22197-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--22197-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--22197-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--22197-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--22197-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==22197== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--22197--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--22197-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--22197-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--22197-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--22197-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--22197-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--22197-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--22197-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--22197-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--22197-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--22197-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--22197-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--22197-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)*/
/*--22197-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--22197-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--22197-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*level 0:*/
/*--22197-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*{}*/
/*level 2:*/
/*{7, 10}*/
/*level 1:*/
/*{7, 10}*/
/*level 0:*/
/*{5, 6, 7, 10}*/
/*7 is in the list*/
/*--22197-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*level 2:*/
/*{10}*/
/*level 1:*/
/*{10}*/
/*level 0:*/
/*{5, 6, 10}*/
/*7 has been deleted*/
/*level 0:*/
/*{}*/
/*level 0:*/
/*{}*/
/*--22197-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--22197-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)*/
/*--22197-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--22197-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)*/
/*level 1:*/
/*{world!}*/
/*level 0:*/
/*{for now!, goodbye, hello, world!}*/
/*goodbye is in the list*/
/*level 1:*/
/*{world!}*/
/*level 0:*/
/*{for now!, hello, world!}*/
/*goodbye has been deleted*/
/*level 0:*/
/*{}*/
/*==22197== */
/*==22197== HEAP SUMMARY:*/
/*==22197==     in use at exit: 0 bytes in 0 blocks*/
/*==22197==   total heap usage: 46 allocs, 46 frees, 476 bytes allocated*/
/*==22197== */
/*==22197== All heap blocks were freed -- no leaks are possible*/
/*==22197== */
/*==22197== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--22197-- */
/*--22197-- used_suppression:     13 dl-hack3-cond-1*/
/*==22197== */
/*==22197== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

