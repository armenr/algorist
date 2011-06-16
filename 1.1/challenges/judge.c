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
3.8.5 Automated Judge Script
PC/UVa IDs: 110305/10188, Popularity: B, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 15
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is:  5
3
Input Set #1: YES
Input Set #2: NO
Input Set #3: NO
3
Input Set #0: YES
Input Set #1: NO
Input Set #2: NO
1
1 0 1 0
1
1010
1
The judges are mean!
1
The judges are good!
0

Sample Output

Run #1: Accepted
Run #2: Wrong Answer
Run #3: Presentation Error
Run #4: Wrong Answer
Run #5: Presentation Error
Run #6: Presentation Error
*/

#include<ctype.h>
#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../ds/queue.h"

static queue q[2];

static void build_queues(void) {
  int i;
  char* s;
  
  init_queue(&q[0]);
  init_queue(&q[1]);
	
  /*first queue fill*/
  i = 2;
  en_queue(&q[0], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[0], s, strlen(s)+1);
  s = "The answer is: 5";
  en_queue(&q[0], s, strlen(s)+1);
  
  en_queue(&q[0], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[0], s, strlen(s)+1);
  s = "The answer is: 5";
  en_queue(&q[0], s, strlen(s)+1);

  en_queue(&q[0], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[0], s, strlen(s)+1);
  s = "The answer is:  5";
  en_queue(&q[0], s, strlen(s)+1);

	i = 3;
  en_queue(&q[0], &i, sizeof(int));
  s = "Input Set #1: YES";
  en_queue(&q[0], s, strlen(s)+1);
  s = "Input Set #2: NO";
  en_queue(&q[0], s, strlen(s)+1);
  s = "Input Set #3: NO";
  en_queue(&q[0], s, strlen(s)+1);

	i = 1;
  en_queue(&q[0], &i, sizeof(int));
  s = "1 0 1 0";
  en_queue(&q[0], s, strlen(s)+1);

  en_queue(&q[0], &i, sizeof(int));
  s = "The judges are mean!";
  en_queue(&q[0], s, strlen(s)+1);

  /*second queue fill*/
	i = 2;
  en_queue(&q[1], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[1], s, strlen(s)+1);
  s = "The answer is: 5";
  en_queue(&q[1], s, strlen(s)+1);
  
  en_queue(&q[1], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[1], s, strlen(s)+1);
  s = "The answer is: 15";
  en_queue(&q[1], s, strlen(s)+1);

  en_queue(&q[1], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[1], s, strlen(s)+1);
  s = "The answer is: 5";
  en_queue(&q[1], s, strlen(s)+1);

	i = 3;
  en_queue(&q[1], &i, sizeof(int));
  s = "Input Set #0: YES";
  en_queue(&q[1], s, strlen(s)+1);
  s = "Input Set #1: NO";
  en_queue(&q[1], s, strlen(s)+1);
  s = "Input Set #2: NO";
  en_queue(&q[1], s, strlen(s)+1);

	i = 1;
  en_queue(&q[1], &i, sizeof(int));
  s = "1010";
  en_queue(&q[1], s, strlen(s)+1);

  en_queue(&q[1], &i, sizeof(int));
  s = "The judges are good!";
  en_queue(&q[1], s, strlen(s)+1);
}

static int getNumber(const char *s) {
  int i, j = 0;
  char *d = malloc(strlen(s)+1);
  
  /*extract all digits from string, ignoring other chars*/
  for(i = 0; i < (int)strlen(s)+1; i++)
    if(isdigit(s[i]))
      d[j++] = s[i];
  d[j] = '\0';

  /*convert string to int*/
  char *n;
  errno = 0;
  int result = strtol(d, &n, 0);
  
  if(!(errno != 0 || *n != '\0' || n == d)) {
    free(d);
    return result;
  } else {
    free(d);
    return -1;
  }
}

static int getBatchCount(queue* q) {
  int *ip = (int*)de_queue(q), tmp;
    
  if(ip != NULL) {
    tmp = *ip;
    free(ip);	  
    return tmp;
    
  } else
    return 0;
}

static void getBatchData(queue* q, int sz, char* s[]) {
  int i;
  
  for(i = 0; i < sz; i++) 
    s[i] = (char*)de_queue(q);
}

