MAKEFILE = Makefile

SOURCES = \
	bfs-demo.c \
	clist-demo.c \
	dlist-demo.c \
	hash-fn-demo.c \
	hash-demo.c \
	kruskal-demo.c \
	list-demo.c \
	queue-demo.c \
	set-union2-demo.c \
	skip-demo.c \
	sort-demo.c \
	stack-demo.c \
	tree-demo.c \
  
OBJECTS = \
	bfs-demo.o \
	clist-demo.o \
	dlist-demo.o \
	hash-fn-demo.o \
	hash-demo.o \
	kruskal-demo.o \
	list-demo.o \
	queue-demo.o \
	set-union2-demo.o \
	skip-demo.o \
	sort-demo.o \
	stack-demo.o \
	tree-demo.o \
          
BINARIES = \
	bfs-demo \
	clist-demo \
	dlist-demo \
	hash-fn-demo \
	hash-demo \
	kruskal-demo \
	list-demo \
	queue-demo \
	set-union2-demo \
	skip-demo \
	sort-demo \
	stack-demo \
	tree-demo \
          
CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)

$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

bfs-demo:	bfs-dfs.o bfs-demo.o $(DS)graph.o $(DS)list.o $(DS)queue.o 
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o bfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

clist-demo:	clist.o clist-demo.o 
	$(CC) $(LFLAGS) -o $@ clist.o clist-demo.o 

dlist-demo:	dlist.o dlist-demo.o 
	$(CC) $(LFLAGS) -o $@ dlist.o dlist-demo.o 

hash-demo:	hashtbl.o hash-demo.o 
	$(CC) $(LFLAGS) -o $@ hashtbl.o hash-demo.o 

hash-fn-demo:	hash-fn.o hash-fn-demo.o 
	$(CC) $(LFLAGS) -o $@ hash-fn.o hash-fn-demo.o 

kruskal-demo: kruskal-demo.o kruskal.o set-union.o
	$(CC) $(LFLAGS) -o $@ kruskal-demo.o kruskal.o set-union.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

list-demo:	list.o list-demo.o 
	$(CC) $(LFLAGS) -o $@ list.o list-demo.o 

queue-demo:	queue.o queue-demo.o list.o
	$(CC) $(LFLAGS) -o $@ queue.o queue-demo.o list.o 

set-union2-demo:	set-union2.o set-union2-demo.o
	$(CC) $(LFLAGS) -o $@ set-union2.o set-union2-demo.o 

skip-demo:	skip-list.o skip-demo.o
	$(CC) $(LFLAGS) -o $@ skip-list.o skip-demo.o

sort-demo: sort.o sort-demo.o list.o priority-queue.o queue.o random.o
	$(CC) $(LFLAGS) -o $@ sort.o sort-demo.o list.o priority-queue.o queue.o \
	random.o 

stack-demo:	stack.o stack-demo.o list.o
	$(CC) $(LFLAGS) -o $@ stack.o stack-demo.o list.o 

tree-demo:	tree.o tree-demo.o
	$(CC) $(LFLAGS) -o $@ tree.o tree-demo.o 
