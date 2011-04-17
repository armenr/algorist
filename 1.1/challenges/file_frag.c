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
3.8.6 File Fragmentation
PC/UVa IDs: 110306/10132, Popularity: C, Success rate: average Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

011
0111
01110
111
0111
10111

Sample Output

01110111
*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char* fragments[] = {"011", "0111", "01110", "111", "0111", "10111"};
#define FRAG_SIZE (int)(sizeof(fragments) / sizeof(fragments[0]))

#define PAIRS 4 /* no of unique pairs to match*/
static char* candidates[2 * PAIRS]; /*each pair can be matched two ways*/

static int compareFrags(const char** xf, const char** yf) {
  int x = strlen(*xf), y = strlen(*yf);

	if(x < y) 
	  return -1;
	else if(x > y) 
	  return 1;

	return 0;
}

static int compareCandidates(const char* xf[], const char* yf[]) {
  int i, lx = (int)(sizeof(*xf)/ sizeof((*xf)[0])), 
    ly = (int)(sizeof(*yf)/ sizeof((*yf)[0]));

    for(i = 0 ; lx > ly ? lx : ly; i++)
	    if((*xf)[i] < (*yf)[i]) 
	      return -1;
	    else if((*xf)[i] > (*yf)[i]) 
	      return 1;
    
	return 0;
}

static void freeCandidates(void) {
  int i;

  for(i = 0; i < 2*PAIRS; i++)
    if(candidates[i] != NULL)
      free(candidates[i]);
}

static void sortCandidates(void) {
  qsort(&candidates, 2*PAIRS, sizeof(const char**), compareCandidates);
}

static void sortFragments(void) {
  qsort(&fragments, FRAG_SIZE, sizeof(const char**), compareFrags);
}

static void printFragments(void) {
  int i;
  for(i = 0; i < FRAG_SIZE; i++)
    printf("%s\n", fragments[i]);
}

  
static void findCandidates(void) {
  int i, j = strlen(fragments[0]), k = strlen(fragments[FRAG_SIZE-1]), l = j+k;
  int m, n, o, p = 0;

  for(i = j, m = 0, n = o = FRAG_SIZE-1; i <= l/2; i++) {
    /*pair up (m, n) strings*/
    for( ; m < (int)FRAG_SIZE && (int)strlen(fragments[m]) == i; m++) 
      for(n = o ; n >= 0 && (int)strlen(fragments[n]) == l-i; n--)
      
        /*for pairs of identical lengths, ignore matches and duplicates*/ 
        if(!(m == n || fragments[m] == fragments[m+1] || 
          fragments[n] == fragments[n-1] || p > PAIRS-1)) {
          
            candidates[2*p] = malloc(strlen(fragments[m]) + 
              strlen(fragments[n]) + 2);
            candidates[2*p +1] = malloc(strlen(fragments[m]) + 
              strlen(fragments[n]) + 2);
              
            /*create candidate combinations*/
            strcat(candidates[2*p], fragments[m]);
            strcat(candidates[2*p], fragments[n]);
            strcat(candidates[2*p +1], fragments[n]);
            strcat(candidates[2*p +1], fragments[m]);
/*            printf("%s %s\n", candidates[2*p], candidates[2*p +1]);*/
            p++; /* quit when we have alloted pairs to find match */
          }
    o = n; /*shorten seek for next time*/
  }
}

static void printMatch(void) {
  int i;
  for(i = 0; i < 2*PAIRS -1; i++)
    if(!strcmp(candidates[i], candidates[i+1])) {
      printf("original file found is %s\n", candidates[i]);
      break;
    }
}

int main(void) {
  sortFragments();
  printFragments();
  findCandidates();
  sortCandidates();
  printMatch();
  freeCandidates();
  return 0;
}

/* test runs
osman@osman-vbox-l32:~/src/challenges$ ./file_frag 
011
111
0111
0111
01110
10111
original file found is 01110111
*/

