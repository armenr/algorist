/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"clist.h"

static const clist_item* search_item(const clist_item* d, int count, 
  const void* item, int sz);

void clear_clist(clist* l) {
  while(l->count > 0) {
    clist p;
    p.data = l->data;
    l->data = p.data->next;
    free(p.data->item);
    free(p.data);
    l->count--;
  }
}

void delete_clist(clist* l, const void* item, int sz) {
	const clist_item* p = search_clist(l, item, sz);
	
	if(p == NULL) /* not found*/
	  return;
	  
	clist_item* pred = p->prev;
	if(pred != NULL)  /* only null for a single item	*/
		pred->next = p->next; /* complete chain*/
  else
    l->data = p->next;
    
	clist_item* succ = p->next;
	if(succ != NULL)   /* only null for a single item	*/
		succ->prev = p->prev; /* complete chain*/

  free(p->item);
  free((clist_item*)p);
  
  l->count--;
}

bool empty_clist(const clist* l) {
  if(l->data == NULL) 
    return true;
    
  return false;
}

const void* head_clist(const clist* l) {
	return l->data->item;
}

void init_clist(clist* l) {
 l->data = NULL;
 l->count = 0;
}

void insert_clist(clist* l, const void* item, int sz) {
	clist_item* p = malloc(sizeof(clist_item));
  p->item = malloc(sz);  
	memcpy(p->item, item, sz);
	
  if(l->data != NULL) {
	  p->next = l->data;
	  l->data->prev = p;
	  /* connect end points to make list circular*/
	  p->prev = l->tail;
	  l->tail->next = p;
  }	else { /* new list*/
  	p->prev = NULL;
	  p->next = NULL;
    l->tail = p;  
  }
  
	l->data = p;
	l->count++;
}

const clist_item* search_clist(const clist* l, const void* item, 
  int sz) {
	if(l == NULL) 
	  return NULL;

	return search_item(l->data, l->count, item, sz);
}

void print_clist(const clist* l, void (*print_item)(const void* item)) {
  clist* p = (clist*)l;
  int i;

  for(i = 0; i < l->count; i++) {
    print_item(p->data->item);

    if(p->data->next != NULL)
      p->data = p->data->next;
  } 
  printf("\n");
}

