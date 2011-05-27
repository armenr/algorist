MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
	8-queens \
	edit-string-demo \
	floyd-demo \
	mst-demo \
	netflow-demo \
	permutations \
	search-demo \
	sort-demo \
#	subsets \
#	sudoku \

make:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

8-queens:	8-queens.o back-track.o
	$(CC) $(LFLAGS) -o $@ 8-queens.o back-track.o

edit-string-demo:	edit-string-demo.o edit-string.o 
	$(CC) $(LFLAGS) -o $@ edit-string-demo.o edit-string.o

floyd-demo:	floyd-demo.o floyd.o 
	$(CC) $(LFLAGS) -o $@ floyd-demo.o floyd.o

mst-demo: mst-demo.o kruskal.o prim.o
	$(CC) $(LFLAGS) -o $@ mst-demo.o kruskal.o prim.o \
	$(DS)graph1.o $(DS)mst.o $(DS)set-union.o $(DS)skip-list.o

netflow-demo: netflow-demo.o netflow.o graph-search.o graph-vertex.o
	$(CC) $(LFLAGS) -o $@ netflow-demo.o netflow.o graph-search.o graph-vertex.o \
	$(DS)graph1.o $(DS)list.o $(DS)queue.o $(DS)skip-list.o $(DS)stack.o

permutations:	permutations.o back-track.o
	$(CC) $(LFLAGS) -o $@ permutations.o back-track.o

search-demo:	 search-demo.o graph-print.o graph-search.o graph-vertex.o
	$(CC) $(LFLAGS) -o $@  search-demo.o graph-print.o graph-search.o \
	graph-vertex.o \
	$(DS)graph1.o $(DS)list.o $(DS)queue.o $(DS)skip-list.o $(DS)stack.o

sort-demo: sort.o sort-demo.o random.o
	$(CC) $(LFLAGS) -o $@ sort.o sort-demo.o random.o \
	$(DS)list.o $(DS)priority-queue.o $(DS)queue.o \

