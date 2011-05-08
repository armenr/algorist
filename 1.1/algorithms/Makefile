MAKEFILE = Makefile

SOURCES = \
	8-queens.c \
	bfs-demo.c \
	dfs-demo.c \
	edit-string-demo.c \
	kruskal-demo.c \
	permutations.c \
	prim-demo.c \
	subsets.c \
	sudoku.c \

OBJECTS = \
	8-queens.o \
	bfs-demo.o \
	dfs-demo.o \
	edit-string-demo.o \
	kruskal-demo.o \
	permutations.o \
	prim-demo.o \
	subsets.o \
	sudoku.o \

BINARIES = \
	8-queens \
	bfs-demo \
	dfs-demo \
	edit-string-demo \
	kruskal-demo \
	permutations \
	prim-demo \
	subsets \
	sudoku \

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

8-queens:	8-queens.o back-track.o
	$(CC) $(LFLAGS) -o $@ 8-queens.o back-track.o

bfs-demo:	bfs-dfs.o bfs-demo.o
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o bfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

dfs-demo:	bfs-dfs.o dfs-demo.o
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o dfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 

edit-string-demo:	edit-string-demo.o edit-string.o 
	$(CC) $(LFLAGS) -o $@ edit-string-demo.o edit-string.o

kruskal-demo: kruskal-demo.o kruskal.o 
	$(CC) $(LFLAGS) -o $@ kruskal-demo.o kruskal.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)set-union.o 

permutations:	permutations.o back-track.o
	$(CC) $(LFLAGS) -o $@ permutations.o back-track.o

prim-demo: prim-demo.o prim.o bfs-dfs.o 
	$(CC) $(LFLAGS) -o $@ prim-demo.o prim.o bfs-dfs.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o 
	
