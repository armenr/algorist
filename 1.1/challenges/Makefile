MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
  3n+1 \
  bridge \
  check \
  common_perm \
  crypt \
  crypt2 \
  doublets\
  doublets-dfs\
  file_frag \
  flapjacks \
  fmt \
  hartals \
  jolly \
  judge \
  mine \
  poker-hands \
  scoreboard \
  shoemaker \
  trip \
  vito \
  voting \
  waldorf \
  wertyu \
  yahtzee 
          
make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

AL =../algorithms/
DS =../ds/

crypt: crypt.o $(DS)stack.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ crypt.o $(DS)stack.o $(DS)list.o

crypt2: crypt2.o $(DS)hash-tbl.o
	$(CC) $(LFLAGS) -o $@ crypt2.o $(DS)hash-tbl.o

doublets: doublets.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hash-tbl.o $(DS)stack.o $(DS)list.o 
	$(CC) $(LFLAGS) -o $@ doublets.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hash-tbl.o  $(DS)stack.o $(DS)list.o 

doublets-dfs: doublets-dfs.o $(AL)bfs-dfs.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hash-tbl.o $(DS)queue.o $(DS)list.o 
	$(CC) $(LFLAGS) -o $@ doublets-dfs.o $(AL)bfs-dfs.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hash-tbl.o $(DS)queue.o $(DS)list.o 

fmt:	fmt.o $(DS)queue.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ fmt.o $(DS)queue.o $(DS)list.o

judge:	judge.o $(DS)queue.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ judge.o $(DS)queue.o $(DS)list.o

wertyu: wertyu.o $(DS)hash-tbl.o 
	$(CC) $(LFLAGS) -o $@ wertyu.o $(DS)hash-tbl.o
	