static void compare_queues(void) {
  int b = 0, i, sz[2];
  bool batches_ok = true;
  
  while(!(empty_queue(&q[0]) || empty_queue(&q[1]) || !batches_ok)) {
  
    sz[0] = getBatchCount(&q[0]);
    sz[1] = getBatchCount(&q[1]);
    b++;
  
    if(sz[0] == sz[1])  { /*batches must be equal, otherwise rejected*/    
      char* s[2][sz[0]];
      
      getBatchData(&q[0], sz[0], s[0]);  
      getBatchData(&q[1], sz[1], s[1]);  
      
      bool accepted = true, presentation = true;
     
      for(i = 0; i < sz[0]; i++) 
        if(strcmp(s[0][i], s[1][i])) { /*mismatch*/
          accepted = false;
          
          /*are the numbers the same?*/
          if(getNumber(s[0][i]) != getNumber(s[1][i])) {
            presentation = false;
            break;
          }
      }
      
      for(i = 0; i < sz[0]; i++) {
        printf("%s\t%s\n", s[0][i], s[1][i]);
        free(s[0][i]);
        free(s[1][i]);
      }

      if(accepted)
        printf("Run #%d: Accepted\n", b);
      else if(presentation)
        printf("Run #%d: Presentation Error\n", b);
      else
        printf("Run #%d: Wrong Answer\n", b);
    } else
      batches_ok = false; /*reject further processing*/
  }
}

int main(void) {
  build_queues();
  compare_queues();
  clear_queue(&q[0]);
  clear_queue(&q[1]);
  return 0;
}

/* 
osman@osman-dev:~/src/algorist/1.1/challenges$ make judge && valgrind --leak-check=yes -v ./judge
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o judge.o judge.c
judge.c: In function ‘build_queues’:
judge.c:91: warning: assignment discards qualifiers from pointer target type
judge.c:93: warning: assignment discards qualifiers from pointer target type
judge.c:97: warning: assignment discards qualifiers from pointer target type
judge.c:99: warning: assignment discards qualifiers from pointer target type
judge.c:103: warning: assignment discards qualifiers from pointer target type
judge.c:105: warning: assignment discards qualifiers from pointer target type
judge.c:110: warning: assignment discards qualifiers from pointer target type
judge.c:112: warning: assignment discards qualifiers from pointer target type
judge.c:114: warning: assignment discards qualifiers from pointer target type
judge.c:119: warning: assignment discards qualifiers from pointer target type
judge.c:123: warning: assignment discards qualifiers from pointer target type
judge.c:129: warning: assignment discards qualifiers from pointer target type
judge.c:131: warning: assignment discards qualifiers from pointer target type
judge.c:135: warning: assignment discards qualifiers from pointer target type
judge.c:137: warning: assignment discards qualifiers from pointer target type
judge.c:141: warning: assignment discards qualifiers from pointer target type
judge.c:143: warning: assignment discards qualifiers from pointer target type
judge.c:148: warning: assignment discards qualifiers from pointer target type
judge.c:150: warning: assignment discards qualifiers from pointer target type
judge.c:152: warning: assignment discards qualifiers from pointer target type
judge.c:157: warning: assignment discards qualifiers from pointer target type
judge.c:161: warning: assignment discards qualifiers from pointer target type
gcc -lm  -o judge judge.o ../ds/queue.o ../ds/list.o
==1051== Memcheck, a memory error detector
==1051== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==1051== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==1051== Command: ./judge
==1051== 
--1051-- Valgrind options:
--1051--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--1051--    --leak-check=yes
--1051--    -v
--1051-- Contents of /proc/version:
--1051--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--1051-- Arch and hwcaps: X86, x86-sse1-sse2
--1051-- Page sizes: currently 4096, max supported 4096
--1051-- Valgrind library directory: /usr/lib/valgrind
--1051-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--1051-- Reading debug info from /lib/ld-2.11.1.so ..
--1051-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--1051-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--1051-- Reading syms from /home/osman/src/algorist/1.1/challenges/judge (0x8048000)
--1051-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--1051--    object doesn't have a dynamic symbol table
--1051-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--1051-- Reading suppressions file: /usr/lib/valgrind/default.supp
--1051-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--1051-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--1051-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==1051== WARNING: new redirection conflicts with existing -- ignoring it
--1051--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--1051-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--1051-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--1051-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--1051-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--1051-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--1051-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--1051-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--1051-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--1051-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--1051-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--1051-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--1051-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--1051-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--1051-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
--1051-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--1051-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)
--1051-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
The answer is: 10	The answer is: 10
The answer is: 5	The answer is: 5
Run #1: Accepted
--1051-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--1051-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)
The answer is: 10	The answer is: 10
The answer is: 5	The answer is: 15
Run #2: Wrong Answer
The answer is: 10	The answer is: 10
The answer is:  5	The answer is: 5
Run #3: Presentation Error
Input Set #1: YES	Input Set #0: YES
Input Set #2: NO	Input Set #1: NO
Input Set #3: NO	Input Set #2: NO
Run #4: Wrong Answer
1 0 1 0	1010
Run #5: Presentation Error
The judges are mean!	The judges are good!
Run #6: Presentation Error
==1051== 
==1051== HEAP SUMMARY:
==1051==     in use at exit: 0 bytes in 0 blocks
==1051==   total heap usage: 78 allocs, 78 frees, 852 bytes allocated
==1051== 
==1051== All heap blocks were freed -- no leaks are possible
==1051== 
==1051== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--1051-- 
--1051-- used_suppression:     13 dl-hack3-cond-1
==1051== 
==1051== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/

