MAKEFILE = Makefile

SOURCES = \
  3n+1.c \
  bridge.c \
  check.c \
  common_perm.c \
  crypt.c \
  crypt2.c \
  doublets.c\
  doublets-dfs.c\
  file_frag.c \
  flapjacks.c \
  fmt.c \
  hartals.c \
  jolly.c \
  judge.c \
  mine.c \
  poker-hands.c \
  scoreboard.c \
  shoemaker.c \
  trip.c \
  vito.c \
  voting.c \
  waldorf.c \
  wertyu.c \
  yahtzee.c 

OBJECTS = \
  3n+1.o \
  bridge.o \
  check.o \
  common_perm.o \
  crypt.o \
  crypt2.o \
  doublets.o\
  doublets-dfs.o\
  file_frag.o \
  flapjacks.o \
  fmt.o \
  hartals.o \
  jolly.o \
  judge.o \
  mine.o \
  poker-hands.o \
  scoreboard.o \
  shoemaker.o \
  trip.o \
  vito.o \
  voting.o \
  waldorf.o \
  wertyu.o \
  yahtzee.o 
          
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

          
CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi #-pedantic 
LFLAGS = -lm # -g -lm -pg


make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)


AL =../algorithms/
DS =../ds/


crypt: crypt.o $(DS)stack.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ crypt.o $(DS)stack.o $(DS)list.o

crypt2: crypt2.o $(DS)hashtbl.o
	$(CC) $(LFLAGS) -o $@ crypt2.o $(DS)hashtbl.o

doublets: doublets.o $(AL)edit-string.o $(DS)graph.o $(DS)hashtbl.o \
	$(DS)stack.o $(DS)list.o 
	$(CC) $(LFLAGS) -o $@ doublets.o $(AL)edit-string.o $(DS)graph.o \
	$(DS)hashtbl.o  $(DS)stack.o $(DS)list.o 

doublets-dfs: doublets-dfs.o $(AL)bfs-dfs.o $(AL)edit-string.o $(DS)graph.o \
	$(DS)hashtbl.o $(DS)queue.o $(DS)list.o 
	$(CC) $(LFLAGS) -o $@ doublets-dfs.o $(AL)bfs-dfs.o $(AL)edit-string.o \
	$(DS)graph.o $(DS)hashtbl.o $(DS)queue.o $(DS)list.o 

fmt:	fmt.o $(DS)queue.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ fmt.o $(DS)queue.o $(DS)list.o

judge:	judge.o $(DS)queue.o $(DS)list.o
	$(CC) $(LFLAGS) -o $@ judge.o $(DS)queue.o $(DS)list.o

wertyu: wertyu.o $(DS)hashtbl.o 
	$(CC) $(LFLAGS) -o $@ wertyu.o $(DS)hashtbl.o


lint:	
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup
 
clean: 	
	rm -f core *.o a.out $(BINARIES)

