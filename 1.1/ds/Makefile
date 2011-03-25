MAKEFILE = Makefile

SOURCES = \
	bfs-demo.c \
	list-demo.c \
	queue-demo.c \
	sort-demo.c \
	stack-demo.c \
	tree-demo.c \ 
  
OBJECTS = \
	bfs-demo.o \
	list-demo.o \
	queue-demo.o \
	sort-demo.o \
	stack-demo.o \
	tree-demo.o \
          
BINARIES = \
	bfs-demo \
	list-demo \
	queue-demo \
	sort-demo \
	stack-demo \
	tree-demo \
          
CC = gcc
CFLAGS = -Wall -Wextra -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

DS =../ds/

bfs-demo:	bfs-dfs.o bfs-demo.o $(DS)graph.o $(DS)list.o $(DS)queue.o 
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o bfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

list-demo:	list.o list-demo.o 
	$(CC) $(LFLAGS) -o $@ list.o list-demo.o 

queue-demo:	queue.o queue-demo.o list.o
	$(CC) $(LFLAGS) -o $@ queue.o queue-demo.o list.o 

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

