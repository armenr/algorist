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
3.8.1 WERTYU
PC/UVa IDs: 110301/10082, Popularity: A, Success rate: high Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

O S, GOMR YPFSU/

Sample Output

I AM FINE TODAY.

*/

#define KEYS 50

#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include"../ds/hash-fn.h"
#include"../ds/hash-tbl.h"
#include"../ds/util.h"

static hashtbl* h;

static char* input = "O S, GOMR YPFSU//";

static void create_keys(void) {
  init_hashtbl(&h, 128, sdbm_hash);

  char* c[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P",
    "Q","R","S","T","U","","W","X","Y","Z"," ","0","1","2","3","4","5","6","7",
    "8","9","-","=","[","]",";","'",",",".","/"};

  char* d[] = {"A","V","X","S","W","D","F","G","U","H","J","K","N","B","I","O",
    "Q","E","A","R","Y","C","Q","Z","T","Z"," ","9","`","1","2","3","4","5","6",
    "7","8","0","-","P","[","L",";","M",",","."};

  int i, l = (int)(sizeof(c) / sizeof(c[0]));
  
  for(i = 0; i < l; i++) 
	  insert_hashtbl(h, c[i], strlen(c[i])+1, d[i], strlen(d[i])+1, 
	    compare_keys_str);
}

static void clean_up(void) {
	clear_hashtbl(h);
}

static void print_correct_output(void) {
  int i; 
  for(i = 0; i < (int)strlen(input)-1; i++) 
    printf("%c", input[i]); /*original*/
  printf("\n");
      
  char s[2];  /*hash function maps on key strings*/      
  for(i = 0; i < (int)strlen(input)-1; i++) {
    s[0] = input[i]; s[1] = '\0';
	  hashnode* n = get_hashtbl(h, s, compare_keys_str);
    printf("%s", n ? (char*)n->item : "not found");
  }
  printf("\n");
}

int main(void) {
  create_keys();
  print_correct_output();      
  clean_up();    
  return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/challenges$ make wertyu && valgrind --leak-check=yes -v ./wertyu
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o wertyu.o wertyu.c
wertyu.c:44: warning: initialization discards qualifiers from pointer target type
wertyu.c: In function ‘create_keys’:
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:49: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:50: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:51: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:53: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:54: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:55: warning: initialization discards qualifiers from pointer target type
wertyu.c:61: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
../ds/hash-tbl.h:26: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
wertyu.c: In function ‘print_correct_output’:
wertyu.c:77: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
../ds/hash-tbl.h:24: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o ../ds/util.o ../ds/util.c
gcc -lm  -o wertyu wertyu.o ../ds/hash-tbl.o ../ds/hash-fn.o ../ds/util.o
==31866== Memcheck, a memory error detector
==31866== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==31866== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==31866== Command: ./wertyu
==31866== 
--31866-- Valgrind options:
--31866--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--31866--    --leak-check=yes
--31866--    -v
--31866-- Contents of /proc/version:
--31866--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--31866-- Arch and hwcaps: X86, x86-sse1-sse2
--31866-- Page sizes: currently 4096, max supported 4096
--31866-- Valgrind library directory: /usr/lib/valgrind
--31866-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--31866-- Reading debug info from /lib/ld-2.11.1.so ..
--31866-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--31866-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--31866-- Reading syms from /home/osman/src/algorist/1.1/challenges/wertyu (0x8048000)
--31866-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--31866--    object doesn't have a dynamic symbol table
--31866-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--31866-- Reading suppressions file: /usr/lib/valgrind/default.supp
--31866-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--31866-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--31866-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==31866== WARNING: new redirection conflicts with existing -- ignoring it
--31866--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--31866-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--31866-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--31866-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--31866-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--31866-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--31866-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--31866-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--31866-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--31866-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--31866-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--31866-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--31866-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--31866-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--31866-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)
--31866-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--31866-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--31866-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
O S, GOMR YPFSU/
--31866-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--31866-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)
I AM FINE TODAY.
--31866-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
==31866== 
==31866== HEAP SUMMARY:
==31866==     in use at exit: 0 bytes in 0 blocks
==31866==   total heap usage: 140 allocs, 140 frees, 1,259 bytes allocated
==31866== 
==31866== All heap blocks were freed -- no leaks are possible
==31866== 
==31866== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--31866-- 
--31866-- used_suppression:     13 dl-hack3-cond-1
==31866== 
==31866== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

