/*
 Copyright 2010 Osman Pub

 Licensed under the Apache License, Version 2.0 (the "License"); you may not use
 this file except in compliance with the License.
  
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software distributed
 under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied. See the License for the
 specific language governing permissions and limitations under the License.
 */

/*
3.8.8 Fmt
PC/UVa IDs: 110308/848, Popularity: C, Success rate: low Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

Unix fmt

The unix fmt program reads lines of text, combining
and breaking lines so as to create an
output file with lines as close to without exceeding
72 characters long as possible. The rules for combining and breaking
lines are as follows.

1. A new line may be started anywhere there is a space in the input.
If a new line is started, there will be no trailing blanks at the
end of the previous line or at the beginning of the new line.

2. A line break in the input may be eliminated in the output, provided
it is not followed by a space or another line break. If a line
break is eliminated, it is replaced by a space.

Sample Output

Unix fmt

The unix fmt program reads lines of text, combining and breaking lines
so as to create an output file with lines as close to without exceeding
72 characters long as possible. The rules for combining and breaking
lines are as follows.

1. A new line may be started anywhere there is a space in the input.
If a new line is started, there will be no trailing blanks at the end of
the previous line or at the beginning of the new line.

2. A line break in the input may be eliminated in the output,
provided it is not followed by a space or another line break. If a line
break is eliminated, it is replaced by a space
*/

/*TODO:*/
/*Add and test 2nd delimiter: a new line followed by a space, i.e "\n "*/

#include"../ds/queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DELIMITER "\n\n"
#define NULL_CHAR "\0"
#define NEW_LINE "\n"
#define SPACE " "
#define SPLIT 72

static char* input = 
"Unix fmt\n"
"\n"
"The unix fmt program reads lines of text, combining\n"
"and breaking lines so as to create an\n"
"output file with lines as close to without exceeding\n"
"72 characters long as possible. The rules for combining and breaking\n"
"lines are as follows.\n"
"\n"
"1. A new line may be started anywhere there is a space in the input.\n"
"If a new line is started, there will be no trailing blanks at the\n"
"end of the previous line or at the beginning of the new line.\n"
"\n"
"2. A line break in the input may be eliminated in the output, provided\n"
"it is not followed by a space or another line break. If a line\n"
"break is eliminated, it is replaced by a space.\n"
"\n";

static queue bq;

static int start; /* start of block, passed between functions*/

static void init_bq(void) {
  init_queue(&bq);
}
static void clean_up(void) {
  clear_queue(&bq);
}

/*split input into tokens (blocks), de-limited by DELIMITER*/
static void tokenize_input(void) {
  char* c = input;
  char* s = strstr(c, DELIMITER);
  
  if(s == NULL) { 
    /* no de-limiter pattern found so add entire input indices as one block*/
    int i = 0;
    en_queue(&bq, &i, sizeof(int)); /* start*/
    i = strlen(c);  /* exclude '\0'*/
    en_queue(&bq, &i, sizeof(int)); /* end*/
    return;
  }
  
  int j, k;

  while(s != NULL) {
    j = c - input;
    k = (s+2) - input;  /* include de-limiter pattern in block*/
    
    en_queue(&bq, &j, sizeof(int));  /* start*/
    en_queue(&bq, &k, sizeof(int));  /* end*/
    
    c = s + 2;  /* skip '\n\n' de-limiters for next search*/
    s = strstr(c, DELIMITER);
  }

  j = c - input;
  k = strlen(input);  /* exclude '\0'*/

  /* add final block, if any*/
  if(j != k) {
    en_queue(&bq, &j, sizeof(int));  /* start*/
    en_queue(&bq, &k, sizeof(int));  /* end*/
  }      
}

/* within block remove all internal '\n's*/
static char* remove_new_lines(char* b) {
  char* t = strtok(b, NEW_LINE);  /* find first single '\n' de-limiter in block*/
  char* s;  /* append '\0' to extracted lines*/
  char* o = NULL;  /* concatenate all lines, separated with spaces*/
  
  if(t != NULL) { /* initial line*/
    s = strcat(t, NULL_CHAR);
    o = strdup(s);      
  } 
    
  while(t != NULL) {
    t = strtok(NULL, NEW_LINE); /* find next de-limited line*/
    
    if(t != NULL) {
      s = strcat(t, NULL_CHAR);  /* append '\0'*/
      void* tmp = realloc(o, strlen(o) + strlen(s) + 1);  /* memory leak? (not freed)*/
      if(tmp != NULL) { /* concatenate with ' '*/
         o = tmp; 
        strcat(o, SPACE); /* add space*/
        strcat(o, s); /* add line*/
      }
    }
  }
  
  return o; /* block with all internal new lines now joined up with spaces*/
}

