MAKEFILE = Makefile

SOURCES = \
	bfs-demo.c \
	clist-demo.c \
	dlist-demo.c \
	hash-demo.c \
	list-demo.c \
	queue-demo.c \
	skip-demo.c \
	sort-demo.c \
	stack-demo.c \
	tree-demo.c \ 
  
OBJECTS = \
	bfs-demo.o \
	clist-demo.o \
	dlist-demo.o \
	hash-demo.o \
	list-demo.o \
	queue-demo.o \
	skip-demo.o \
	sort-demo.o \
	stack-demo.o \
	tree-demo.o \
          
BINARIES = \
	bfs-demo \
	clist-demo \
	dlist-demo \
	hash-demo \
	list-demo \
	queue-demo \
	skip-demo \
	sort-demo \
	stack-demo \
	tree-demo \
          
CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi #-pedantic 
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

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

list-demo:	list.o list-demo.o 
	$(CC) $(LFLAGS) -o $@ list.o list-demo.o 

queue-demo:	queue.o queue-demo.o list.o
	$(CC) $(LFLAGS) -o $@ queue.o queue-demo.o list.o 

skip-demo:	skip-list.o skip-demo.o
	$(CC) $(LFLAGS) -o $@ skip-list.o skip-demo.o

sort-demo: sort.o sort-demo.o list.o priority-queue.o queue.o random.o
	$(CC) $(LFLAGS) -o $@ sort.o sort-demo.o list.o priority-queue.o queue.o \
	random.o 

stack-demo:	stack.o stack-demo.o list.o
	$(CC) $(LFLAGS) -o $@ stack.o stack-demo.o list.o 

tree-demo:	tree.o tree-demo.o
	$(CC) $(LFLAGS) -o $@ tree.o tree-demo.o 

lint:	
	lint -h $(SOURCES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

