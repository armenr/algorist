/*see README for original credits */

#include<ctype.h>
#include<stdio.h>
#include"dlist.h"

static void print_item(const int* item) {
  printf("%d ", *item);
}

int main(void) {
	dlist *l;		/* dlist under construction */
	init_dlist(&l);

	char c;			/* input character */
  printf("dlist options: (p)rint, (s)earch, (i)nsert, (d)elete, (q) quit \n");

	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) {
  	int d;		/* input item */
  	const dlist *tmp;		/* returned dlist from search */

		if(tolower(c) == 'p')
			print_dlist(l, print_item);
			
		else if(tolower(c) == 'i') {
		  printf("insert item: ");
			scanf("%d", &d);
      printf("new item: %d\n", d);
			insert_dlist(&l, &d, sizeof(int));
		}
		
		else if(tolower(c) == 's') {
		  printf("search for item: ");
			scanf("%d", &d);
			tmp = search_dlist(l, &d, sizeof(int));
			
			printf("item %d ", d);
			if(tmp != NULL) 
				printf("found\n");
			else
				printf("not found\n");
		}
		
		else if(tolower(c) == 'd') {
		  printf("delete item: ");
			scanf("%d", &d);
      tmp = search_dlist(l, &d, sizeof(int));

			printf("item %d ", d);
      if(tmp != NULL) {
  			delete_dlist(&l, &d, sizeof(int));
				printf("deleted\n");
			} else
        printf("not found\n");
		}
	}
	
	clear_dlist(l);
	return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make dlist-demo && valgrind --leak-check=yes -v ./dlist-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o dlist.o dlist.c
dlist.c: In function ‘delete_dlist’:
dlist.c:18: warning: cast discards qualifiers from pointer target type
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o dlist-demo.o dlist-demo.c
dlist-demo.c: In function ‘main’:
dlist-demo.c:23: warning: passing argument 2 of ‘print_dlist’ from incompatible pointer type
dlist.h:20: note: expected ‘void (*)(void *)’ but argument is of type ‘void (*)(const int *)’
gcc -lm  -o dlist-demo dlist.o dlist-demo.o 
==4037== Memcheck, a memory error detector
==4037== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==4037== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==4037== Command: ./dlist-demo
==4037== 
--4037-- Valgrind options:
--4037--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--4037--    --leak-check=yes
--4037--    -v
--4037-- Contents of /proc/version:
--4037--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--4037-- Arch and hwcaps: X86, x86-sse1-sse2
--4037-- Page sizes: currently 4096, max supported 4096
--4037-- Valgrind library directory: /usr/lib/valgrind
--4037-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--4037-- Reading debug info from /lib/ld-2.11.1.so ..
--4037-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--4037-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--4037-- Reading syms from /home/osman/src/algorist/1.1/ds/dlist-demo (0x8048000)
--4037-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--4037--    object doesn't have a dynamic symbol table
--4037-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--4037-- Reading suppressions file: /usr/lib/valgrind/default.supp
--4037-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--4037-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--4037-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==4037== WARNING: new redirection conflicts with existing -- ignoring it
--4037--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--4037-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--4037-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--4037-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--4037-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--4037-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--4037-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--4037-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--4037-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--4037-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--4037-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--4037-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)
dlist options: (p)rint, (s)earch, (i)nsert, (d)elete, (q) quit 
i
--4037-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
insert item: 1
new item: 1
--4037-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--4037-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--4037-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
i
insert item: 2
new item: 2
i
insert item: 3
new item: 3
p
3 2 1 
s
search for item: 0
--4037-- REDIR: 0x40d6540 (bcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--4037-- REDIR: 0x417d160 (__memcmp_ssse3) redirected to 0x4027000 (bcmp)
item 0 not found
s
search for item: 2
item 2 found
d
delete item: 2
--4037-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
item 2 deleted
p
3 1 
q
==4037== 
==4037== HEAP SUMMARY:
==4037==     in use at exit: 0 bytes in 0 blocks
==4037==   total heap usage: 6 allocs, 6 frees, 48 bytes allocated
==4037== 
==4037== All heap blocks were freed -- no leaks are possible
==4037== 
==4037== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--4037-- 
--4037-- used_suppression:     13 dl-hack3-cond-1
==4037== 
==4037== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
