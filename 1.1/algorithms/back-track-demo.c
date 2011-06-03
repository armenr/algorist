/*see README for original credits */

#include<stdbool.h>
#include<stdio.h>
#include"back-track.h"
#include"back-track-funcs.h"
#include"../ds/graph1.h"
#include"graph-print.h"

static void paths_demo(graph* g) {
  init_graph(g, false);

  /*should check for return values of insert vertex*/
  insert_vertex(g); /*0 - sentinel*/
  insert_vertex(g); /*1*/
  insert_vertex(g); /*2*/
  insert_vertex(g); /*3*/
  insert_vertex(g); /*4*/
  insert_vertex(g); /*5*/
  insert_vertex(g); /*6*/
  
  insert_edge(g, 1, 2, 0);
  insert_edge(g, 1, 3, 0);
  insert_edge(g, 1, 4, 0);
  insert_edge(g, 1, 5, 0);
  insert_edge(g, 2, 6, 0);
  insert_edge(g, 3, 6, 0);
  insert_edge(g, 4, 6, 0);
  insert_edge(g, 5, 6, 0);
  insert_edge(g, 3, 4, 0);
}

int main(void) {
  back_track_t b;

  printf("\n============\n");
  printf("Permutations");
  printf("\n============\n\n");

  b.process_solution = perm_process_solution;
  b.is_a_solution = perm_is_a_solution;
  b.construct_candidates = perm_construct_candidates;
  b.make_move = perm_make_move;
  b.unmake_move = perm_unmake_move;

  int i = 3;
  init_back_track(&b, i+1); 
	back_track(&b, 0, i, &i); 
  clear_back_track(&b);
  
  printf("\n=======\n");
  printf("Subsets");
  printf("\n=======\n\n");

  b.process_solution = subset_process_solution;
  b.is_a_solution = subset_is_a_solution;
  b.construct_candidates = subset_construct_candidates;
  b.make_move = subset_make_move;
  b.unmake_move = subset_unmake_move;

  i = 3;
  init_back_track(&b, i+1); 
	back_track(&b, 0, 2, &i);
  clear_back_track(&b);
  
  printf("\n=====\n");
  printf("Paths");
  printf("\n=====\n\n");

  b.process_solution = paths_process_solution;
  b.is_a_solution = paths_is_a_solution;
  b.construct_candidates = paths_construct_candidates;
  b.make_move = paths_make_move;
  b.unmake_move = paths_unmake_move;
  
  path_t p;
  paths_demo(&(p.g));
  print_graph(&(p.g), print_item);

  p.v = 3;
  init_back_track(&b, p.v); 
	back_track(&b, 0, p.v, &p);

  clear_back_track(&b);
  clear_graph(&(p.g));
	return 0;
}

/*
see fig 7.1 pp 236 "The Algorithm Design Manual" by Steve S. Skiena
*/
