/*see README for original credits */

#include"tree.h"
#include<ctype.h>
#include<stdio.h>
#include<string.h>

static void print_item_int(const tree* t) {
  printf("key = %d\n", *(int*)t->key);
}

static void print_item_str(const tree* t) {
  printf("key = %s\n", (char*)t->key);
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

static void int_test(tree** t) {
  /*root  */
  int i = 4;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);
  /*level 1 node, left child of root*/
  i = 1;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);
  /*level 1 node, right child of root*/
  i = 8;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, left child of 1*/
  i = 2;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, right child of 1*/
  i = 3;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, left child of 8*/
  i = 16;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, right child of 8*/
  i = 32;
  insert_tree(t, &i, sizeof(int), &i, sizeof(int), NULL, compare_keys_int);

  printf("\n** IN ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_int);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_int);
  printf("\n** POST ORDER **\n");
  print_tree(*t, POST_ORDER, print_item_int);
  
  printf("\ndeleting root: 4\n");
  i = 4;
  delete_tree(t, &i, compare_keys_int);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_int);
  
  printf("\ndeleting level 1 node: 8\n");
  i = 8;
  delete_tree(t, &i, compare_keys_int);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_int);

  printf("\ndeleting level 2 (leaf) node: 32\n");
  i = 32;
  delete_tree(t, &i, compare_keys_int);

  printf("\n** IN ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_int);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_int);
  printf("\n** POST ORDER **\n");
  print_tree(*t, POST_ORDER, print_item_int);
}

