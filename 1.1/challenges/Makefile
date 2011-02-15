MAKEFILE = Makefile

SOURCES = 3n+1.c check.c common_perm.c crypt.c crypt2.c doublets.c\
  file_frag.c graph.c hartals.c \
  jolly.c judge.c list.c mine.c poker-hands.c \
  scoreboard.c trip.c voting.c waldorf.c wertyu.c \
  yahtzee.c 

OBJECTS = 3n+1.o check.o common_perm.o crypt.o crypt2.o doublets.o \
  file_frag.o graph.o hartals.o \
  jolly.o judge.o mine.o poker-hands.o \
  scoreboard.o \
  trip.o voting.o waldorf.o wertyu.o yahtzee.o 
          
BINARIES = 3n+1 check common_perm crypt crypt2 doublets file_frag hartals \
  jolly judge mine poker-hands scoreboard \
  trip voting waldorf wertyu yahtzee 
          
CC = gcc
CFLAGS = -Wall -Wextra -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

DS =../ds/

crypt: crypt.o $(DS)stack.o $(DS)list.o
	$(CC) -o $@ crypt.o $(DS)stack.o $(DS)list.o $(LFLAGS)

crypt2: crypt2.o $(DS)hashtbl.o
	$(CC) -o $@ crypt2.o $(DS)hashtbl.o $(LFLAGS)

doublets: doublets.o $(DS)graph.o
	$(CC) -o $@ doublets.o $(DS)graph.o $(LFLAGS)

judge:	judge.o $(DS)queue.o $(DS)list.o
		$(CC) -o $@ judge.o $(DS)queue.o $(DS)list.o $(LFLAGS)

wertyu: wertyu.o $(DS)hashtbl.o 
	$(CC) -o $@ wertyu.o $(DS)hashtbl.o $(LFLAGS)

lint:	
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup
 
clean: 	
	rm -f core *.o a.out $(BINARIES)

