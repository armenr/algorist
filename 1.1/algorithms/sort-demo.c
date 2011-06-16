/*see README for original credits */

#include<stdio.h>
#include"random.h"
#include"sort.h"

static void randomizeArray(int s[]) {
    int i;
    for (i = 0; i < NELEM; i++)
        s[i] = NELEM - i;
    random_permutation(s, NELEM);
}

static void printArray(int s[]) {
    int i;
    for (i = 0; i < NELEM; i++)
        printf("%d ", s[i]);
}

int main(void) {
    int s[NELEM + 2], i;

    printf("Randomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    insertion_sort(s, NELEM);
    printf("\n\nInsertion sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    selection_sort(s, NELEM);
    printf("\n\nSelection sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    quick_sort(s, 0, NELEM - 1);
    printf("\n\nQuick sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    heap_sort(s, NELEM);
    printf("\n\nHeap sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    merge_sort(s, 0, NELEM - 1);
    printf("\n\nMerge sort: \n");
    printArray(s);

    printf("\n\n");

    for (i = 0; i < NELEM; i++)
        s[i] = 2 * (NELEM - i);
    random_permutation(s, NELEM);

    heap_sort(s, NELEM);

    for (i = 0; i < 2 * NELEM + 1; i++)
        printf("%d found in %d\n", i, binary_search(s, i, 0, NELEM - 1));

    printf("\n");
    return 0;
}

/*
osman@osman-dev:~/src/ds$ ./sort-demo 
Randomized array from 1 to 8: 
6 2 3 7 8 5 4 1 

Insertion sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
8 3 1 5 6 2 7 4 

Selection sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
1 6 4 3 7 2 8 5 

Quick sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
1 7 2 4 6 5 3 8 

Heap sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
1 7 8 4 6 2 3 5 

Merge sort: 
1 2 3 4 5 6 7 8 

0 found in -1
1 found in -1
2 found in 0
3 found in -1
4 found in 1
5 found in -1
6 found in 2
7 found in -1
8 found in 3
9 found in -1
10 found in 4
11 found in -1
12 found in 5
13 found in -1
14 found in 6
15 found in -1
16 found in 7
 */

/*osman@osman-dev:~/src/algorist/1.1/ds$ make sort-demo && valgrind --leak-check=yes -v ./sort-demo*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o sort.o sort.c*/
/*sort.c: In function ‘insertion_sort’:*/
/*sort.c:62: warning: implicit declaration of function ‘swap’*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o sort-demo.o sort-demo.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o list.o list.c*/
/*list.c: In function ‘delete_list’:*/
/*list.c:18: warning: cast discards qualifiers from pointer target type*/
/*list.c:23: warning: cast discards qualifiers from pointer target type*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o priority-queue.o priority-queue.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o queue.o queue.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi    -c -o random.o random.c*/
/*gcc -lm  -o sort-demo sort.o sort-demo.o list.o priority-queue.o queue.o \*/
/*	random.o */
/*==4273== Memcheck, a memory error detector*/
/*==4273== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==4273== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==4273== Command: ./sort-demo*/
/*==4273== */
/*--4273-- Valgrind options:*/
/*--4273--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--4273--    --leak-check=yes*/
/*--4273--    -v*/
/*--4273-- Contents of /proc/version:*/
/*--4273--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--4273-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--4273-- Page sizes: currently 4096, max supported 4096*/
/*--4273-- Valgrind library directory: /usr/lib/valgrind*/
/*--4273-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--4273-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--4273-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--4273-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--4273-- Reading syms from /home/osman/src/algorist/1.1/ds/sort-demo (0x8048000)*/
/*--4273-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--4273--    object doesn't have a dynamic symbol table*/
/*--4273-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--4273-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--4273-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--4273-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--4273-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==4273== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--4273--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--4273-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--4273-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--4273-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--4273-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--4273-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--4273-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--4273-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--4273-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--4273-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--4273-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--4273-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*Randomized array from 1 to 8: */
/*--4273-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*6 2 3 7 8 5 4 1 */

/*Insertion sort: */
/*1 2 3 4 5 6 7 8 */

/*Randomized array from 1 to 8: */
/*8 3 1 5 6 2 7 4 */

/*Selection sort: */
/*1 2 3 4 5 6 7 8 */

/*Randomized array from 1 to 8: */
/*1 6 4 3 7 2 8 5 */

/*Quick sort: */
/*1 2 3 4 5 6 7 8 */

/*Randomized array from 1 to 8: */
/*--4273-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--4273-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--4273-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*--4273-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*1 7 2 4 6 5 3 8 */

/*Heap sort: */
/*1 2 3 4 5 6 7 8 */

/*Randomized array from 1 to 8: */
/*1 7 8 4 6 2 3 5 */

/*Merge sort: */
/*1 2 3 4 5 6 7 8 */

/*0 found in -1*/
/*1 found in -1*/
/*2 found in 0*/
/*3 found in -1*/
/*4 found in 1*/
/*5 found in -1*/
/*6 found in 2*/
/*7 found in -1*/
/*8 found in 3*/
/*9 found in -1*/
/*10 found in 4*/
/*11 found in -1*/
/*12 found in 5*/
/*13 found in -1*/
/*14 found in 6*/
/*15 found in -1*/
/*16 found in 7*/

/*==4273== */
/*==4273== HEAP SUMMARY:*/
/*==4273==     in use at exit: 0 bytes in 0 blocks*/
/*==4273==   total heap usage: 80 allocs, 80 frees, 416 bytes allocated*/
/*==4273== */
/*==4273== All heap blocks were freed -- no leaks are possible*/
/*==4273== */
/*==4273== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--4273-- */
/*--4273-- used_suppression:     13 dl-hack3-cond-1*/
/*==4273== */
/*==4273== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