static void str_test(tree** t) {
  char* s[] = {"hello", "world!", "goodbye", "for now!", "still", "here?"};
  int i, sz = sizeof(s) / sizeof(s[0]);
  
  for(i = 0; i < sz; i++ )
    insert_tree(t, s[i], strlen(s[i])+1, s[i], strlen(s[i])+1, NULL, 
      compare_keys_str);

  printf("\n** IN ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_str);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_str);
  printf("\n** POST ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_str);
  
  printf("\ndeleting root: %s\n", s[0]);
  delete_tree(t, s[0], compare_keys_str);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_str);

  printf("\ndeleting level 1 node: %s\n", s[1]);
  delete_tree(t, s[1], compare_keys_str);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_str);

  printf("\ndeleting level 1 node: %s\n", s[2]);
  delete_tree(t, s[2], compare_keys_str);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, PRE_ORDER, print_item_str);

  printf("\ndeleting level 2 (leaf) node: %s\n", s[sz-1]);
  delete_tree(t, s[sz-1], compare_keys_str);

  printf("\n** IN ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_str);
  printf("\n** PRE ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_str);
  printf("\n** POST ORDER **\n");
  print_tree(*t, IN_ORDER, print_item_str);
}

int main(void) {
  tree* t; /* tree under construction */
  init_tree(&t);
  int_test(&t);
  clear_tree(&t);
  str_test(&t);
  clear_tree(&t);
  return 0;
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make tree-demo && valgrind --leak-check=yes -v ./tree-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o tree.o tree.c*/
/*tree.c: In function ‘insert_tree’:*/
/*tree.c:71: warning: cast discards qualifiers from pointer target type*/
/*tree.c: In function ‘find_minimum’:*/
/*tree.c:116: warning: cast discards qualifiers from pointer target type*/
/*tree.c: In function ‘delete_tree’:*/
/*tree.c:161: warning: cast discards qualifiers from pointer target type*/
/*tree.c: In function ‘delete_root’:*/
/*tree.c:199: warning: cast discards qualifiers from pointer target type*/
/*tree.c:201: warning: cast discards qualifiers from pointer target type*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o tree-demo.o tree-demo.c*/
/*tree-demo.c: In function ‘int_test’:*/
/*tree-demo.c:46: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:49: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:52: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:55: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:58: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:61: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:64: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:67: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:69: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:71: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:75: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:77: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:81: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:83: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:87: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’*/
/*tree-demo.c:90: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:92: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:94: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c: In function ‘str_test’:*/
/*tree-demo.c:98: warning: initialization discards qualifiers from pointer target type*/
/*tree-demo.c:98: warning: initialization discards qualifiers from pointer target type*/
/*tree-demo.c:98: warning: initialization discards qualifiers from pointer target type*/
/*tree-demo.c:98: warning: initialization discards qualifiers from pointer target type*/
/*tree-demo.c:98: warning: initialization discards qualifiers from pointer target type*/
/*tree-demo.c:98: warning: initialization discards qualifiers from pointer target type*/
/*tree-demo.c:103: warning: passing argument 7 of ‘insert_tree’ from incompatible pointer type*/
/*tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*tree-demo.c:106: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:108: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:110: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:113: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*tree-demo.c:115: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:118: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*tree-demo.c:120: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:123: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*tree-demo.c:125: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:128: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type*/
/*tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’*/
/*tree-demo.c:131: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:133: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*tree-demo.c:135: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type*/
/*tree.h:32: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’*/
/*gcc -lm  -o tree-demo tree.o tree-demo.o */
/*==12345== Memcheck, a memory error detector*/
/*==12345== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==12345== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==12345== Command: ./tree-demo*/
/*==12345== */
/*--12345-- Valgrind options:*/
/*--12345--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--12345--    --leak-check=yes*/
/*--12345--    -v*/
/*--12345-- Contents of /proc/version:*/
/*--12345--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--12345-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--12345-- Page sizes: currently 4096, max supported 4096*/
/*--12345-- Valgrind library directory: /usr/lib/valgrind*/
/*--12345-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--12345-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--12345-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--12345-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--12345-- Reading syms from /home/osman/src/algorist/1.1/ds/tree-demo (0x8048000)*/
/*--12345-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--12345--    object doesn't have a dynamic symbol table*/
/*--12345-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--12345-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--12345-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--12345-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--12345-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==12345== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--12345--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--12345-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--12345-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--12345-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--12345-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--12345-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--12345-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--12345-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--12345-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--12345-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--12345-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--12345-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--12345-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--12345-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--12345-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/

/*** IN ORDER ***/
/*key = 1*/
/*key = 2*/
/*key = 3*/
/*key = 4*/
/*key = 8*/
/*key = 16*/
/*key = 32*/

/*** PRE ORDER ***/
/*key = 4*/
/*key = 1*/
/*key = 2*/
/*key = 3*/
/*key = 8*/
/*key = 16*/
/*key = 32*/

/*** POST ORDER ***/
/*key = 3*/
/*key = 2*/
/*key = 1*/
/*key = 32*/
/*key = 16*/
/*key = 8*/
/*key = 4*/

/*deleting root: 4*/
/*--12345-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/

/*** PRE ORDER ***/
/*key = 3*/
/*key = 1*/
/*key = 2*/
/*key = 8*/
/*key = 16*/
/*key = 32*/

/*deleting level 1 node: 8*/

/*** PRE ORDER ***/
/*key = 3*/
/*key = 1*/
/*key = 2*/
/*key = 16*/
/*key = 32*/

/*deleting level 2 (leaf) node: 32*/

/*** IN ORDER ***/
/*key = 1*/
/*key = 2*/
/*key = 3*/
/*key = 16*/

/*** PRE ORDER ***/
/*key = 3*/
/*key = 1*/
/*key = 2*/
/*key = 16*/

/*** POST ORDER ***/
/*key = 2*/
/*key = 1*/
/*key = 16*/
/*key = 3*/
/*--12345-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--12345-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)*/
/*--12345-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--12345-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)*/

/*** IN ORDER ***/
/*key = for now!*/
/*key = goodbye*/
/*key = hello*/
/*key = here?*/
/*key = still*/
/*key = world!*/

/*** PRE ORDER ***/
/*key = for now!*/
/*key = goodbye*/
/*key = hello*/
/*key = here?*/
/*key = still*/
/*key = world!*/

/*** POST ORDER ***/
/*key = for now!*/
/*key = goodbye*/
/*key = hello*/
/*key = here?*/
/*key = still*/
/*key = world!*/

/*deleting root: hello*/

/*** PRE ORDER ***/
/*key = goodbye*/
/*key = for now!*/
/*key = world!*/
/*key = still*/
/*key = here?*/

/*deleting level 1 node: world!*/

/*** PRE ORDER ***/
/*key = goodbye*/
/*key = for now!*/
/*key = still*/
/*key = here?*/

/*deleting level 1 node: goodbye*/

/*** PRE ORDER ***/
/*key = for now!*/
/*key = still*/
/*key = here?*/

/*deleting level 2 (leaf) node: here?*/

/*** IN ORDER ***/
/*key = for now!*/
/*key = still*/

/*** PRE ORDER ***/
/*key = for now!*/
/*key = still*/

/*** POST ORDER ***/
/*key = for now!*/
/*key = still*/
/*==12345== */
/*==12345== HEAP SUMMARY:*/
/*==12345==     in use at exit: 0 bytes in 0 blocks*/
/*==12345==   total heap usage: 45 allocs, 45 frees, 546 bytes allocated*/
/*==12345== */
/*==12345== All heap blocks were freed -- no leaks are possible*/
/*==12345== */
/*==12345== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--12345-- */
/*--12345-- used_suppression:     13 dl-hack3-cond-1*/
/*==12345== */
/*==12345== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

