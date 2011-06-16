MAKEFILE = Makefile

CC = gcc
CFLAGS = -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2 #-pedantic 
LFLAGS = -lm 

BINARIES = \
	birthday \
	coin-toss \
	coupon \
	crap-shoot \
	random-walk
          
make:	$(BINARIES)
	
clean: 	
	rm -f core *.o a.out $(BINARIES)

