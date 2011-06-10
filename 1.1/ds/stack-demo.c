/*see README for original credits */

#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

static void print_item(const int* item) {
  printf("%d ", *item);
}

int main(void) {
	stack s;		/* list under construction */
	init_stack(&s);

	char c;			/* input character */

  printf("stack options: (p)ush, (o)pop, (r)print, (q)uit \n");

	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) {
  	int d;		/* input item */

		if(tolower(c) == 'p') {
		  printf("push item: ");
			scanf("%d", &d);
      printf("new item: %d\n", d);
			push_stack(&s, &d, sizeof(int));
		
		} else if(tolower(c) == 'o') {
		  int *ip = (int*)pop_stack(&s);
		  
		  if(ip != NULL) {
  		  printf("popped item: %d\n", *ip);
  		  free(ip);	  
  		  
		  } else
  		  printf("stack empty\n");
  		  
		} else if(tolower(c) == 'r')
			print_stack(s, print_item);
	}
	
	clear_stack(s);
	return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make stack-demo && valgrind --leak-check=yes -v ./stack-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o stack.o stack.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o stack-demo.o stack-demo.c
stack-demo.c: In function ‘main’:
stack-demo.c:40: warning: passing argument 2 of ‘print_stack’ from incompatible pointer type
stack.h:15: note: expected ‘void (*)(void *)’ but argument is of type ‘void (*)(const int *)’
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o list.o list.c
list.c: In function ‘delete_list’:
list.c:18: warning: cast discards qualifiers from pointer target type
list.c:23: warning: cast discards qualifiers from pointer target type
gcc -lm  -o stack-demo stack.o stack-demo.o list.o 
==4175== Memcheck, a memory error detector
==4175== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==4175== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==4175== Command: ./stack-demo
==4175== 
--4175-- Valgrind options:
--4175--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--4175--    --leak-check=yes
--4175--    -v
--4175-- Contents of /proc/version:
--4175--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--4175-- Arch and hwcaps: X86, x86-sse1-sse2
--4175-- Page sizes: currently 4096, max supported 4096
--4175-- Valgrind library directory: /usr/lib/valgrind
--4175-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--4175-- Reading debug info from /lib/ld-2.11.1.so ..
--4175-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--4175-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--4175-- Reading syms from /home/osman/src/algorist/1.1/ds/stack-demo (0x8048000)
--4175-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--4175--    object doesn't have a dynamic symbol table
--4175-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--4175-- Reading suppressions file: /usr/lib/valgrind/default.supp
--4175-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--4175-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--4175-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==4175== WARNING: new redirection conflicts with existing -- ignoring it
--4175--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--4175-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--4175-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--4175-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--4175-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--4175-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--4175-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--4175-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--4175-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--4175-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--4175-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--4175-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)
stack options: (p)ush, (o)pop, (r)print, (q)uit 
p
--4175-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
push item: 1
new item: 1
--4175-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--4175-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--4175-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
p
push item: 2
new item: 2
p
push item: 3
new item: 3
r
3 2 1 
o
--4175-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
popped item: 3
r
2 1 
o
popped item: 2
r
1 
o
popped item: 1
r

o
stack empty
q
==4175== 
==4175== HEAP SUMMARY:
==4175==     in use at exit: 0 bytes in 0 blocks
==4175==   total heap usage: 6 allocs, 6 frees, 36 bytes allocated
==4175== 
==4175== All heap blocks were freed -- no leaks are possible
==4175== 
==4175== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--4175-- 
--4175-- used_suppression:     13 dl-hack3-cond-1
==4175== 
==4175== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
