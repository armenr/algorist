MAKEFILE = Makefile

SOURCES = backtrack.c 8-queens.c permutations.c subsets.c queue.c \
	graph.c random.c sort.c bfs-dfs.c bfs-demo.c dfs-demo.c 	connected.c  \
	topsort.c floyd.c floyd-demo.c findcycle.c editdistance.c stringedit.c \
	stringedit-demo.c lcs.c substringedit.c geometry.c superman.c convex-hull.c \
	convex-hull-demo.c triangulate.c distance.c list.c \
	polly.c primes.c bignum.c editbrute.c editbrute-demo.c elevator.c order.c \
	geotest.c netflow.c paths.c sudoku.c tsp.c fib.c partition.c \
	biconnected.c stack.c strong.c topsort1.c bipartite.c priority_queue.c \
	kruskal.c set_union.c list-demo.c tree-demo.c matrix.c josephus.c prim.c \
	dijkstra.c netflow-demo.c annealing.c binomial.c ackermann.c matrix-demo.c \
	mwt.c mwt-demo.c plates.c gcd.c sort-demo.c tree.c triangulate-demo.c \
	hash-demo.c hashtbl.c

OBJECTS = backtrack.o 8-queens.o permutations.o subsets.o queue.o  \
	graph.o random.o sort.o bfs-dfs.o bfs-demo.o dfs-demo.o list.o \
	connected.o topsort.o floyd.o floyd-demo.o findcycle.o editbrute-demo.o \
	editdistance.o editbrute.o stringedit-demo.o lcs.o substringedit.o geometry.o \
	superman.o convex-hull.o convex-hull-demo.o triangulate.o distance.o \
	polly.o primes.o bignum.o elevator.o order.o geotest.o plates.o \
  netflow.o paths.o sudoku.o tsp.o fib.o partition.o biconnected.o stack.o \
	strong.o topsort1.o bipartite.o priority_queue.o kruskal.o set_union.o \
	list-demo.o tree-demo.o matrix.o josephus.o prim.o dijkstra.o netflow-demo.o \
	annealing.o binomial.o ackermann.o matrix-demo.o mwt.o mwt-demo.o gcd.o \
	sort-demo.o tree.o triangulate-demo.o hash-demo.o

BINARIES = 8-queens permutations subsets bfs-demo dfs-demo \
  connected topsort prim floyd-demo findcycle stringedit-demo lcs \
  substringedit superman convex-hull-demo triangulate-demo  \
	polly primes bignum elevator order geotest paths sudoku tsp-demo plates \
	fib partition biconnected strong topsort1 bipartite kruskal matrix-demo tree-demo \
	list-demo josephus dijkstra netflow-demo binomial editbrute-demo ackermann \
	mwt-demo gcd sort-demo hash-demo

INCLUDES = bool.h backtrack.h queue.h graph.h editdistance.h \
  geometry.h annealing.h tsp.h stack.h priority_queue.h set_union.h \
  list.h tree.h item.h kruskal.h netflow.h bfs-dfs.h sudoku.h random.h \
  stringedit.h editbrute.h convex-hull.h matrix.h mwt.h partition.h sort.h \
  triangulate.h hashtbl.h

CC = gcc
CFLAGS = -Wall -Wextra -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

lint:	
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup
 
clean: 	
	rm -f core *.o a.out $(BINARIES)

tar:	
	make clean
	tar cvf /tmp/bookprograms.tar .


8-queens:	8-queens.o backtrack.o 
		$(CC) -o $@ 8-queens.o backtrack.o $(LFLAGS)

bfs-demo:	queue.o graph.o bfs-dfs.o bfs-demo.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o bfs-demo.o $(LFLAGS)

biconnected:	biconnected.o bfs-dfs.o queue.o graph.o
		$(CC) -o $@ biconnected.o bfs-dfs.o queue.o graph.o $(LFLAGS)

bipartite:	bipartite.o queue.o graph.o bfs-dfs.o
		$(CC) -o $@ bipartite.o queue.o graph.o bfs-dfs.o $(LFLAGS)

connected:	queue.o graph.o bfs-dfs.o connected.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o connected.o $(LFLAGS)

convex-hull-demo:	geometry.o convex-hull.o convex-hull-demo.o
		$(CC) -o $@ geometry.o convex-hull.o convex-hull-demo.o $(LFLAGS)

