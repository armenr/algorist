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
3.8.7 Doublets
PC/UVa IDs: 110307/10150, Popularity: C, Success rate: average Level: 3

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input 

booster 
rooster 
roaster 
coasted 
roasted 
coastal 
postal 

booster roasted
coastal postal

Sample Output

booster
rooster
roaster
roasted

No solution.
*/

#include"../ds/graph.h"
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char* dictionary[] = {"booster", "rooster", "roaster", "coasted", 
  "roasted", "coastal", "postal"};
#define DICT_SIZE (int)(sizeof(dictionary) / sizeof(dictionary[0]))

static char* pairs[][2] = {{"booster", " roasted"}, {"coastal", "postal"}};
#define PAIRS_SIZE (int)(sizeof(pairs) / sizeof(pairs[0]))

static	graph g;

static int compareWords(const char* xf[], const char* yf[]) {
  int i, lx = (int)(sizeof(*xf)/ sizeof((*xf)[0])), 
    ly = (int)(sizeof(*yf)/ sizeof((*yf)[0]));

    for(i = 0 ; lx > ly ? lx : ly; i++)
	    if((*xf)[i] < (*yf)[i]) 
	      return -1;
	    else if((*xf)[i] > (*yf)[i]) 
	      return 1;
    
	return 0;
}

static void sortDictionary(void) {
  qsort(&dictionary, DICT_SIZE, sizeof(const char**), compareWords);
}

static void printDictionary(void) {
  int i;
  for(i = 0; i < DICT_SIZE; i++)
    printf("%s\n", dictionary[i]);
}

static void init_graph(graph* g) {
  char c;
  initialize_graph(g, false);
  
/*  c = 'a';*/
/*  insert_vertex(g, 1, &c, sizeof(char));*/
/*  c = 'b';*/
/*  insert_vertex(g, 2, &c, sizeof(char));*/
/*  insert_edge(g, 1, 2, false, 0);*/
/*  c = 'e';*/
/*  insert_vertex(g, 5, &c, sizeof(char));*/
/*  insert_edge(g,1, 5, false, 0);*/
/*  c = 'f';*/
/*  insert_vertex(g, 6, &c, sizeof(char));*/
/*  insert_edge(g,1, 6, false, 0);*/
/*  insert_edge(g,2, 5, false, 0);*/
/*  c = 'c';*/
/*  insert_vertex(g, 3, &c, sizeof(char));*/
/*  insert_edge(g,2, 3, false, 0);*/
/*  c = 'd';*/
/*  insert_vertex(g, 4, &c, sizeof(char));*/
/*  insert_edge(g,5, 4, false, 0);*/
/*  insert_edge(g,3, 4, false, 0);*/
}

int main(void) {
  init_graph(&g);    
  sortDictionary();
  printDictionary();
	clear_graph(&g);
  return 0;
}

for each pair (pi where 0 <= i < PAIR_SIZE, pi=(p1, p2))

  for each doublet (di where 0 <= i < DICT_SIZE) of pi(p1):
  
    does di == pi(p2)?
    
      yes: 
        report match
        go to next pair        
        
      no:
        add vertex (v) for di

                
/* test runs
*/

