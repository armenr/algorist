MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
	back-track-demo \
	edit-string-demo \
	floyd-demo \
	heuristics-demo \
	mst-demo \
	netflow-demo \
	search-demo \
	sort-demo \

make:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

DS =../ds/

back-track-demo:	back-track-demo.o back-track.o back-track-funcs.o \
	graph-print.o graph-search.o graph-vertex.o
	$(CC) $(LFLAGS) -o $@ back-track-demo.o back-track.o back-track-funcs.o \
	graph-print.o graph-search.o 	graph-vertex.o \
	$(DS)graph1.o $(DS)list.o $(DS)queue.o $(DS)skip-list.o $(DS)stack.o

edit-string-demo:	edit-string-demo.o edit-string.o 
	$(CC) $(LFLAGS) -o $@ edit-string-demo.o edit-string.o

floyd-demo:	floyd-demo.o floyd.o 
	$(CC) $(LFLAGS) -o $@ floyd-demo.o floyd.o

heuristics-demo:  heuristics-demo.o heuristics.o random.o tsp.o 
	$(CC) $(LFLAGS) -o $@ heuristics-demo.o heuristics.o random.o tsp.o 
	
mst-demo: mst-demo.o kruskal.o prim.o
	$(CC) $(LFLAGS) -o $@ mst-demo.o kruskal.o prim.o \
	$(DS)graph1.o $(DS)mst.o $(DS)set-union.o $(DS)skip-list.o

netflow-demo: netflow-demo.o netflow.o graph-search.o graph-vertex.o
	$(CC) $(LFLAGS) -o $@ netflow-demo.o netflow.o graph-search.o graph-vertex.o \
	$(DS)graph1.o $(DS)list.o $(DS)queue.o $(DS)skip-list.o $(DS)stack.o

search-demo:	 search-demo.o graph-print.o graph-search.o graph-vertex.o
	$(CC) $(LFLAGS) -o $@  search-demo.o graph-print.o graph-search.o \
	graph-vertex.o \
	$(DS)graph1.o $(DS)list.o $(DS)queue.o $(DS)skip-list.o $(DS)stack.o

sort-demo: sort.o sort-demo.o random.o
	$(CC) $(LFLAGS) -o $@ sort.o sort-demo.o random.o \
	$(DS)list.o $(DS)priority-queue.o $(DS)queue.o \


