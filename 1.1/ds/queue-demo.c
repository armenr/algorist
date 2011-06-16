/*see README for original credits */

#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include<ctype.h>

static void print_item(const int* item) {
  printf("%d ", *item);
}

int main(void) {
	queue q;		
	init_queue(&q);

	char c;			

  printf("queue options: (e)nqueue, (d)equeue, (p)rint, (q)uit \n");

	while(!(scanf("%c", &c) == EOF || tolower(c) == 'q')) {
  	int d;

		if(tolower(c) == 'e') {
		  printf("enqueue item: ");
			scanf("%d", &d);
      printf("new item: %d\n", d);
			en_queue(&q, &d, sizeof(int));
		
		} else if(tolower(c) == 'd') {
		  int* ip = (int*)de_queue(&q);
		  if(ip != NULL) {
  		  printf("dequeue item: %d\n", *ip);
  		  free(ip);	  
  		  
		  } else
  		  printf("queue empty\n");
  		  
		} else if(tolower(c) == 'p')
			print_queue(&q, print_item);
	}
	
	clear_queue(&q);
	return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make queue-demo && valgrind --leak-check=yes -v ./queue-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o queue.o queue.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o queue-demo.o queue-demo.c
queue-demo.c: In function ‘main’:
queue-demo.c:39: warning: passing argument 2 of ‘print_queue’ from incompatible pointer type
queue.h:19: note: expected ‘void (*)(void *)’ but argument is of type ‘void (*)(const int *)’
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o list.o list.c
list.c: In function ‘delete_list’:
list.c:18: warning: cast discards qualifiers from pointer target type
list.c:23: warning: cast discards qualifiers from pointer target type
gcc -lm  -o queue-demo queue.o queue-demo.o list.o 
==4128== Memcheck, a memory error detector
==4128== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==4128== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==4128== Command: ./queue-demo
==4128== 
--4128-- Valgrind options:
--4128--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--4128--    --leak-check=yes
--4128--    -v
--4128-- Contents of /proc/version:
--4128--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--4128-- Arch and hwcaps: X86, x86-sse1-sse2
--4128-- Page sizes: currently 4096, max supported 4096
--4128-- Valgrind library directory: /usr/lib/valgrind
--4128-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--4128-- Reading debug info from /lib/ld-2.11.1.so ..
--4128-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--4128-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--4128-- Reading syms from /home/osman/src/algorist/1.1/ds/queue-demo (0x8048000)
--4128-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--4128--    object doesn't have a dynamic symbol table
--4128-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--4128-- Reading suppressions file: /usr/lib/valgrind/default.supp
--4128-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--4128-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--4128-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==4128== WARNING: new redirection conflicts with existing -- ignoring it
--4128--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--4128-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--4128-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--4128-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--4128-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--4128-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--4128-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--4128-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--4128-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--4128-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--4128-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--4128-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)
queue options: (e)nqueue, (d)equeue, (p)rint, (q)uit 
e
--4128-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
enqueue item: 1
new item: 1
--4128-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--4128-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--4128-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
e
enqueue item: 2
new item: 2
e
enqueue item: 3
new item: 3
p
1 2 3 
d
--4128-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
dequeue item: 1
p
2 3 
d
dequeue item: 2
p
3 
d
dequeue item: 3
p

d
queue empty
q
==4128== 
==4128== HEAP SUMMARY:
==4128==     in use at exit: 0 bytes in 0 blocks
==4128==   total heap usage: 6 allocs, 6 frees, 36 bytes allocated
==4128== 
==4128== All heap blocks were freed -- no leaks are possible
==4128== 
==4128== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--4128-- 
--4128-- used_suppression:     13 dl-hack3-cond-1
==4128== 
==4128== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
