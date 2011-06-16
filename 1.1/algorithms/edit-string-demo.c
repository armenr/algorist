/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include"edit-string.h"

#define MAXLEN 100

int main(void) {
	char s[MAXLEN], t[MAXLEN];		/* input strings */
  s[0] = t[0] = ' ';
  scanf("%s %s", &(s[1]), &(t[1]));

	int i, j;
  edit_string e;

  init_edit_str(&e, strlen(s), strlen(t));
  
  e.row_init = row_init;
  e.col_init = col_init;
  e.goal_cell = goal_cell;
  e.match = match;
  
  printf("matching cost = %d \n", string_compare(&e, s, t));
  print_matrix(&e, s, t, true);
  printf("\n");
  print_matrix(&e, s, t, false);
  goal_cell(&e, &i, &j);
  printf("%d %d\n", i, j);
  
  e.delete_out = delete_out;
  e.insert_out = insert_out;
  e.match_out = match_out;
  
  reconstruct_path(&e, s, t, i, j);
  printf("\n");

  printf("\nsubstring\n");

  e.row_init = row_init_sub;
  e.col_init = col_init;
  e.goal_cell = goal_cell_sub;
  e.match = match;

  printf("matching cost = %d \n", string_compare(&e, s, t));
  print_matrix(&e, s, t, true);
  printf("\n");
  print_matrix(&e, s, t, false);
  goal_cell_sub(&e, &i, &j);
  printf("%d %d\n", i, j);

  e.delete_out = delete_out;
  e.insert_out = insert_out;
  e.match_out = match_out;
  
  reconstruct_path(&e, s, t, i, j);
  printf("\n");

  printf("\nlcs\n");

  e.row_init = row_init;
  e.col_init = col_init;
  e.goal_cell = goal_cell;
  e.match = match_lcs;

	int l = string_compare(&e, s, t);
	int lcs = (strlen(s) + strlen(t) - 2 - l) / 2;
	printf("length of longest common subsequence = %d\n", lcs);
  goal_cell_sub(&e, &i, &j);

  e.delete_out = delete_out_lcs;
  e.insert_out = insert_out_lcs;
  e.match_out = match_out_lcs;
  
  reconstruct_path(&e, s, t, i, j);
	printf("\n");

  clear_edit_str(&e);
	return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/algorithms$ make edit-string-demo && valgrind --leak-check=yes -v ./edit-string-demo < datafiles/stringedit-in
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o edit-string-demo.o edit-string-demo.c
edit-string-demo.c: In function ‘main’:
edit-string-demo.c:12: warning: ignoring return value of ‘scanf’, declared with attribute warn_unused_result
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o edit-string.o edit-string.c
edit-string.c: In function ‘delete_out’:
edit-string.c:186: warning: unused parameter ‘s’
edit-string.c:186: warning: unused parameter ‘i’
edit-string.c: In function ‘insert_out’:
edit-string.c:190: warning: unused parameter ‘t’
edit-string.c:190: warning: unused parameter ‘j’
edit-string.c: In function ‘insert_out_lcs’:
edit-string.c:206: warning: unused parameter ‘t’
edit-string.c:206: warning: unused parameter ‘j’
edit-string.c: In function ‘delete_out_lcs’:
edit-string.c:209: warning: unused parameter ‘s’
edit-string.c:209: warning: unused parameter ‘i’
edit-string.c: In function ‘indel’:
edit-string.c:216: warning: unused parameter ‘c’
gcc -lm  -o edit-string-demo edit-string-demo.o edit-string.o
==12595== Memcheck, a memory error detector
==12595== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==12595== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==12595== Command: ./edit-string-demo
==12595== 
--12595-- Valgrind options:
--12595--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--12595--    --leak-check=yes
--12595--    -v
--12595-- Contents of /proc/version:
--12595--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--12595-- Arch and hwcaps: X86, x86-sse1-sse2
--12595-- Page sizes: currently 4096, max supported 4096
--12595-- Valgrind library directory: /usr/lib/valgrind
--12595-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--12595-- Reading debug info from /lib/ld-2.11.1.so ..
--12595-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--12595-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--12595-- Reading syms from /home/osman/src/algorist/1.1/algorithms/edit-string-demo (0x8048000)
--12595-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--12595--    object doesn't have a dynamic symbol table
--12595-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--12595-- Reading suppressions file: /usr/lib/valgrind/default.supp
--12595-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--12595-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--12595-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==12595== WARNING: new redirection conflicts with existing -- ignoring it
--12595--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--12595-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--12595-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--12595-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--12595-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--12595-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--12595-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--12595-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--12595-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--12595-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--12595-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--12595-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--12595-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
matching cost = 5 
        y  o  u  -  s  h  o  u  l  d  -  n  o  t
 :   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
t:   1  1  2  3  4  5  6  7  8  9 10 11 12 13 13
h:   2  2  2  3  4  5  5  6  7  8  9 10 11 12 13
o:   3  3  2  3  4  5  6  5  6  7  8  9 10 11 12
u:   4  4  3  2  3  4  5  6  5  6  7  8  9 10 11
-:   5  5  4  3  2  3  4  5  6  6  7  7  8  9 10
s:   6  6  5  4  3  2  3  4  5  6  7  8  8  9 10
h:   7  7  6  5  4  3  2  3  4  5  6  7  8  9 10
a:   8  8  7  6  5  4  3  3  4  5  6  7  8  9 10
l:   9  9  8  7  6  5  4  4  4  4  5  6  7  8  9
t:  10 10  9  8  7  6  5  5  5  5  5  6  7  8  8
-:  11 11 10  9  8  7  6  6  6  6  6  5  6  7  8
n:  12 12 11 10  9  8  7  7  7  7  7  6  5  6  7
o:  13 13 12 11 10  9  8  7  8  8  8  7  6  5  6
t:  14 14 13 12 11 10  9  8  8  9  9  8  7  6  5

        y  o  u  -  s  h  o  u  l  d  -  n  o  t
 :  -1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
t:   2  0  0  0  0  0  0  0  0  0  0  0  0  0  0
h:   2  0  0  0  0  0  0  1  1  1  1  1  1  1  1
o:   2  0  0  0  0  0  0  0  1  1  1  1  1  0  1
u:   2  0  2  0  1  1  1  1  0  1  1  1  1  1  1
-:   2  0  2  2  0  1  1  1  1  0  0  0  1  1  1
s:   2  0  2  2  2  0  1  1  1  1  0  0  0  0  0
h:   2  0  2  2  2  2  0  1  1  1  1  1  1  0  0
a:   2  0  2  2  2  2  2  0  0  0  0  0  0  0  0
l:   2  0  2  2  2  2  2  0  0  0  1  1  1  1  1
t:   2  0  2  2  2  2  2  0  0  0  0  0  0  0  0
-:   2  0  2  2  0  2  2  0  0  0  0  0  1  1  1
n:   2  0  2  2  2  2  2  0  0  0  0  2  0  1  1
o:   2  0  0  2  2  2  2  0  0  0  0  2  2  0  1
t:   2  0  2  2  2  2  2  2  0  0  0  2  2  2  0
14 14
DSMMMMMISMSMMMM

substring
matching cost = 5 
        y  o  u  -  s  h  o  u  l  d  -  n  o  t
 :   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
t:   1  1  1  1  1  1  1  1  1  1  1  1  1  1  0
h:   2  2  2  2  2  2  1  2  2  2  2  2  2  2  1
o:   3  3  2  3  3  3  2  1  2  3  3  3  3  2  2
u:   4  4  3  2  3  4  3  2  1  2  3  4  4  3  3
-:   5  5  4  3  2  3  4  3  2  2  3  3  4  4  4
s:   6  6  5  4  3  2  3  4  3  3  3  4  4  5  5
h:   7  7  6  5  4  3  2  3  4  4  4  4  5  5  6
a:   8  8  7  6  5  4  3  3  4  5  5  5  5  6  6
l:   9  9  8  7  6  5  4  4  4  4  5  6  6  6  7
t:  10 10  9  8  7  6  5  5  5  5  5  6  7  7  6
-:  11 11 10  9  8  7  6  6  6  6  6  5  6  7  7
n:  12 12 11 10  9  8  7  7  7  7  7  6  5  6  7
o:  13 13 12 11 10  9  8  7  8  8  8  7  6  5  6
t:  14 14 13 12 11 10  9  8  8  9  9  8  7  6  5

        y  o  u  -  s  h  o  u  l  d  -  n  o  t
 :  -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
t:   2  0  0  0  0  0  0  0  0  0  0  0  0  0  0
h:   2  0  0  0  0  0  0  0  0  0  0  0  0  0  2
o:   2  0  0  0  0  0  2  0  1  0  0  0  0  0  2
u:   2  0  2  0  1  0  2  2  0  1  1  0  0  2  0
-:   2  0  2  2  0  1  1  2  2  0  0  0  1  2  0
s:   2  0  2  2  2  0  1  1  2  0  0  0  0  0  0
h:   2  0  2  2  2  2  0  1  1  0  0  0  0  0  0
a:   2  0  2  2  2  2  2  0  0  0  0  0  0  0  0
l:   2  0  2  2  2  2  2  0  0  0  1  0  0  0  0
t:   2  0  2  2  2  2  2  0  0  0  0  0  0  0  0
-:   2  0  2  2  0  2  2  0  0  0  0  0  1  1  2
n:   2  0  2  2  2  2  2  0  0  0  0  2  0  1  1
o:   2  0  0  2  2  2  2  0  0  0  0  2  2  0  1
t:   2  0  2  2  2  2  2  2  0  0  0  2  2  2  0
14 14
DSMMMMMISMSMMMM

lcs
length of longest common subsequence = 10
ou-shl-not
--12595-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
==12595== 
==12595== HEAP SUMMARY:
==12595==     in use at exit: 0 bytes in 0 blocks
==12595==   total heap usage: 1 allocs, 1 frees, 1,800 bytes allocated
==12595== 
==12595== All heap blocks were freed -- no leaks are possible
==12595== 
==12595== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--12595-- 
--12595-- used_suppression:     13 dl-hack3-cond-1
==12595== 
==12595== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
