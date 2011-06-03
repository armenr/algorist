/*see README for original credits */

#include<stdio.h>
#include"back-track-funcs.h"
#include"../ds/graph1.h"

void paths_process_solution(const back_track_t* b, int k, void* input) {
  int i;

  printf("{ ");
  for(i = 1; i <= k; i++)
    printf("%d ", b->solution[i]);
  printf(" }\n");
}

bool paths_is_a_solution(const back_track_t* b, int k, void* input) {
  int n = ((path_t*)input)->v;
	return b->solution[k] == n;
}

void paths_make_move(back_track_t* b, int k, void* input) {
}

void paths_unmake_move(back_track_t* b, int k, void* input) {
}

/*	What are possible elements of the next slot in the path
*/

void paths_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {

	bool in_sol[b->sol_sz];	
  int i;
  
	for(i = 1; i < b->sol_sz; i++) 
	  in_sol[i] = false;

	for(i = 1; i < k; i++) 
	  in_sol[b->solution[i]] = true;
	  
  if(k == 1) {
/*printf("init k = 1\n");*/
    c[0] = 1;
    *ncandidates = 1;

  } else	{
    *ncandidates = 0;
    int last = b->solution[k-1];
    
    const graph g = ((path_t*)input)->g;
    const vertex* v = find_vertex(&g, last);
    const edge_node* p = v->edges;

    /*build candidate list from adjacent vertices in list*/
    while(p != NULL) {
/*printf("%d %d %d\n", last, p->y, *ncandidates);    */
      if(!in_sol[p->y]) {
/*        c[*ncandidates] = p->y;*/
        *(ncandidates)++;
      }

      p = p->next;
    }
  }
}

void perm_process_solution(const back_track_t* b, int k, void* input) {
	int i;

	for(i = 1; i <= k; i++) 
	  printf("%d ", b->solution[i]);
	printf("\n");
}

bool perm_is_a_solution(const back_track_t* b, int k, void* input) {
	return k == *(int*)input;
}

void perm_make_move(back_track_t* b, int k, void* input) {
}

void perm_unmake_move(back_track_t* b, int k, void* input){
}

/*	What are possible elements of the next slot in the permutation?  */
void perm_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {
	
	bool in_perm[b->sol_sz];		/* what is now in the permutation? */
  int i;
  
  /*create bitset for existing permutation members*/
	for(i = 1; i < b->sol_sz; i++) 
	  in_perm[i] = false;

	for(i = 1; i < k; i++) 
	  in_perm[b->solution[i]] = true;

  int n = *(int*)input;
	*ncandidates = 0;

  /*build list of candidates for next position*/
	for(i = 1; i <= n; i++) 
		if(!in_perm[i]) {
			c[*ncandidates] = i;
			(*ncandidates)++;
		}
}

void subset_process_solution(const back_track_t* b, int k, void* input) {
	int i;

	printf("{");
	for(i = 1; i <= k; i++)
		if(b->solution[i]) 
		  printf(" %d", i);

	printf(" }\n");
}

bool subset_is_a_solution(const back_track_t* b, int k, void* input) {
	return k == *(int*)input;
}

void subset_make_move(back_track_t* b, int k, void* input) {
}

void subset_unmake_move(back_track_t* b, int k, void* input){
}

/*	What are possible elements of the next slot in the permutation?  */
void subset_construct_candidates(const back_track_t* b, int k, int* c, 
  int* ncandidates, void* input) {
	
	c[0] = true; 
	c[1] = false; 
  *ncandidates = 2; /* next position candidate count */
}