dfs-demo:	queue.o graph.o bfs-dfs.o dfs-demo.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o dfs-demo.o $(LFLAGS)

dijkstra:		graph.o dijkstra.o queue.o
		$(CC) -o $@ bfs-dfs.c graph.o dijkstra.o queue.o $(LFLAGS)

editbrute-demo:	editbrute.o stringedit.o editbrute-demo.o 
		$(CC) -o $@ editbrute.o stringedit.o editbrute-demo.o $(LFLAGS)

findcycle:	queue.o graph.o bfs-dfs.o findcycle.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o findcycle.o $(LFLAGS)

floyd-demo:	floyd.o floyd-demo.o 
		$(CC) -o $@ floyd.o floyd-demo.o $(LFLAGS)

gcd:		gcd.o
		$(CC) -o $@ gcd.o $(LFLAGS)

geotest:	geometry.o geotest.o
		$(CC) -o $@ geometry.o geotest.o $(LFLAGS)

hash-demo:	hashtbl.o hash-demo.o 
		$(CC) -o $@ hashtbl.o hash-demo.o $(LFLAGS)

kruskal:		graph.o kruskal.o queue.o set_union.o
		$(CC) -o $@ bfs-dfs.c graph.o kruskal.o queue.o set_union.o $(LFLAGS)

lcs:		editdistance.o lcs.o
		$(CC) -o $@ editdistance.o lcs.o $(LFLAGS)

list-demo:	list.o list-demo.o 
		$(CC) -o $@ list.o list-demo.o $(LFLAGS)

matrix-demo:	matrix.o matrix-demo.o 
		$(CC) -o $@ matrix.o matrix-demo.o $(LFLAGS)

mwt-demo:	mwt.o geometry.o mwt-demo.o 
		$(CC) -o $@ mwt.o geometry.o mwt-demo.o $(LFLAGS)

netflow-demo:	netflow-demo.o netflow.o queue.o
		$(CC) -o $@ netflow.o queue.o netflow-demo.o $(LFLAGS)

paths:		backtrack.o paths.o graph.o
		$(CC) -o $@ paths.o backtrack.o graph.o $(LFLAGS)

permutations:	backtrack.o permutations.o
		$(CC) -o $@ permutations.o backtrack.o $(LFLAGS)

plates:		plates.o
		$(CC) -o $@ plates.o $(LFLAGS)

prim:		graph.o prim.o queue.o
		$(CC) -o $@ bfs-dfs.c graph.o prim.o queue.o $(LFLAGS)

primes:		primes.o
		$(CC) -o $@ primes.o $(LFLAGS)

stringedit-demo:	editdistance.o stringedit.o stringedit-demo.o  
		$(CC) -o $@ editdistance.o stringedit.o stringedit-demo.o $(LFLAGS)

substringedit:	editdistance.o substringedit.o
		$(CC) -o $@ editdistance.o substringedit.o $(LFLAGS)

superman:	geometry.o superman.o
		$(CC) -o $@ geometry.o superman.o $(LFLAGS)

strong:		bfs-dfs.o queue.o graph.o stack.o strong.o 
		$(CC) -o $@ bfs-dfs.o queue.o graph.o stack.o strong.o $(LFLAGS)

sort-demo:	random.o queue.o priority_queue.o sort.o sort-demo.o
		$(CC) -o $@ random.o queue.o priority_queue.o sort.o sort-demo.o $(LFLAGS)

topsort:	queue.o graph.o topsort.o
		$(CC) -o $@ queue.o graph.o topsort.o $(LFLAGS)

topsort1:	topsort1.o queue.o graph.o stack.o bfs-dfs.o
		$(CC) -o $@ topsort1.o queue.o graph.o stack.o bfs-dfs.o $(LFLAGS)

tree-demo:		tree.o tree-demo.o
		$(CC) -o $@ tree.o tree-demo.o $(LFLAGS)

triangulate-demo:	geometry.o triangulate.o triangulate-demo.o
		$(CC) -o $@ geometry.o triangulate.o triangulate-demo.o $(LFLAGS)

tsp-demo:		annealing.o random.o tsp.o tsp-demo.o
		$(CC) -o $@ annealing.o random.o tsp.o tsp-demo.o $(LFLAGS)


