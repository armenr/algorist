/*see README for original credits */

#include<assert.h>
#include"set-union2.h"

int main(void) {
  int i;
  forest_node* f[3];

  for(i = 0; i < 3; i++)
    init_set_union2(&f[i], &i, sizeof(int));
  
  assert(find_set_union2(f[0]) == f[0]);

  merge_set_union2(f[0], f[1]);
  assert(find_set_union2(f[0]) == find_set_union2(f[1]));

  assert(find_set_union2(f[0]) != find_set_union2(f[2]));
  merge_set_union2(f[1], f[2]);
  assert(find_set_union2(f[0]) == find_set_union2(f[1]) &&
    find_set_union2(f[0]) == find_set_union2(f[2]));

  for(i = 0; i < 3; i++) {
    free(f[i]->item);
    free(f[i]);
  }

  return 0;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make set-union2-demo && valgrind --leak-check=yes -v ./set-union2-demo
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o set-union2.o set-union2.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o set-union2-demo.o set-union2-demo.c
gcc -lm  -o set-union2-demo set-union2.o set-union2-demo.o 
==5884== Memcheck, a memory error detector
==5884== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==5884== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==5884== Command: ./set-union2-demo
==5884== 
--5884-- Valgrind options:
--5884--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--5884--    --leak-check=yes
--5884--    -v
--5884-- Contents of /proc/version:
--5884--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--5884-- Arch and hwcaps: X86, x86-sse1-sse2
--5884-- Page sizes: currently 4096, max supported 4096
--5884-- Valgrind library directory: /usr/lib/valgrind
--5884-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--5884-- Reading debug info from /lib/ld-2.11.1.so ..
--5884-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--5884-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--5884-- Reading syms from /home/osman/src/algorist/1.1/ds/set-union2-demo (0x8048000)
--5884-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--5884--    object doesn't have a dynamic symbol table
--5884-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--5884-- Reading suppressions file: /usr/lib/valgrind/default.supp
--5884-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--5884-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--5884-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==5884== WARNING: new redirection conflicts with existing -- ignoring it
--5884--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--5884-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--5884-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--5884-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--5884-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--5884-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--5884-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--5884-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--5884-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--5884-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--5884-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--5884-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)
--5884-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)
--5884-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)
--5884-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
==5884== 
==5884== HEAP SUMMARY:
==5884==     in use at exit: 0 bytes in 0 blocks
==5884==   total heap usage: 6 allocs, 6 frees, 48 bytes allocated
==5884== 
==5884== All heap blocks were freed -- no leaks are possible
==5884== 
==5884== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--5884-- 
--5884-- used_suppression:     13 dl-hack3-cond-1
==5884== 
==5884== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
