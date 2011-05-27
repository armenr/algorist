MAKEFILE = Makefile

SOURCES = \
	birthday.c \
	coin-toss.c \
	coupon.c \
	crap-shoot.c \
	random-walk.c

OBJECTS = \
	birthday.o \
	coin-toss.o \
	coupon.o \
	crap-shoot.o \
	random-walk.o
          
BINARIES = \
	birthday \
	coin-toss \
	coupon \
	crap-shoot \
	random-walk
          
INCLUDES = 

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

clean: 	
	rm -f core *.o a.out $(BINARIES)