static int get_block_size(void) {
  /* block indices always in pairs (start, end)*/
  int* sb = (int*)de_queue(&bq); /* start of block*/
  int* eb = (int*)de_queue(&bq); /* end of block*/
  start = *sb;  /* need to keep start for get_block function*/
  int l = (*eb - start);  /* block length*/

  free(sb);
  free(eb);
  
  return l;
}

/*! "side effect" of malloc, needs to be refactored*/
static char* get_block(char* b, int l) {
  strncpy(b, input + start, l); /* get block*/
  b[l] = '\0';  /* string terminator  */
  return b;
}

static void print_block(const char *b) {
  char* w = strtok(b, SPACE);   /* get first word*/
  int i = (w != NULL) ? (int)strlen(w) : 0;

  if(i < SPLIT-1) 
    printf("%s", w); /* first word*/

  while(w != NULL) {
    w = strtok(NULL, SPACE); /* find next word*/
    int l = (w != NULL) ? (int)strlen(w) : 0;
    
    if(i + l > SPLIT-1) { /* if we can't fit word on this line, start a new one*/
      i = l;  /* reset line length to size of current word*/
      printf(NEW_LINE);
      
    } else {
      printf(SPACE);
      i++;  /* count space*/
      i += l; /* add word length*/
    }
    
    printf("%s", (w != NULL) ? w : "");  /* suppress null printing*/
  }
}

static void append_delimiter(const char* b) {
  if(strstr(b, DELIMITER) != NULL)
    printf(DELIMITER);
  else
    printf(NEW_LINE);    
}

static void print_blocks(void) {
  while(!empty_queue(&bq)) {
    int l = get_block_size();    
    char* b = malloc(l);
    get_block(b, l); 
    print_block(remove_new_lines(strdup(b))); /* make changes to a copy...*/
    append_delimiter(b);  /* ...so we can keep original block for here*/
    free(b);      
  }
}

int main(void) {
  init_bq();
  tokenize_input();
/*  print_blocks();*/
  clean_up();  
  return 0;
}

/* test runs

SPLIT 72

osman@osman-desktop:~/src/algorist/1.1/challenges$ make && ./fmt
gcc -Wall -Wextra -ggdb    -c -o fmt.o fmt.c
fmt.c: In function ‘print_block’:
fmt.c:180: warning: passing argument 1 of ‘strtok’ discards qualifiers from pointer target type
/usr/include/string.h:346: note: expected ‘char * __restrict__’ but argument is of type ‘const char *’
gcc -lm  -o fmt fmt.o ../ds/queue.o ../ds/list.o
Unix fmt 

The unix fmt program reads lines of text, combining and breaking lines
so as to create an output file with lines as close to without exceeding
72 characters long as possible. The rules for combining and breaking
lines are as follows. 

1. A new line may be started anywhere there is a space in the input. If
a new line is started, there will be no trailing blanks at the end of
the previous line or at the beginning of the new line. 

2. A line break in the input may be eliminated in the output, provided
it is not followed by a space or another line break. If a line break is
eliminated, it is replaced by a space. 

osman@osman-desktop:~/src/algorist/1.1/challenges$ 

SPLIT 36

osman@osman-desktop:~/src/algorist/1.1/challenges$ make && ./fmt
gcc -Wall -Wextra -ggdb    -c -o fmt.o fmt.c
fmt.c: In function ‘print_block’:
fmt.c:180: warning: passing argument 1 of ‘strtok’ discards qualifiers from pointer target type
/usr/include/string.h:346: note: expected ‘char * __restrict__’ but argument is of type ‘const char *’
gcc -lm  -o fmt fmt.o ../ds/queue.o ../ds/list.o
Unix fmt 

The unix fmt program reads lines of
text, combining and breaking lines
so as to create an output file with
lines as close to without exceeding
72 characters long as possible. The
rules for combining and breaking
lines are as follows. 

1. A new line may be started
anywhere there is a space in the
input. If a new line is started,
there will be no trailing blanks at
the end of the previous line or at
the beginning of the new line. 

2. A line break in the input may be
eliminated in the output, provided
it is not followed by a space or
another line break. If a line break
is eliminated, it is replaced by a
space. 

osman@osman-desktop:~/src/algorist/1.1/challenges$ 
*/

