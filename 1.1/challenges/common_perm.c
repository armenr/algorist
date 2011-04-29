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
3.8.3 Common Permutation
PC/UVa IDs: 110303/10252, Popularity: A, Success rate: average Level: 1

Given two strings a and b, print the longest string x of letters such that 
there is a permutation of x that is a subsequence of a and there is a 
permutation of x that is a subsequence of b.

Input

The input file contains several cases, each case consisting of two consecutive
lines. This means that lines 1 and 2 are a test case, lines 3 and 4 are another 
test case, and so on.
 
Each line contains one string of lowercase characters, with first line of a pair
denoting a and the second denoting b. Each string consists of at most 1,000 
characters.

Output

For each set of input, output a line containing x. If several x satisfy the 
criteria above, choose the first one in alphabetical order.

Sample Input

pretty
women
walking
down
the
street

Sample Output

e
nw
et

*/

#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define ALPHABET 26 

static char* s[] = {"pretty", "women", "walking", "down", "the", "street"};
#define LENGTH (int)(sizeof(s) / sizeof(s[0])) 

static bool found[ALPHABET]; /*bitset from a to z*/

static void initFound(void) {
  int i;
  for(i = 0; i < ALPHABET; i++)
    found[i] = false;
}

static void printFound(void) {
  int i;
  for(i = 0; i < ALPHABET; i++)
    if(found[i])
      printf("%c", 'a' + i);
  printf("\n");
}

/*add case handling to make more robust, assumes strings are all lowercase*/
static void findSub(char *substr, char *str) {
  int i;
  for(i = 0; i < (int)(strlen(substr)); i++) {
    char c = substr[i];
    if(strchr(str, c) != (char*)0)
      found[c - 'a'] = true;
  }
}

static void compareStrings(char *str1, char *str2) {
  initFound();
  printf("%s %s\n", str1, str2);
  
  int l1 = (int)strlen(str1), l2 = (int)strlen(str2);
  if(l1 < l2) 
    findSub(str1, str2);
  else 
    findSub(str2, str1);
  
  printFound();
}

int main(void) {
  int i;
  for(i = 0; i < LENGTH; i+=2)
    compareStrings(s[i], s[i+1]);
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./common_perm 
pretty women
e
walking down
nw
the street
et
*/

