/*see README for original credits */

#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include"tree.h"
#include"util.h"

static void print_item_int(const tree* t) {
  printf("key = %d\n", *(int*)t->key);
}

static void print_item_str(const tree* t) {
  printf("key = %s\titem = %s\n", (char*)t->key, (char*)t->item);
}

static void int_test(tree** t) {
  /*root  */
  int i = 4;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);
  /*level 1 node, left child of root*/
  i = 1;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);
  /*level 1 node, right child of root*/
  i = 8;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, left child of 1*/
  i = 2;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, right child of 1*/
  i = 3;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, left child of 8*/
  i = 16;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);
  /*level 2 node, right child of 8*/
  i = 32;
  insert_tree(t, &i, sizeof(int), NULL, compare_keys_int);

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
  
  for(i = 0; i < sz; i++ ) {
    tree* n = insert_tree(t, s[i], strlen(s[i])+1, NULL, compare_keys_str);
    add_tree_item(n, s[i], strlen(s[i])+1); 
  }

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

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make tree-demo && valgrind --leak-check=yes -v ./tree-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o tree.o tree.c
tree.c: In function ‘insert_tree’:
tree.c:78: warning: cast discards qualifiers from pointer target type
tree.c: In function ‘find_minimum’:
tree.c:123: warning: cast discards qualifiers from pointer target type
tree.c: In function ‘delete_tree’:
tree.c:168: warning: cast discards qualifiers from pointer target type
tree.c: In function ‘delete_root’:
tree.c:206: warning: cast discards qualifiers from pointer target type
tree.c:208: warning: cast discards qualifiers from pointer target type
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o tree-demo.o tree-demo.c
tree-demo.c: In function ‘int_test’:
tree-demo.c:46: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:49: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:52: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:55: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:58: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:61: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:64: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:67: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:69: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:71: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:75: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:77: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:81: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:83: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:87: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
tree-demo.c:90: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:92: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:94: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c: In function ‘str_test’:
tree-demo.c:98: warning: initialization discards qualifiers from pointer target type
tree-demo.c:98: warning: initialization discards qualifiers from pointer target type
tree-demo.c:98: warning: initialization discards qualifiers from pointer target type
tree-demo.c:98: warning: initialization discards qualifiers from pointer target type
tree-demo.c:98: warning: initialization discards qualifiers from pointer target type
tree-demo.c:98: warning: initialization discards qualifiers from pointer target type
tree-demo.c:102: warning: passing argument 5 of ‘insert_tree’ from incompatible pointer type
tree.h:29: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
tree-demo.c:107: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:109: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:111: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:114: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
tree-demo.c:116: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:119: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
tree-demo.c:121: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:124: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
tree-demo.c:126: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:129: warning: passing argument 3 of ‘delete_tree’ from incompatible pointer type
tree.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
tree-demo.c:132: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:134: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
tree-demo.c:136: warning: passing argument 3 of ‘print_tree’ from incompatible pointer type
tree.h:31: note: expected ‘void (*)(const void *)’ but argument is of type ‘void (*)(const struct tree *)’
gcc -lm  -o tree-demo tree.o tree-demo.o 
==15646== Memcheck, a memory error detector
==15646== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==15646== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==15646== Command: ./tree-demo
==15646== 
--15646-- Valgrind options:
--15646--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--15646--    --leak-check=yes
--15646--    -v
--15646-- Contents of /proc/version:
--15646--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--15646-- Arch and hwcaps: X86, x86-sse1-sse2
--15646-- Page sizes: currently 4096, max supported 4096
--15646-- Valgrind library directory: /usr/lib/valgrind
--15646-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--15646-- Reading debug info from /lib/ld-2.11.1.so ..
--15646-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--15646-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--15646-- Reading syms from /home/osman/src/algorist/1.1/ds/tree-demo (0x8048000)
--15646-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--15646--    object doesn't have a dynamic symbol table
--15646-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--15646-- Reading suppressions file: /usr/lib/valgrind/default.supp
--15646-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--15646-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--15646-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==15646== WARNING: new redirection conflicts with existing -- ignoring it
--15646--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--15646-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--15646-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--15646-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--15646-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--15646-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--15646-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--15646-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--15646-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--15646-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--15646-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--15646-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--15646-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--15646-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--15646-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)

** IN ORDER **
key = 1
key = 2
key = 3
key = 4
key = 8
key = 16
key = 32

** PRE ORDER **
key = 4
key = 1
key = 2
key = 3
key = 8
key = 16
key = 32

** POST ORDER **
key = 3
key = 2
key = 1
key = 32
key = 16
key = 8
key = 4

deleting root: 4
--15646-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)

** PRE ORDER **
key = 3
key = 1
key = 2
key = 8
key = 16
key = 32

deleting level 1 node: 8

** PRE ORDER **
key = 3
key = 1
key = 2
key = 16
key = 32

deleting level 2 (leaf) node: 32

** IN ORDER **
key = 1
key = 2
key = 3
key = 16

** PRE ORDER **
key = 3
key = 1
key = 2
key = 16

** POST ORDER **
key = 2
key = 1
key = 16
key = 3
--15646-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--15646-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)
--15646-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--15646-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)

** IN ORDER **
key = for now!	item = for now!
key = goodbye	item = goodbye
key = hello	item = hello
key = here?	item = here?
key = still	item = still
key = world!	item = world!

** PRE ORDER **
key = for now!	item = for now!
key = goodbye	item = goodbye
key = hello	item = hello
key = here?	item = here?
key = still	item = still
key = world!	item = world!

** POST ORDER **
key = for now!	item = for now!
key = goodbye	item = goodbye
key = hello	item = hello
key = here?	item = here?
key = still	item = still
key = world!	item = world!

deleting root: hello

** PRE ORDER **
key = goodbye	item = goodbye
key = for now!	item = for now!
key = world!	item = world!
key = still	item = still
key = here?	item = here?

deleting level 1 node: world!

** PRE ORDER **
key = goodbye	item = goodbye
key = for now!	item = for now!
key = still	item = still
key = here?	item = here?

deleting level 1 node: goodbye

** PRE ORDER **
key = for now!	item = for now!
key = still	item = still
key = here?	item = here?

deleting level 2 (leaf) node: here?

** IN ORDER **
key = for now!	item = for now!
key = still	item = still

** PRE ORDER **
key = for now!	item = for now!
key = still	item = still

** POST ORDER **
key = for now!	item = for now!
key = still	item = still
==15646== 
==15646== HEAP SUMMARY:
==15646==     in use at exit: 0 bytes in 0 blocks
==15646==   total heap usage: 37 allocs, 37 frees, 514 bytes allocated
==15646== 
==15646== All heap blocks were freed -- no leaks are possible
==15646== 
==15646== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--15646-- 
--15646-- used_suppression:     13 dl-hack3-cond-1
==15646== 
==15646== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
