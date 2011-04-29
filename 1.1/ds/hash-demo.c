/* Copyright (c) 2011 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hash_table_(C)?action=history&offset=20100620072342

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hash_table_(C)?oldid=16749
*/

#include"hashtbl.h"
#include<stdio.h>
#include<stdlib.h>

int main(void) {
	HASHTBL *hashtbl;
	char *spain, *italy;

	if(!(hashtbl=hashtbl_create(16, NULL))) {
		fprintf(stderr, "ERROR: hashtbl_create() failed\n");
		exit(EXIT_FAILURE);
	}

	hashtbl_insert(hashtbl, "France", "Paris");
	hashtbl_insert(hashtbl, "England", "London");
	hashtbl_insert(hashtbl, "Sweden", "Stockholm");
	hashtbl_insert(hashtbl, "Germany", "Berlin");
	hashtbl_insert(hashtbl, "Norway", "Oslo");
	hashtbl_insert(hashtbl, "Italy", "Rome");
	hashtbl_insert(hashtbl, "Spain", "Madrid");
	hashtbl_insert(hashtbl, "Estonia", "Tallinn");
	hashtbl_insert(hashtbl, "Netherlands", "Amsterdam");
	hashtbl_insert(hashtbl, "Ireland", "Dublin");

	printf("After insert:\n");
	italy=hashtbl_get(hashtbl, "Italy");
	printf("Italy: %s\n", italy?italy:"-");
	spain=hashtbl_get(hashtbl, "Spain");
	printf("Spain: %s\n", spain?spain:"-");


	hashtbl_remove(hashtbl, "Spain");

	printf("After remove:\n");
	spain=hashtbl_get(hashtbl, "Spain");
	printf("Spain: %s\n", spain?spain:"-");


	hashtbl_resize(hashtbl, 8);

	printf("After resize:\n");
	italy=hashtbl_get(hashtbl, "Italy");
	printf("Italy: %s\n", italy?italy:"-");

	hashtbl_destroy(hashtbl);

	return 0;
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make hash-demo && valgrind --leak-check=yes -v ./hash-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o hashtbl.o hashtbl.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o hash-demo.o hash-demo.c*/
/*hash-demo.c: In function ‘main’:*/
/*hash-demo.c:39: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:40: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:41: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:42: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:43: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:44: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:45: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:46: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:47: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*hash-demo.c:48: warning: passing argument 3 of ‘hashtbl_insert’ discards qualifiers from pointer target type*/
/*hashtbl.h:29: note: expected ‘void *’ but argument is of type ‘const char *’*/
/*gcc -lm  -o hash-demo hashtbl.o hash-demo.o */
/*==19213== Memcheck, a memory error detector*/
/*==19213== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==19213== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==19213== Command: ./hash-demo*/
/*==19213== */
/*--19213-- Valgrind options:*/
/*--19213--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--19213--    --leak-check=yes*/
/*--19213--    -v*/
/*--19213-- Contents of /proc/version:*/
/*--19213--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--19213-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--19213-- Page sizes: currently 4096, max supported 4096*/
/*--19213-- Valgrind library directory: /usr/lib/valgrind*/
/*--19213-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--19213-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--19213-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--19213-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--19213-- Reading syms from /home/osman/src/algorist/1.1/ds/hash-demo (0x8048000)*/
/*--19213-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--19213--    object doesn't have a dynamic symbol table*/
/*--19213-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--19213-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--19213-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--19213-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--19213-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==19213== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--19213--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--19213-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--19213-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--19213-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--19213-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--19213-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--19213-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--19213-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--19213-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--19213-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--19213-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--19213-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--19213-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)*/
/*--19213-- REDIR: 0x40d5730 (strlen) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--19213-- REDIR: 0x40d5770 (__strlen_sse2) redirected to 0x4026030 (strlen)*/
/*--19213-- REDIR: 0x40d5200 (strcpy) redirected to 0x40260b0 (strcpy)*/
/*--19213-- REDIR: 0x40d5140 (strcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--19213-- REDIR: 0x417a240 (__strcmp_ssse3) redirected to 0x4026630 (strcmp)*/
/*--19213-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*After insert:*/
/*--19213-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*Italy: Rome*/
/*Spain: Madrid*/
/*--19213-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*After remove:*/
/*Spain: -*/
/*After resize:*/
/*Italy: Rome*/
/*==19213== */
/*==19213== HEAP SUMMARY:*/
/*==19213==     in use at exit: 0 bytes in 0 blocks*/
/*==19213==   total heap usage: 41 allocs, 41 frees, 484 bytes allocated*/
/*==19213== */
/*==19213== All heap blocks were freed -- no leaks are possible*/
/*==19213== */
/*==19213== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--19213-- */
/*--19213-- used_suppression:     13 dl-hack3-cond-1*/
/*==19213== */
/*==19213== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

