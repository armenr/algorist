/*see README for original credits */

#include"hash-fn.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	hash_t (*hash)(const unsigned char *key) = NULL;

  hashfunc_s funcs[] = {
	  {"add", add_hash},
	  {"xor", xor_hash},
	  {"sax", sax_hash},
	  {"sdbm", sdbm_hash},
	  {"bernstein", bernstein_hash}
  };

  /*select a function*/
	if(argc > 1) {
  	int i, sz = sizeof(funcs) / sizeof(hashfunc_s);

		for(i = 0; i < sz; i++) 
			if(!strcmp(argv[1], funcs[i].name)) {
				hash = funcs[i].func;
				break;
			}
			
		if(hash == NULL) {
			fprintf(stderr, "ERROR: Could not find the %s hash function\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		
	} else 
	  hash = funcs[0].func; /*default to first entry (add_hash)*/

	hash_t hsize;
	if(argc > 2) 
	  hsize = atol(argv[2]);
	else 
	  hsize = 32768;

/*  
This program will read a list of words, one for each line, from stdin and print 
the corresponding hash values. The hash function and table size are specified 
as command line arguments.
*/
  char line[256];

  while(fgets(line, 256, stdin)) {
	  char* p;

		if((p = strchr(line, '\r')))
		  *p = '\0';
		if((p = strchr(line, '\n'))) 
		  *p = '\0';

/*
The hash functions take one argument, a '\0'-terminated string, and return the 
calculated hash value. This value is later redused to the hash table size before 
it is printed. 
*/
		printf("%lu\n", hash((unsigned char*)line) % hsize);
	}
	
	return EXIT_SUCCESS;
}

/*osman@osman-dev:~/src/algorist/1.1/ds$ make hash-fn-demo && ./hash-fn-demo */
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o hash-fn.o hash-fn.c*/
/*gcc -Wall -Wcast-qual -Wextra -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wwrite-strings -ansi -O2    -c -o hash-fn-demo.o hash-fn-demo.c*/
/*gcc -lm  -o hash-fn-demo hash-fn.o hash-fn-demo.o */
/*hello*/
/*532*/
/*world!*/
/*585*/
