MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

OBJECTS = \
	set-union \

BINARIES = \
	clist-demo \
	dlist-demo \
	graph-demo \
	graph-demo2 \
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

graph-demo:	graph.o graph-demo.o skip-list.o
	$(CC) $(LFLAGS) -o $@ graph.o graph-demo.o skip-list.o

graph-demo2:	graph2.o graph-demo2.o 
	$(CC) $(LFLAGS) -o $@ graph2.o graph-demo2.o 

hash-demo:	hash-tbl.o hash-demo.o hash-fn.o
	$(CC) $(LFLAGS) -o $@ hash-tbl.o hash-demo.o hash-fn.o

hash-fn-demo:	hash-fn.o hash-fn-demo.o 
	$(CC) $(LFLAGS) -o $@ hash-fn.o hash-fn-demo.o 

list-demo:	list.o list-demo.o 
	$(CC) $(LFLAGS) -o $@ list.o list-demo.o 

queue-demo:	queue.o queue-demo.o list.o
	$(CC) $(LFLAGS) -o $@ queue.o queue-demo.o list.o 

set-union:	set-union.c
	$(CC) -c $@.c

set-union2-demo:	set-union2.o set-union2-demo.o
	$(CC) $(LFLAGS) -o $@ set-union2.o set-union2-demo.o 

skip-demo:	skip-list.o skip-demo.o
	$(CC) $(LFLAGS) -o $@ skip-list.o skip-demo.o

stack-demo:	stack.o stack-demo.o list.o
	$(CC) $(LFLAGS) -o $@ stack.o stack-demo.o list.o 

tree-demo:	tree.o tree-demo.o
	$(CC) $(LFLAGS) -o $@ tree.o tree-demo.o 
