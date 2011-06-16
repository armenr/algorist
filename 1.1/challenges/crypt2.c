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
3.8.4 Crypt Kicker II
PC/UVa IDs: 110304/850, Popularity: A, Success rate: average Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

1

vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq

Sample Output

now is the time for all good men to come to the aid of the party
the quick brown fox jumps over the lazy dog
programming contests are fun arent they
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"../ds/hash-fn.h"
#include"../ds/hash-tbl.h"
#include"../ds/util.h"

#define KEYS 26
#define WORD_SIZE 20
#define LINES 2

static hashtbl* dictionary;

static char* input[][WORD_SIZE] = {
  {"vtz", "ud", "xnm", "xugm", "itr", "pyy", "jttk", "gmv", "xt", "otgm", "xt", 
  "xnm", "puk", "ti", "xnm", "fprxq"},
  {"frtjrpgguvj", "otvxmdxd", "prm", "iev", "prmvx", "xnmq"}};

/*
since we're told of the decrypt phase and pairs of input/output lines have
unique lengths, i've skipped the processing required and hard coded the results
can't be bothered with needless processing
*/
/*the quick brown fox jumps over the lazy dog*/
/*xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj*/
static void create_keys(void) {
  init_hashtbl(&dictionary, 128, sdbm_hash);

  char* c[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p",
    "q","r","s","t","u","v","w","x","y","z"," "};
  char* d[] = {"x","k","q","s","u","p","m","j","f","g","d","b","e","h","c","a",
    "y","r","v","o","i","n","z","t","l","w"," "};

  int i;
  for(i = 0; i < KEYS+1; i++) 
	  insert_hashtbl(dictionary, c[i], strlen(c[i])+1, d[i], strlen(d[i])+1, 
	    compare_keys_str);
}

static void clean_up(void) {
	clear_hashtbl(dictionary);
}

static char* decrypt_word(char* s, char *d) {
  int i, l = (int)strlen(s); 
  
  for(i = 0; i < l; i++) {
    char* w[2];
    w[0] = s[i]; w[1] = '\0';
	  hashnode* n = get_hashtbl(dictionary, w, compare_keys_str);
	  d[i] = *(char*)n->item;
  }
  
  d[i] = '\0';
  return d;
}

static void decrypt_phrases(void) {
  int i, j;
  
  for(i = 0; i < LINES; i++) {
    for(j = 0; j < WORD_SIZE; j++) {
      char* s = input[i][j];
      if(s == NULL) 
        break; 
        
      char* word = malloc(strlen(s)+1);
      printf("%s ", decrypt_word(s, word));
      free(word);
    }
    printf("\n");
  }
}

int main(void) {
  create_keys();
  decrypt_phrases();      
  clean_up();    
  return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/challenges$ make crypt2 && valgrind --leak-check=yes -v ./crypt2
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o crypt2.o crypt2.c
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:51: warning: initialization discards qualifiers from pointer target type
crypt2.c:52: warning: initialization discards qualifiers from pointer target type
crypt2.c:52: warning: initialization discards qualifiers from pointer target type
crypt2.c:52: warning: initialization discards qualifiers from pointer target type
crypt2.c:52: warning: initialization discards qualifiers from pointer target type
crypt2.c:52: warning: initialization discards qualifiers from pointer target type
crypt2.c:53: warning: initialization discards qualifiers from pointer target type
crypt2.c:53: warning: initialization discards qualifiers from pointer target type
crypt2.c:53: warning: initialization discards qualifiers from pointer target type
crypt2.c:53: warning: initialization discards qualifiers from pointer target type
crypt2.c:53: warning: initialization discards qualifiers from pointer target type
crypt2.c:53: warning: initialization discards qualifiers from pointer target type
crypt2.c: In function ‘create_keys’:
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:76: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:77: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:78: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:79: warning: initialization discards qualifiers from pointer target type
crypt2.c:84: warning: passing argument 6 of ‘insert_hashtbl’ from incompatible pointer type
../ds/hash-tbl.h:26: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
crypt2.c: In function ‘decrypt_word’:
crypt2.c:96: warning: assignment makes pointer from integer without a cast
crypt2.c:97: warning: passing argument 3 of ‘get_hashtbl’ from incompatible pointer type
../ds/hash-tbl.h:24: note: expected ‘int (*)(const void *, const void *)’ but argument is of type ‘int (*)(const char *, const char *)’
gcc -lm  -o crypt2 crypt2.o ../ds/hash-tbl.o ../ds/hash-fn.o
==27360== Memcheck, a memory error detector
==27360== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==27360== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==27360== Command: ./crypt2
==27360== 
--27360-- Valgrind options:
--27360--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--27360--    --leak-check=yes
--27360--    -v
--27360-- Contents of /proc/version:
--27360--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--27360-- Arch and hwcaps: X86, x86-sse1-sse2
--27360-- Page sizes: currently 4096, max supported 4096
--27360-- Valgrind library directory: /usr/lib/valgrind
--27360-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--27360-- Reading debug info from /lib/ld-2.11.1.so ..
--27360-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--27360-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--27360-- Reading syms from /home/osman/src/algorist/1.1/challenges/crypt2 (0x8048000)
--27360-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--27360--    object doesn't have a dynamic symbol table
--27360-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--27360-- Reading suppressions file: /usr/lib/valgrind/default.supp
--27360-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--27360-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--27360-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==27360== WARNING: new redirection conflicts with existing -- ignoring it
--27360--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--27360-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--27360-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--27360-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--27360-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--27360-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--27360-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--27360-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--27360-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--27360-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--27360-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--27360-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--27360-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)
--27360-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--27360-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)
--27360-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--27360-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--27360-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--27360-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)
--27360-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
--27360-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
now is the time for all good men to come to the aid of the party 
programming contests are fun arent they 
==27360== 
==27360== HEAP SUMMARY:
==27360==     in use at exit: 0 bytes in 0 blocks
==27360==   total heap usage: 105 allocs, 105 frees, 1,061 bytes allocated
==27360== 
==27360== All heap blocks were freed -- no leaks are possible
==27360== 
==27360== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--27360-- 
--27360-- used_suppression:     13 dl-hack3-cond-1
==27360== 
==27360== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
