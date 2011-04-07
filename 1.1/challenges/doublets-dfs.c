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

#include"../algorithms/bfs-dfs.h"
#include"../algorithms/edit-string.h"
#include"../ds/graph.h"
#include"../ds/hashtbl.h"
#include"../ds/queue.h"
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
static int target_vertex = -1;  // target vertex for path finding 

void process_vertex_early(int v) {
	time++;
	entry_time[v] = time;
	printf("entered vertex %d at time %d\n", v, entry_time[v]);
}

void process_vertex_late(int v) {
	time++;
	exit_time[v] = time;
  printf("exit vertex %d at time %d\n", v, exit_time[v]);
}

void process_edge(int x, int y) {
	int class;		/* edge class */

	class = edge_classification(x, y);

	if(class == BACK) 
	  printf("back edge (%d, %d)\n", x, y);
	else if(class == TREE) 
	  printf("tree edge (%d,%d)\n", x, y);
	else if(class == FORWARD) 
	  printf("forward edge (%d,%d)\n", x, y);
	else if(class == CROSS) 
	  printf("cross edge (%d,%d)\n", x, y);
	else 
	  printf("edge (%d,%d)\n not in valid class=%d", x, y, class);
}

static void print_item(const char* item) {
  printf("%s ", item);
}

static void print_dfs_item(const graph* g, int i) {
  printf("%s ", (char*)g->vertices[i].item);
}

static void init_graph(graph* g, const char* r) {
  initialize_graph(g, true);  // directed graph 
  insert_vertex(g, 0, r, strlen(r)+1);
	hashtbl_insert(found, r, r);          
}

void init_found(void) {
	found = hashtbl_create(DICT_SIZE, NULL);
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
        free(t);
        target_vertex = g.nvertices-1;
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

  // to save space we can delete processed vertices, so the path we find later
  // on just contains the link from root to target
  if(!success)
    delete_vertex(&g, v);
    
  return success;
}

static void clean_up(void) {
  clear_graph(&g);
	hashtbl_destroy(found);
}

static void print_target(void) {
  printf("\n");
	print_graph(&g, print_item);  
  initialize_search(&g);
  dfs(&g, 0);
  find_path(&g, 0, target_vertex, parent, print_dfs_item);
}

static void find_doublets(void) {
  int i;

  printf("\n==============================\n\n");    

  for(i = 0; i < PAIRS_SIZE; i++) {
    char* root = pairs[i][0];
    char* target = pairs[i][1];
    
    init_found();
    init_graph(&g, root);   
    
    printf("%s to %s: \n", root, target);
    
    bool success = find_target(0, target);
    print_target();  
        
  	if(!success)
  	  printf("\nno solution");
  	  
    printf("\n\n==============================\n\n");    
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

