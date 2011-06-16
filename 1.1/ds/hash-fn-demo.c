/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"hash-fn.h"

int main(int argc, char* argv[]) {
	hash_t (*hash)(const void* key) = NULL;

  hashfunc_s funcs[] = {
	  {"add", add_hash},
	  {"xor", xor_hash},
	  {"sax", sax_hash},
	  {"sdbm", sdbm_hash},
	  {"bernstein", bernstein_hash}
  };

  /*select a function*/
	if(argc > 1) {
  	int i, sz = sizeof(funcs) / sizeof(hashfunc_s);

		for(i = 0; i < sz; i++) 
			if(!strcmp(argv[1], funcs[i].name)) {
				hash = funcs[i].func;
				break;
			}
			
		if(hash == NULL) {
			fprintf(stderr, "ERROR: Could not find the %s hash function\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		
	} else 
	  hash = funcs[0].func; /*default to first entry (add_hash)*/

	hash_t hsize;
	if(argc > 2) 
	  hsize = atol(argv[2]);
	else 
	  hsize = 32768;

/*  
This program will read a list of words, one for each line, from stdin and print 
the corresponding hash values. The hash function and table size are specified 
as command line arguments.
*/
  char line[256];

  while(fgets(line, 256, stdin)) {
	  char* p;

		if((p = strchr(line, '\r')))
		  *p = '\0';
		if((p = strchr(line, '\n'))) 
		  *p = '\0';

/*
The hash functions take one argument, a '\0'-terminated string, and return the 
calculated hash value. This value is later redused to the hash table size before 
it is printed. 
*/
		printf("%s\n%lu\n", line, hash((unsigned char*)line) % hsize);
	}
	
	return EXIT_SUCCESS;
}

/*
osman@osman-dev:~/src/algorist/1.1/ds$ make hash-fn-demo && valgrind --leak-check=yes -v ./hash-fn-demo < hash-words-100
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o hash-fn.o hash-fn.c
gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o hash-fn-demo.o hash-fn-demo.c
gcc -lm  -o hash-fn-demo hash-fn.o hash-fn-demo.o 
==8081== Memcheck, a memory error detector
==8081== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==8081== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==8081== Command: ./hash-fn-demo
==8081== 
--8081-- Valgrind options:
--8081--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp
--8081--    --leak-check=yes
--8081--    -v
--8081-- Contents of /proc/version:
--8081--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011
--8081-- Arch and hwcaps: X86, x86-sse1-sse2
--8081-- Page sizes: currently 4096, max supported 4096
--8081-- Valgrind library directory: /usr/lib/valgrind
--8081-- Reading syms from /lib/ld-2.11.1.so (0x4000000)
--8081-- Reading debug info from /lib/ld-2.11.1.so ..
--8081-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)
--8081-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..
--8081-- Reading syms from /home/osman/src/algorist/1.1/ds/hash-fn-demo (0x8048000)
--8081-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)
--8081--    object doesn't have a dynamic symbol table
--8081-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp
--8081-- Reading suppressions file: /usr/lib/valgrind/default.supp
--8081-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)
--8081-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)
--8081-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)
==8081== WARNING: new redirection conflicts with existing -- ignoring it
--8081--     new: 0x040160b0 (index               ) R-> 0x04025c30 index
--8081-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)
--8081-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)
--8081-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..
--8081-- .. CRC mismatch (computed a765a73c wanted 8d13be57)
--8081-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..
--8081-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)
--8081-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..
--8081-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)
--8081-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..
--8081-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)
--8081-- REDIR: 0x40d63a0 (memchr) redirected to 0x40267b0 (memchr)
--8081-- REDIR: 0x40d4fd0 (index) redirected to 0x4025ba0 (index)
--8081-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)
overinform
1095
trochozoon
1109
glycerophosphoric
1844
unimplicitly
1315
ferthumlungur
1432
sesquipedality
1526
portulan
885
hypodermatic
1289
amphibrach
1039
subungulate
1199
refractively
1296
ongaro
646
zootoxin
906
Wovoka
631
Norn
413
skerry
672
azygomatous
1219
neurogenous
1210
salary
652
fodda
510
teil
430
gelatigenous
1287
satisfice
955
sensibilitist
1414
bootikin
863
impatiently
1200
redeflect
942
sarraf
639
Cymbium
726
groveless
986
unmarked
855
nonreality
1093
Moguntine
950
whatsoever
1096
trimerization
1425
thallose
860
kiskatom
867
unincited
963
subintroductory
1664
scrawk
651
Myrmecobius
1167
pahi
418
formability
1186
odontornithic
1412
sheepshank
1066
interstage
1078
cutpurse
891
jellify
751
farcelike
934
prasinous
996
barbatimao
1042
protectionize
1423
polygamical
1170
aquariist
979
ornithon
881
enthusiast
1096
adorn
532
flurry
676
undecimole
1061
hypotoxicity
1341
apocryphate
1184
shallowbrained
1487
physicomental
1408
economics
960
tupman
661
diselectrify
1287
strophically
1310
verminicidal
1271
organon
756
slonk
551
bebouldered
1149
unmarching
1068
walsh
543
amateur
751
opiniativeness
1521
termen
651
tripartition
1321
teleran
747
huskened
855
Pleurosticti
1287
beshroud
860
palea
515
calcaneoscaphoid
1665
meetable
831
mainour
763
refine
633
Hanse
495
grangerism
1071
Alison
614
siesta
649
psychomotility
1553
turbantop
991
crustless
1000
mormaordom
1085
phaenogamian
1256
pseudofeminine
1499
undecane
835
nursling
882
unmarried
967
mass
436
--8081-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)
==8081== 
==8081== HEAP SUMMARY:
==8081==     in use at exit: 0 bytes in 0 blocks
==8081==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==8081== 
==8081== All heap blocks were freed -- no leaks are possible
==8081== 
==8081== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
--8081-- 
--8081-- used_suppression:     13 dl-hack3-cond-1
==8081== 
==8081== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)
*/
