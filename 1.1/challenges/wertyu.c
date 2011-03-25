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
3.8.1 WERTYU
PC/UVa IDs: 110301/10082, Popularity: A, Success rate: high Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

O S, GOMR YPFSU/

Sample Output

I AM FINE TODAY.

*/

#define KEYS 50

#include"../ds/hashtbl.h"
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

static HASHTBL *hashtbl;

static char* input = "O S, GOMR YPFSU//";

bool createKeyMaps(void) {

	if(!(hashtbl = hashtbl_create(KEYS, NULL))) {
		return false;
	}

	hashtbl_insert(hashtbl, " ", " ");
	hashtbl_insert(hashtbl, "0", "9");
	hashtbl_insert(hashtbl, "1", "`");
	hashtbl_insert(hashtbl, "2", "1");
	hashtbl_insert(hashtbl, "3", "2");
	hashtbl_insert(hashtbl, "4", "3");
	hashtbl_insert(hashtbl, "5", "4");
	hashtbl_insert(hashtbl, "6", "5");
	hashtbl_insert(hashtbl, "7", "6");
	hashtbl_insert(hashtbl, "8", "7");
	hashtbl_insert(hashtbl, "9", "8");
	hashtbl_insert(hashtbl, "0", "9");
	hashtbl_insert(hashtbl, "A", "A");
	hashtbl_insert(hashtbl, "B", "V");
	hashtbl_insert(hashtbl, "C", "X");
	hashtbl_insert(hashtbl, "D", "S");
	hashtbl_insert(hashtbl, "E", "W");
	hashtbl_insert(hashtbl, "F", "D");
	hashtbl_insert(hashtbl, "G", "F");
	hashtbl_insert(hashtbl, "H", "G");
	hashtbl_insert(hashtbl, "I", "U");
	hashtbl_insert(hashtbl, "J", "H");
	hashtbl_insert(hashtbl, "K", "J");
	hashtbl_insert(hashtbl, "L", "K");
	hashtbl_insert(hashtbl, "M", "N");
	hashtbl_insert(hashtbl, "N", "B");
	hashtbl_insert(hashtbl, "O", "I");
	hashtbl_insert(hashtbl, "P", "O");
	hashtbl_insert(hashtbl, "Q", "Q");
	hashtbl_insert(hashtbl, "R", "E");
	hashtbl_insert(hashtbl, "S", "A");
	hashtbl_insert(hashtbl, "T", "R");
	hashtbl_insert(hashtbl, "U", "Y");
	hashtbl_insert(hashtbl, "V", "C");
	hashtbl_insert(hashtbl, "W", "Q");
	hashtbl_insert(hashtbl, "X", "Z");
	hashtbl_insert(hashtbl, "Y", "T");
	hashtbl_insert(hashtbl, "Z", "Z");
	hashtbl_insert(hashtbl, "`", "`");
	hashtbl_insert(hashtbl, "-", "0");
	hashtbl_insert(hashtbl, "=", "-");
	hashtbl_insert(hashtbl, "[", "P");
	hashtbl_insert(hashtbl, "]", "[");
	hashtbl_insert(hashtbl, ";", "L");
	hashtbl_insert(hashtbl, "'", ";");
	hashtbl_insert(hashtbl, ",", "M");
	hashtbl_insert(hashtbl, ".", ",");
	hashtbl_insert(hashtbl, "/", ".");

  return true;
}

static void cleanUp(void) {
	hashtbl_destroy(hashtbl);
}

static void printCorrectOutput(void) {
  int i; 
  for(i = 0; i < (int)strlen(input)-1; i++) 
    printf("%c", input[i]); /*original*/
  printf("\n");
      
  char s[2];  /*hash function maps on key strings*/      
  for(i = 0; i < (int)strlen(input)-1; i++) {
    s[0] = input[i]; s[1] = '\0';
    printf("%s", (char*)hashtbl_get(hashtbl, s));
  }
  printf("\n");
}

int main(void) {

  if(!createKeyMaps()) 
    return -1;

  printCorrectOutput();
  cleanUp();    
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./wertyu 
O S, GOMR YPFSU/
I AM FINE TODAY.
*/

