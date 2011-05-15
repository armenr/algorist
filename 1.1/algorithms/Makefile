MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
	8-queens \
	bfs-demo \
	dfs-demo \
	edit-string-demo \
	kruskal-demo \
	permutations \
	prim-demo \
	sort-demo \
	subsets \
	sudoku \

make:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

8-queens:	8-queens.o back-track.o
	$(CC) $(LFLAGS) -o $@ 8-queens.o back-track.o

bfs-demo:	bfs-dfs.o bfs-demo.o
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o bfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

dfs-demo:	bfs-dfs.o dfs-demo.o
	$(CC) $(LFLAGS) -o $@ bfs-dfs.o dfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

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
	
sort-demo: sort.o sort-demo.o random.o
	$(CC) $(LFLAGS) -o $@ sort.o sort-demo.o random.o\
	$(DS)list.o $(DS)priority-queue.o $(DS)queue.o \

