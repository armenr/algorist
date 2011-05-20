MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
	8-queens \
	bfs-demo \
	bi-connected \
	bi-partite \
	connected \
	dfs-demo \
	edit-string-demo \
	mst-demo \
	permutations \
	sort-demo \
	subsets \
	sudoku \

make:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

8-queens:	8-queens.o back-track.o
	$(CC) $(LFLAGS) -o $@ 8-queens.o back-track.o

bfs-demo:	graph-search.o bfs-demo.o
	$(CC) $(LFLAGS) -o $@ graph-search.o bfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

bi-connected:	graph-search.o bi-connected.o
	$(CC) $(LFLAGS) -o $@ graph-search.o bi-connected.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

bi-partite:	graph-search.o bi-partite.o
	$(CC) $(LFLAGS) -o $@ graph-search.o bi-partite.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

connected:	graph-search.o connected.o
	$(CC) $(LFLAGS) -o $@ graph-search.o connected.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

dfs-demo:	graph-search.o dfs-demo.o
	$(CC) $(LFLAGS) -o $@ graph-search.o dfs-demo.o \
	$(DS)graph.o $(DS)list.o 	$(DS)queue.o $(DS)skip-list.o

edit-string-demo:	edit-string-demo.o edit-string.o 
	$(CC) $(LFLAGS) -o $@ edit-string-demo.o edit-string.o

mst-demo: mst-demo.o kruskal.o prim.o
	$(CC) $(LFLAGS) -o $@ mst-demo.o kruskal.o prim.o \
	$(DS)graph.o $(DS)mst.o $(DS)set-union.o 	$(DS)skip-list.o

permutations:	permutations.o back-track.o
	$(CC) $(LFLAGS) -o $@ permutations.o back-track.o

sort-demo: sort.o sort-demo.o random.o
	$(CC) $(LFLAGS) -o $@ sort.o sort-demo.o random.o\
	$(DS)list.o $(DS)priority-queue.o $(DS)queue.o \

