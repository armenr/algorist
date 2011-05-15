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
2.8.4    Crypt Kicker
PC/UVa IDs: 110204/843, Popularity: B, Success rate: low Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

6
and
dick
jane
puff
spot
yertle
bjvg xsb hxsn xsb qymm xsb rqat xsb pnetfn
xxxx yyy zzzz www yyyy aaa bbbb ccc dddddd

Sample Output

dick and jane and puff and spot and yertle
**** *** **** *** **** *** **** *** ******

a c d e f i j k l n o p r s t u y

x s b
a n d

p n e t f n
y e r t l e

M: a d e l n r t y (mapped)
U: c f i j k o p s u (un-mapped)

b j v g
d 

found one word beginning with 'd'

b j v g
d i c k

M: a c d e i k l n r t y 
U: f j o p s u

h x s n
  a n e

found one word ending 'ane'

h x s n
j a n e

M: a c d e i j k l n r t y 
U: f o p s u

r q a t
      t  

found one word ending with 't'
      
r q a t
s p o t  

M: a c d e i j k l n o p r s t y 
U: f u

q y m m
p

found one word beginning with 'p'

q y m m
p u f f

M: a c d e f i j k l n o p r s t u y 
U: 
*/

#include"../ds/stack.h"
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define ALPHABET 26
#define MAX_WORD 16
#define NOT_FOUND -1
#define UNKNOWN '*'

#define STRCMP(a,R,b) (strcmp(a,b) R 0)

/*dictionary and encrypted words must be no larger than MAX_WORD*/
static char *dictionary[] = {"yertle", "dick", "puff", "jane", "spot", 
  "and"};
#define DICT_SIZE (sizeof(dictionary) / sizeof(dictionary[0]))

static bool processed[DICT_SIZE];  /* mark processed dictionary entries as true */  

static char *encrypted[] = {"bjvg", "xsb", "hxsn", "xsb", "qymm", "xsb", 
  "rqat", "xsb", "pnetfn"};
#define ENC_SIZE (sizeof(encrypted) / sizeof(encrypted[0]))

/*  
note that the line below causes the program to loop infinitely in mapDuplicates
since the previous ran mapUniques maps duplicates to letters when it should do
nothing. so this remains a brittle solution whereby mapUniques needs to find
some unique matches before the rest of the program will work
*/  
/*static char *encrypted[ENC_SIZE] = {"xxxx", "yyy", "zzzz", "www", "yyyy", "aaa", */
/*  "bbbb", "ccc", "dddddd"};*/

static char *original[ENC_SIZE];  /* so we can output correctly */

/* letter mappings, should be hashed: key = decrypted, value = encrypted */
static char decrypt[ALPHABET];

static stack refs = NULL; /* stack to hold references for dictionary entries */

static void copyOriginal(void) {
  int i;
  for(i = 0; i < (int)ENC_SIZE; i++)
    original[i] = encrypted[i];      
}

/* find search pattern for dictionary word to find in encrypted list */
/* return length of pattern string, -1 if no pattern created */
static int createPattern(const char *word, char pattern[]) {
  int i, j, l = strlen(word);
  char d_letter, e_letter;

  /* clear pattern */
  for(i = 0; i < MAX_WORD; i++)    
    pattern[i] = ' ';
    
  j = NOT_FOUND;
  
  /* evaluate pattern of decrypted letters to find in encrypted words */
  for(i = 0; i < l+1; i++) {

    /* look up mappings */
    d_letter = word[i];
    e_letter = decrypt[d_letter - 'a'];
    if(j < MAX_WORD)         
      pattern[++j] = e_letter;
  } 

  /* if the pattern is all wildcards then it isn't valid */
  int w = 0;
  for(i = 0; i < j; i++)
    if(pattern[i] == UNKNOWN)
      w++;

  if(w == j)  /* all unknown */      
    j = NOT_FOUND;
    
  /* return pattern length */
  return j;
}

static void decryptWord(const char *dec, const char *enc, int l) {
  int i;
  /*map all encrypted letters to dictionary letters */
  for(i = 0; i <= l; i++) 
    decrypt[dec[i] - 'a'] = enc[i];
}

static void decodeOriginal(void) {
  int i, j, k;
  char c, d, *word;
  
  for(i = 0; i < (int)ENC_SIZE; i++) {
    word = original[i];
    for(j = 0; j <= (int)strlen(word); j++) {
      c = word[j];
      for(k = 0; k < (int)ALPHABET; k++)
        if(c == decrypt[k]) {
          d = 'a' + k;
          printf("%c", d);
          break;
        }
    }   
    printf(" ");      
  }
  printf("\n");  
}

static bool patternMatch(const char *word, const char pattern[], int sz) {
  int i;
  char c;

  for(i = 0; i< sz; i++) {
    c = pattern[i];
    if(c != UNKNOWN)  /* ignore wildcards */
      if(c != word[i]) 
        return false;
  }
  return true;
}

