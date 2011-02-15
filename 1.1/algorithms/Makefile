MAKEFILE = Makefile

SOURCES = \
	bfs-demo.c \
	dfs-demo.c \
	kruskal-demo.c \
	prim-demo.c \

OBJECTS = \
	bfs-demo.o \
	dfs-demo.o \
	kruskal-demo.o \
	prim-demo.o \

BINARIES = \
	bfs-demo \
	dfs-demo \
	kruskal-demo \
	prim-demo \

CC = gcc
CFLAGS = -Wall -Wextra -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

lint:	
	lint -h $(SOURCES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

bfs-demo:	bfs-dfs.o bfs-demo.o
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o bfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

dfs-demo:	bfs-dfs.o dfs-demo.o
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o dfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

kruskal-demo: kruskal-demo.o kruskal.o set-union.o
	$(CC) $(LFLAGS) -o $@ kruskal-demo.o kruskal.o set-union.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

prim-demo: prim-demo.o prim.o bfs-dfs.o 
	$(CC) $(LFLAGS) -o $@ prim-demo.o prim.o bfs-dfs.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 
	