static const clist_item* search_item(const clist_item* d, int count, 
  const void* item, int sz) {
  static int c = 0; /* keep count of how many nodes searched*/
  
	if(c == count) {
	  c = 0;
	  return NULL;
	}

  int cmp = memcmp(d->item, item, sz);
  if(!cmp) {  /*equal values*/
    c = 0;
		return d;
		
	} else {
	  c++;
		return search_item(d->next, count, item, sz);  
	}
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make clist-demo && valgrind --leak-check=yes -v ./clist-demo*/
/*gcc -Wall -Wextra -ggdb    -c -o clist.o clist.c*/
/*gcc -Wall -Wextra -ggdb    -c -o clist-demo.o clist-demo.c*/
/*clist-demo.c: In function ‘main’:*/
/*clist-demo.c:23: warning: passing argument 2 of ‘print_clist’ from incompatible pointer type*/
/*clist.h:28: note: expected ‘void (*)(void *)’ but argument is of type ‘void (*)(const int *)’*/
/*gcc -lm  -o clist-demo clist.o clist-demo.o */
/*==2410== Memcheck, a memory error detector*/
/*==2410== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.*/
/*==2410== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info*/
/*==2410== Command: ./clist-demo*/
/*==2410== */
/*--2410-- Valgrind options:*/
/*--2410--    --suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--2410--    --leak-check=yes*/
/*--2410--    -v*/
/*--2410-- Contents of /proc/version:*/
/*--2410--   Linux version 2.6.32-30-generic (buildd@vernadsky) (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5) ) #59-Ubuntu SMP Tue Mar 1 21:30:21 UTC 2011*/
/*--2410-- Arch and hwcaps: X86, x86-sse1-sse2*/
/*--2410-- Page sizes: currently 4096, max supported 4096*/
/*--2410-- Valgrind library directory: /usr/lib/valgrind*/
/*--2410-- Reading syms from /lib/ld-2.11.1.so (0x4000000)*/
/*--2410-- Reading debug info from /lib/ld-2.11.1.so ..*/
/*--2410-- .. CRC mismatch (computed 45f50ae1 wanted 137bc614)*/
/*--2410-- Reading debug info from /usr/lib/debug/lib/ld-2.11.1.so ..*/
/*--2410-- Reading syms from /home/osman/src/algorist/1.1/ds/clist-demo (0x8048000)*/
/*--2410-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)*/
/*--2410--    object doesn't have a dynamic symbol table*/
/*--2410-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp*/
/*--2410-- Reading suppressions file: /usr/lib/valgrind/default.supp*/
/*--2410-- REDIR: 0x40160b0 (index) redirected to 0x3803e9b3 (vgPlain_x86_linux_REDIR_FOR_index)*/
/*--2410-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x401f000)*/
/*--2410-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4022000)*/
/*==2410== WARNING: new redirection conflicts with existing -- ignoring it*/
/*--2410--     new: 0x040160b0 (index               ) R-> 0x04025c30 index*/
/*--2410-- REDIR: 0x4016290 (strlen) redirected to 0x4026070 (strlen)*/
/*--2410-- Reading syms from /lib/tls/i686/cmov/libm-2.11.1.so (0x403b000)*/
/*--2410-- Reading debug info from /lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--2410-- .. CRC mismatch (computed a765a73c wanted 8d13be57)*/
/*--2410-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libm-2.11.1.so ..*/
/*--2410-- Reading syms from /lib/tls/i686/cmov/libc-2.11.1.so (0x4062000)*/
/*--2410-- Reading debug info from /lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--2410-- .. CRC mismatch (computed 2236eb0a wanted a071c0c3)*/
/*--2410-- Reading debug info from /usr/lib/debug/lib/tls/i686/cmov/libc-2.11.1.so ..*/
/*--2410-- REDIR: 0x40d5b10 (rindex) redirected to 0x4025ae0 (rindex)*/
/*--2410-- REDIR: 0x40d57f0 (__GI_strlen) redirected to 0x4026050 (__GI_strlen)*/
/*clist options: (p)rint, (s)earch, (i)nsert, (d)elete, (q) quit */
/*i*/
/*--2410-- REDIR: 0x40d82b0 (strchrnul) redirected to 0x4027510 (strchrnul)*/
/*insert item: 1*/
/*new item: 1*/
/*--2410-- REDIR: 0x40d1f40 (malloc) redirected to 0x4024e9b (malloc)*/
/*--2410-- REDIR: 0x40d6f20 (memcpy) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--2410-- REDIR: 0x4172000 (__memcpy_ssse3) redirected to 0x40267f0 (memcpy)*/
/*i*/
/*insert item: 2*/
/*new item: 2*/
/*i*/
/*insert item: 3*/
/*new item: 3*/
/*p*/
/*3 2 1 */
/*s*/
/*search for item: 0*/
/*--2410-- REDIR: 0x40d6540 (bcmp) redirected to 0x401f44c (_vgnU_ifunc_wrapper)*/
/*--2410-- REDIR: 0x417d160 (__memcmp_ssse3) redirected to 0x4027000 (bcmp)*/
/*item 0 not found*/
/*s*/
/*search for item: 2*/
/*item 2 found*/
/*d*/
/*delete item: 2*/
/*--2410-- REDIR: 0x40d1e60 (free) redirected to 0x4024ab5 (free)*/
/*item 2 deleted*/
/*p*/
/*3 1 */
/*q*/
/*==2410== */
/*==2410== HEAP SUMMARY:*/
/*==2410==     in use at exit: 0 bytes in 0 blocks*/
/*==2410==   total heap usage: 6 allocs, 6 frees, 48 bytes allocated*/
/*==2410== */
/*==2410== All heap blocks were freed -- no leaks are possible*/
/*==2410== */
/*==2410== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/
/*--2410-- */
/*--2410-- used_suppression:     13 dl-hack3-cond-1*/
/*==2410== */
/*==2410== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 6)*/

