/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include"hash-fn.h"
#include"hash-tbl.h"
#include"util.h"

static void str_test() {
  char* co[] = {"France", "England", "Spain"};
  char* ca[] = {"Paris", "London", "Madrid"};
  int sz = (int)(sizeof(co) / sizeof(co[0]));
  
	hashtbl* h;
  init_hashtbl(&h, 128, sdbm_hash);

  int i;
  for(i = 0; i < sz; i++)
  	insert_hashtbl(h, co[i], strlen(co[i])+1, ca[i], strlen(ca[i])+1, 
  	  compare_keys_str);

	printf("After insert:\n");
	hashnode* n = get_hashtbl(h, "France", compare_keys_str);
	printf("France: %s\n", n ? (char*)n->item : "not found");

	insert_hashtbl(h, co[0], strlen(co[0])+1, "PARIS", 6, compare_keys_str);
	printf("After update:\n");
	printf("France: %s\n", n ? (char*)n->item : "not found");

	n = get_hashtbl(h, "Italy", compare_keys_str);
	printf("Italy: %s\n", n ? (char*)n->item : "not found");

	remove_hashtbl(h, "Spain", compare_keys_str);
	printf("After remove:\n");
	n = get_hashtbl(h, "Spain", compare_keys_str);
	printf("Spain: %s\n", n ? (char*)n->item : "not found");

	resize_hashtbl(h, 256);
	printf("After resize:\n");
	n = get_hashtbl(h, "England", compare_keys_str);
	printf("England: %s\n", n ? (char*)n->item : "not found");

	clear_hashtbl(h);
}

static void int_test() {
	hashtbl* h;
  init_hashtbl(&h, 128, bernstein_hash);

  int i = 1;
	insert_hashtbl(h, &i, sizeof(int), "one", 4, compare_keys_int);
  i = 2;
	insert_hashtbl(h, &i, sizeof(int), "two", 4, compare_keys_int);
  i = 4;
	insert_hashtbl(h, &i, sizeof(int), "four", 5, compare_keys_int);

  i = 1;
	hashnode* n = get_hashtbl(h, &i, compare_keys_int);
	printf("%d: %s\n", i, n ? (char*)n->item : "not found");

	insert_hashtbl(h, &i, sizeof(int), "ONE", 4, compare_keys_int);
	printf("After update:\n");
	printf("%d: %s\n", i, n ? (char*)n->item : "not found");

  i = 2;
	remove_hashtbl(h, &i, compare_keys_int);
	printf("After remove:\n");
	n = get_hashtbl(h, &i, compare_keys_int);
	printf("%d: %s\n", i, n ? (char*)n->item : "not found");

	resize_hashtbl(h, 64);
	printf("After resize:\n");
	i = 4;
	n = get_hashtbl(h, &i, compare_keys_int);
	printf("%d: %s\n", i, n ? (char*)n->item : "not found");

	clear_hashtbl(h);
}

int main(void) {
  str_test();
  int_test();
	return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make hash-demo && valgrind --leak-check=yes -v ./hash-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o hash-tbl.o hash-tbl.c
hash-tbl.c: In function ‘remove_hashtbl’:
hash-tbl.c:98: warning: cast discards qualifiers from pointer target type
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o hash-demo.o hash-demo.c
hash-demo.c:35: warning: function declaration isn’t a prototype
hash-demo.c: In function ‘str_test’:
hash-demo.c:36: warning: initialization discards qualifiers from pointer target type
hash-demo.c:36: warning: initialization discards qualifiers from pointer target type
hash-demo.c:36: warning: initialization discards qualifiers from pointer target type
hash-demo.c:37: warning: initialization discards qualifiers from pointer target type
hash-demo.c:37: warning: initialization discards qualifiers from pointer target type
hash-demo.c:37: warning: initialization discards qualifiers from pointer target type
hash-demo.c:46: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
hash-tbl.h:27: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c:49: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c:52: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
hash-tbl.h:27: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c:56: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c:59: warning: passing argument 3 of ‘remove_hashtbl’ from incompatible pointer type
hash-tbl.h:30: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c:61: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c:66: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
hash-demo.c: At top level:
hash-demo.c:72: warning: function declaration isn’t a prototype
hash-demo.c: In function ‘int_test’:
hash-demo.c:77: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
hash-tbl.h:27: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:79: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
hash-tbl.h:27: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:81: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
hash-tbl.h:27: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:84: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:87: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
hash-tbl.h:27: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:92: warning: passing argument 3 of ‘remove_hashtbl’ from incompatible pointer type
hash-tbl.h:30: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:94: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
hash-demo.c:100: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
hash-tbl.h:25: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const int *, const int *)’
gcc -lm  -o hash-demo hash-tbl.o hash-demo.o hash-fn.o
==3278== Memcheck, a memory error detector
==3278== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==3278== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==3278== Command: ./hash-demo
==3278== 
--3278-- Valgrind options:
--3278--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--3278--    --leak-check=yes
--3278--    -v
--3278-- Contents of /proc/version:
--3278--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--3278-- Arch and hwcaps: X86, x86-sse1-sse2
--3278-- Page sizes: currently 4096, max supported 4096
--3278-- Valgrind library directory: /usr/lib/valgrind
--3278-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--3278-- Reading debug info from /lib/ld-2.11.1.so ..
--3278-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--3278-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--3278-- Reading syms from /home/osman/src/algorist/1.1/ds/hash-demo (0x8048000)
--3278-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--3278--    object doesn't have a dynamic symbol table
--3278-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--3278-- Reading suppressions file: /usr/lib/valgrind/default.supp
--3278-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--3278-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--3278-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==3278== WARNING: new redirection conflicts with existing -- ignoring it
--3278--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--3278-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--3278-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--3278-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--3278-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--3278-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--3278-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--3278-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--3278-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--3278-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--3278-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--3278-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--3278-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--3278-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--3278-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--3278-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--3278-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)
--3278-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
After insert:
--3278-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--3278-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)
France: Paris
--3278-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
After update:
France: PARIS
Italy: not found
After remove:
Spain: not found
After resize:
England: London
1: one
After update:
1: ONE
After remove:
2: not found
After resize:
4: four
==3278== 
==3278== HEAP SUMMARY:
==3278==     in use at exit: 0 bytes in 0 blocks
==3278==   total heap usage: 26 allocs, 26 frees, 2,476 bytes allocated
==3278== 
==3278== All heap blocks were freed -- no leaks are possible
==3278== 
==3278== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--3278-- 
--3278-- used_suppression:     13 dl-hack3-cond-1
==3278== 
==3278== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/ 
