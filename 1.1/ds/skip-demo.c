/*see README for original credits */

#include"skip-list.h"
#include <stdio.h>

int main(void) {

  skipset* ss;
  init_skipset(&ss);
  print_skipset(ss);

  int i = 5;
  insert_skipnode(ss, i, &i, sizeof(i));
  i = 10;
  insert_skipnode(ss, i, &i, sizeof(i));
  i = 7;
  insert_skipnode(ss, i, &i, sizeof(i));
  insert_skipnode(ss, i, &i, sizeof(i));
  i = 6;
  insert_skipnode(ss, i, &i, sizeof(i));

  print_skipset(ss);

  if(contains_skipnode(ss, 7) != NULL) 
    printf("7 is in the list\n");

  delete_skipnode(ss, 7);
  print_skipset(ss);

  if(!contains_skipnode(ss, 7)) 
    printf("7 has been deleted\n");

  delete_skipnode(ss, 5);
  delete_skipnode(ss, 6);
  delete_skipnode(ss, 10);
  
  print_skipset(ss);
  clear_skipset(&ss);
  return 0;
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make skip-demo && valgrind --leak-check=yes -v ./skip-demo*/
/*make: `skip-demo' is up to date.*/
/*==7998== Memcheck, a memory error detector*/
/*==7998== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==7998== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==7998== Command: ./skip-demo*/
/*==7998== */
/*--7998-- Valgrind options:*/
/*--7998--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--7998--    --leak-check=yes*/
/*--7998--    -v*/
/*--7998-- Contents of /proc/version:*/
/*--7998--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--7998-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--7998-- Page sizes: currently 4096, max supported 4096*/
/*--7998-- Valgrind library directory: /usr/lib/valgrind*/
/*--7998-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--7998-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--7998-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--7998-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--7998-- Reading syms from /home/osman/src/algorist/1.1/ds/skip-demo (0x8048000)*/
/*--7998-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--7998--    object doesn't have a dynamic symbol table*/
/*--7998-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--7998-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--7998-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--7998-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--7998-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==7998== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--7998--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--7998-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--7998-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--7998-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--7998-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--7998-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--7998-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--7998-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--7998-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--7998-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--7998-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--7998-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--7998-- REDIR: 0x40d1660 (calloc) redirected to 0x402417f (calloc)*/
/*--7998-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--7998-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--7998-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*level 0:*/
/*--7998-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*{}*/
/*level 3:*/
/*{7, 10}*/
/*level 2:*/
/*{7, 10}*/
/*level 1:*/
/*{7, 10}*/
/*level 0:*/
/*{5, 6, 7, 10}*/
/*7 is in the list*/
/*--7998-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*level 3:*/
/*{10}*/
/*level 2:*/
/*{10}*/
/*level 1:*/
/*{10}*/
/*level 0:*/
/*{5, 6, 10}*/
/*7 has been deleted*/
/*level 0:*/
/*{}*/
/*==7998== */
/*==7998== HEAP SUMMARY:*/
/*==7998==     in use at exit: 0 bytes in 0 blocks*/
/*==7998==   total heap usage: 21 allocs, 21 frees, 264 bytes allocated*/
/*==7998== */
/*==7998== All heap blocks were freed -- no leaks are possible*/
/*==7998== */
/*==7998== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--7998-- */
/*--7998-- used_suppression:     13 dl-hack3-cond-1*/
/*==7998== */
/*==7998== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

