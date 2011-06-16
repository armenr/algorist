MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

OBJECTS = \
	mst \
	priority-queue \
	set-union \
	util \

BINARIES = \
	clist-demo \
	dlist-demo \
	graph1-demo \
	graph2-demo \
	hash-fn-demo \
	hash-demo \
	list-demo \
	queue-demo \
	set-union2-demo \
	skip-demo \
	stack-demo \
	tree-demo \
          
make:	$(OBJECTS) $(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

clist-demo:	clist.o clist-demo.o 
	$(CC) $(LFLAGS) -o $@ clist.o clist-demo.o 

dlist-demo:	dlist.o dlist-demo.o 
	$(CC) $(LFLAGS) -o $@ dlist.o dlist-demo.o 

graph1-demo:	graph1.o graph1-demo.o skip-list.o util.o
	$(CC) $(LFLAGS) -o $@ graph1.o graph1-demo.o skip-list.o util.o

graph2-demo:	graph2.o graph2-demo.o 
	$(CC) $(LFLAGS) -o $@ graph2.o graph2-demo.o 

hash-demo:	hash-tbl.o hash-demo.o hash-fn.o util.o
	$(CC) $(LFLAGS) -o $@ hash-tbl.o hash-demo.o hash-fn.o util.o

hash-fn-demo:	hash-fn.o hash-fn-demo.o 
	$(CC) $(LFLAGS) -o $@ hash-fn.o hash-fn-demo.o 

list-demo:	list.o list-demo.o 
	$(CC) $(LFLAGS) -o $@ list.o list-demo.o 

mst:	mst.c
	$(CC) -c $@.c

priority-queue:	priority-queue.c
	$(CC) -c $@.c

queue-demo:	queue.o queue-demo.o list.o
	$(CC) $(LFLAGS) -o $@ queue.o queue-demo.o list.o 

set-union:	set-union.c
	$(CC) -c $@.c

set-union2-demo:	set-union2.o set-union2-demo.o
	$(CC) $(LFLAGS) -o $@ set-union2.o set-union2-demo.o 

skip-demo:	skip-list.o skip-demo.o util.o
	$(CC) $(LFLAGS) -o $@ skip-list.o skip-demo.o util.o

stack-demo:	stack.o stack-demo.o list.o
	$(CC) $(LFLAGS) -o $@ stack.o stack-demo.o list.o 

tree-demo:	tree.o tree-demo.o util.o
	$(CC) $(LFLAGS) -o $@ tree.o tree-demo.o util.o

util:	util.c
	$(CC) -c $@.c

