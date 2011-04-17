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

#include"../algorithms/edit-string.h"
#include"../ds/graph.h"
#include"../ds/hashtbl.h"
#include"../ds/stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char* dictionary[] = {"booster", "rooster", "roaster", "coasted", 
  "roasted", "coastal", "postal"};
#define DICT_SIZE (int)(sizeof(dictionary) / sizeof(dictionary[0]))

static char* pairs[][2] = {{"booster", "roasted"}, {"coastal", "postal"}};
#define PAIRS_SIZE (int)(sizeof(pairs) / sizeof(pairs[0]))

static HASHTBL *found;  // discovered doublets
static graph g; // only add unique doublets to graph, by checking first in found
static stack solution;		/* hold path from root to target in a stack */

static void print_item(const char* item) {
  printf("%s ", item);
}

static void init_graph(graph* g, const char* r) {
  initialize_graph(g, true);  // directed graph 
  insert_vertex(g, 0, r, strlen(r)+1);
	hashtbl_insert(found, r, r);          
}

void init_found(void) {
	found = hashtbl_create(DICT_SIZE, NULL);
}

void init_solution(void) {
	solution = init_stack();
}

static void add_candidate(const char* candidate, int v) {
  insert_vertex(&g, g.nvertices, candidate, (int)strlen(candidate)+1);      
  int n = g.nvertices-1;
  insert_edge(&g, v, n, 0, true);
	hashtbl_insert(found, candidate, &n);          
}

static bool find_target(int v, const char* m) {
	char* s, *r;		
  int i;
  bool success = false;
  
  
  // s used in edit string to find doublet
  r = (char*)g.vertices[v].item; // root item
  s = malloc((int)strlen(r)+2);
  // append an initial space for edit string function
  s[0] = ' ';
  strcpy(&s[1], r);

  for(i = 0; i < DICT_SIZE; i++) {

    char* candidate = dictionary[i];
    char* t = malloc((int)strlen(candidate)+2);
    
	  t[0] = ' '; 
    strcpy(&t[1], candidate);
    
    if(string_compare(s, t) == 1) { // doublet

      if(strcmp(candidate, m)) { // unmatched
        if(hashtbl_get(found, candidate) == NULL)  // not already added
          add_candidate(candidate, v);
          
      } else {
        add_candidate(candidate, v);
		    push_stack(&solution, candidate, (int)strlen(candidate)+1);
        free(t);
        success = true;
        break;
      }
    } 
         
    free(t);
  }

  free(s);
  
  // iterate through graph edges to find target
  edgenode* p = g.vertices[v].edges;
  
  while(p != NULL && !success) 
  	if(!(success = find_target(p->y, m)))
  	  p = p->next;

  if(success)  // add item to solution 
		push_stack(&solution, g.vertices[v].item, 
		  (int)strlen(g.vertices[v].item)+1);

  // to save space we can delete processed vertices, so the path we find later
  // on just contains the link from root to target
  else 
    delete_vertex(&g, v);
    
  return success;
}

static void clean_up(void) {
  clear_graph(&g);
	clear_stack(&solution);    
	hashtbl_destroy(found);
}

static void find_doublets(void) {
  int i;

  printf("\n==============================\n\n");    

  for(i = 0; i < PAIRS_SIZE; i++) {
    char* root = pairs[i][0];
    char* target = pairs[i][1];
    
    init_found();
    init_graph(&g, root);   
    init_solution();
        
    printf("%s to %s: \n", root, target);
    
  	if(find_target(0, target)) 
			print_stack(solution, print_item);
  	else
  	  printf("no solution\n");
  	    	  
    printf("\n==============================\n\n");    
  	clean_up();
  }
}

int main(void) {
  find_doublets();
  return 0;
}

/* test runs
osman@osman-desktop:~/src/algorist/1.1/challenges$ ./doublets-dfs 

==============================

booster to roasted: 

node: 0 booster edges: 1 
node: 1 rooster edges: 2 
node: 2 roaster edges: 3 
node: 3 roasted edges: 
entered vertex 0 at time 2
tree edge (0,1)
entered vertex 1 at time 4
tree edge (1,2)
entered vertex 2 at time 6
tree edge (2,3)
entered vertex 3 at time 8
exit vertex 3 at time 9
exit vertex 2 at time 11
exit vertex 1 at time 13
exit vertex 0 at time 15

booster rooster roaster roasted 

==============================

coastal to postal: 

entered vertex 0 at time 2
exit vertex 0 at time 3

(null) (null) (null) (null) 
no solution

==============================

*/

