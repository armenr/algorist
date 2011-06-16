MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
  3n+1 \
  bridge \
  check \
  common-perm \
  crypt \
  crypt2 \
  doublets\
  doublets-dfs\
  file-frag \
  flapjacks \
  fmt \
  hartals \
  jolly \
  judge \
  mine \
  poker-hands \
  scoreboard \
  trip \
  vito \
  voting \
  waldorf \
  wertyu \
          
make:	$(BINARIES)
	
clean: 	
	rm -f core *.o a.out $(BINARIES)

AL =../algorithms/
DS =../ds/

bridge: bridge.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ bridge.o $(DS)util.o

crypt: crypt.o $(DS)stack.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ crypt.o $(DS)stack.o $(DS)list.o

crypt2: crypt2.o $(DS)hash-tbl.o $(DS)hash-fn.o $(DS)util.o
	$(CC) $(LFLAGS) -o $@ crypt2.o $(DS)hash-tbl.o $(DS)hash-fn.o $(DS)util.o

doublets: doublets.o $(AL)edit-string.o \
	$(DS)graph2.o $(DS)hash-tbl.o $(DS)stack.o $(DS)list.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ doublets.o $(AL)edit-string.o \
	$(DS)graph2.o $(DS)hash-tbl.o $(DS)stack.o $(DS)list.o $(DS)util.o 

doublets-dfs: doublets-dfs.o $(AL)bfs-dfs.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hash-tbl.o $(DS)queue.o $(DS)list.o 
	$(CC) $(LFLAGS) -o $@ doublets-dfs.o $(AL)bfs-dfs.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hash-tbl.o $(DS)queue.o $(DS)list.o 

file-frag: file-frag.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ file-frag.o $(DS)util.o

flapjacks: flapjacks.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ flapjacks.o $(DS)util.o

fmt:	fmt.o $(DS)queue.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ fmt.o $(DS)queue.o $(DS)list.o

hartals: hartals.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ hartals.o $(DS)util.o

judge:	judge.o $(DS)queue.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ judge.o $(DS)queue.o $(DS)list.o

vito: vito.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ vito.o $(DS)util.o

waldorf: waldorf.o $(DS)util.o 
	$(CC) $(LFLAGS) -o $@ waldorf.o $(DS)util.o

wertyu: wertyu.o $(DS)hash-tbl.o $(DS)hash-fn.o $(DS)util.o
	$(CC) $(LFLAGS) -o $@ wertyu.o $(DS)hash-tbl.o $(DS)hash-fn.o $(DS)util.o
	
