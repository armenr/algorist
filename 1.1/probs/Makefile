MAKEFILE = Makefile

SOURCES = birthday.c coin-toss.c coupon.c crap-shoot.c random-walk.c

OBJECTS = birthday.o coin-toss.o coupon.o crap-shoot.o random-walk.o
          
BINARIES = birthday coin-toss coupon crap-shoot random-walk
          
INCLUDES = 


CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi #-pedantic 
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

#wertyu: hashtbl.o wertyu.o
#	$(CC) -o $@ hashtbl.o wertyu.o $(LFLAGS)

lint:	
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup
 
clean: 	
	rm -f core *.o a.out $(BINARIES)