/* match pattern to a unique word in encrypted, returning position or not found*/
static int findWord(const char pattern[], int sz) {
  int i, found = NOT_FOUND;
  char *word;

  /* find index range of words to match */
  for(i = 0; i < (int)ENC_SIZE; i++)
    if(sz == (int)strlen(encrypted[i]))
      break;
  
  word = encrypted[i];                    

  bool match;
  
  /*keep searching while we have't matched a unique word of the same size and pattern*/
  while((found == NOT_FOUND) && (i < (int)ENC_SIZE) && (sz == (int)strlen(word))) {

    match = patternMatch(word, pattern, sz);        

    /*if there is a match, is the word unique?*/
    if(match) 
      if(sz != (int)strlen(encrypted[i+1]) || STRCMP(word, !=, encrypted[i+1])) 
        found = i;                    
    
    /* if we haven't matched this one or word is duplicate then skip all same 
       words in sorted list */
    if(!match || found == (int)NOT_FOUND)
      for(i++; i < (int)ENC_SIZE; i++)
        if(STRCMP(word, !=, encrypted[i]))
          break;

    /* see if there is another word to pattern match */
    if(i < (int)ENC_SIZE)          
      word = encrypted[i];                    
  }
  
  return found;
}

static void findUniques(const char *words[], stack* s, int sz) {
  /*find all entries with unique lengths and push them on stack*/
  int i, l = strlen(words[0]), count = 0;
  
  for(i = 1; i < sz; i++)    

    if((int)strlen(words[i]) != l) {
      if(count == 0) {
        int j = i-1;
        push_stack(s, &j, sizeof(int));    
      }
      l = strlen(words[i]); count = 0;

    } else
      count++;

  if(count == 0) {
    int j = i-1;
    push_stack(s, &j, sizeof(int));    
  }
}

static void initMappings(void) {
  int i;
  for(i = 0; i < ALPHABET; i++) 
    decrypt[i] = UNKNOWN;
}

static void initProcessed(void) {
  int i;
  for(i = 0; i < (int)DICT_SIZE; i++) 
    processed[i] = false;
}

static void mapDuplicates(void) {
/* we need to avoid infinite loops by flagging any new mappings found after  
    each round */
  int i = 0, l, found;
  char pattern[MAX_WORD], *word;
    
  while(i < (int)DICT_SIZE) {  /* keep looking */
    
    if(!processed[i]) {
      /* create pattern match for searching encrypted, incl pattern length, l */
      word = dictionary[i];
      l = createPattern(word, pattern);     

      if(l != NOT_FOUND) {
        /*pattern match on a unique word in encrypted  */
        found = findWord(pattern, l);

        if(found != NOT_FOUND) {
          decryptWord(word, encrypted[found], strlen(word));
          processed[i] = true;
          i = 0; /* reset so we can reprocess earlier, undecrypted words */
        }     
      } else  /* unmatchable pattern */
        i++;  /* move onto next word to decrypt */
      
    } else  /* word already processed */
      i++;  /* move onto next word to decrypt */
  }
}

static void mapUniques(void) {
  int i, l, r;

  while(refs != NULL) {  
	  int *ip = (int*)pop_stack(&refs);
	  
	  if(ip != NULL) {
      r = *ip;
		  free(ip);	  
		  
      /*find first match in encrypted where lengths match*/
      for(i = 0; i < (int)ENC_SIZE; i++) {
        l = strlen(dictionary[r]);
        if(l == (int)strlen(encrypted[i])) 
          decryptWord(dictionary[r], encrypted[i], l);
      }
      /*mark dictionary entry as processed (true)*/
      processed[r] = true;
	  } 
  }
}

static void printMappings(void) {
  int i;
  
  for(i = 0; i < ALPHABET; i++) 
    printf("%c%c ", i + 'a', decrypt[i]);    
  printf("\n");
}

static void printWords(const char *words[], int sz) {
  int i;
  for(i = 0; i < sz; i++)
    printf("%s ", words[i]);
  printf("\n");
}

/* sort words in order of increasing length */
static void sortWords(char *words[], int sz) {
	int i, j;
	char *w;
	
  /* insertion sort, replace with quicksort for large N */
	for(i = 1; i < sz; i++) {
	  j = i;
	  while((j > 0) && (strlen(words[j]) < strlen(words[j-1]))) {
	    /* swap function */
	    w = words[j]; words[j] = words[j-1]; words[j-1] = w;
		  j--;
	  }
	}
	/* then sort by alphabetical order */
	int k, s = 0, l = strlen(words[0]);
	
	for(k = s+1; k < sz; k++)
	  if((int)strlen(words[k]) != l) {

      /* insertion sort, replace with quicksort for large N */
	    for(i = s+1; i < k; i++) {
	      j = i;
	      while((j > s) && (strcmp(words[j], words[j-1]) < 0)) {
	        /* swap function */
	        w = words[j]; words[j] = words[j-1]; words[j-1] = w;
		      j--;
	      }
	    }
	    
      /* search new length block */	    
      s = k; l = strlen(words[k]);	  
	  }
	
}

int main(void) {
  copyOriginal(); initMappings(); initProcessed();
  sortWords(dictionary, DICT_SIZE); sortWords(encrypted, ENC_SIZE);
  printWords((const char **)dictionary, DICT_SIZE);
  printWords((const char **)encrypted, ENC_SIZE);
  findUniques((const char **)dictionary, &refs, DICT_SIZE);
  mapUniques(); mapDuplicates();
  printMappings(); 
  decodeOriginal();
  clear_stack(&refs);
  return 0;
}

/* test run
osman@osman-desktop:~/src/challenges$ ./crypt 
and dick jane puff spot yertle 
xsb xsb xsb xsb bjvg hxsn qymm rqat pnetfn 
ax b* cv db en fm g* h* ij jh kg lf m* ns oa pq q* re sr tt uy v* w* x* yp z* 
dick and jane and puff and spot and yertle 
*/
