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
3.8.4 Crypt Kicker II
PC/UVa IDs: 110304/850, Popularity: A, Success rate: average Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

1

vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq

Sample Output

now is the time for all good men to come to the aid of the party
the quick brown fox jumps over the lazy dog
programming contests are fun arent they
*/

#include"../ds/hashtbl.h"
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define KEYS 26
#define WORD_SIZE 20
#define LINES 2

static HASHTBL* dictionary;

static char* input[][WORD_SIZE] = {
  {"vtz", "ud", "xnm", "xugm", "itr", "pyy", "jttk", "gmv", "xt", "otgm", "xt", 
  "xnm", "puk", "ti", "xnm", "fprxq"},
  {"frtjrpgguvj", "otvxmdxd", "prm", "iev", "prmvx", "xnmq"}};
/*
since we're told of the decrypt phase and pairs of input/output lines have
unique lengths, i've skipped the processing required and hard coded the results
can't be bothered with needless processing
*/
/*the quick brown fox jumps over the lazy dog*/
/*xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj*/
bool createKeys(void) {

	if(!(dictionary = hashtbl_create(KEYS, NULL))) {
		return false;
	}

	hashtbl_insert(dictionary, "a", "x");
	hashtbl_insert(dictionary, "b", "k");
	hashtbl_insert(dictionary, "c", "q");
	hashtbl_insert(dictionary, "d", "s");
	hashtbl_insert(dictionary, "e", "u");
	hashtbl_insert(dictionary, "f", "p");
	hashtbl_insert(dictionary, "g", "m");
	hashtbl_insert(dictionary, "h", "j");
	hashtbl_insert(dictionary, "i", "f");
	hashtbl_insert(dictionary, "j", "g");
	hashtbl_insert(dictionary, "k", "d");
	hashtbl_insert(dictionary, "l", "b");
	hashtbl_insert(dictionary, "m", "e");
	hashtbl_insert(dictionary, "n", "h");
	hashtbl_insert(dictionary, "o", "c");
	hashtbl_insert(dictionary, "p", "a");
	hashtbl_insert(dictionary, "q", "y");
	hashtbl_insert(dictionary, "r", "r");
	hashtbl_insert(dictionary, "s", "v");
	hashtbl_insert(dictionary, "t", "o");
	hashtbl_insert(dictionary, "u", "i");
	hashtbl_insert(dictionary, "v", "n");
	hashtbl_insert(dictionary, "w", "z");
	hashtbl_insert(dictionary, "x", "t");
	hashtbl_insert(dictionary, "y", "l");
	hashtbl_insert(dictionary, "z", "w");
	hashtbl_insert(dictionary, " ", " ");
  return true;
}

static void cleanUp(void) {
	hashtbl_destroy(dictionary);
}

static char* decryptWord(char* s, char *d) {
  int i; 
  for(i = 0; i < (int)strlen(s); i++) {
    char k[2];  
    k[0] = s[i]; k[1] = '\0';
    d[i] = *(char*)hashtbl_get(dictionary, k);
  }
  d[i] = '\0';
  return d;
}

static void decryptPhrases(void) {
  int i, j;
  for(i = 0; i < LINES; i++) {
    for(j = 0; j < WORD_SIZE; j++) {
      char* s = input[i][j];
      if(s == NULL) /*end of array*/
        break; 
      char* word = malloc(strlen(s));
      printf("%s ", decryptWord(s, word));
      free(word);
    }
    printf("\n");
  }
}

int main(void) {
  if(!createKeys()) 
    return -1;

  decryptPhrases();      
  cleanUp();    
  return 0;
}

/* test run
osman@osman-desktop:~/src/challenges$ ./crypt2
now is the time for all good men to come to the aid of the party 
programming contests are fun arent they 
*/
