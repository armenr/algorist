/*see README for original credits */

#include<limits.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"edit-string.h"

#define LCS_MAX (INT_MAX / 2)

static int cell_index(int row, int col, int row_sz);
static int indel(char c);

void clear_edit_str(edit_string* e) {
  free(e->m);
}
void init_edit_str(edit_string* e, int row_sz, int col_sz) {
  e->row_sz = row_sz;
  e->col_sz = col_sz;
  e->m = malloc(row_sz * col_sz * sizeof(cell));
}

/*	For normal edit distance computation  */
void goal_cell(const edit_string* e, int* i, int* j) {
	*i = e->row_sz-1;
	*j = e->col_sz-1;
}

void goal_cell_sub(const edit_string* e, int *i, int *j) {
	*i = e->row_sz-1;
	*j = 0;

  int k;
  
	for(k = 1; k < e->col_sz; k++) {
		int p1 = cell_index(*i, k, e->row_sz);
		int p2 = cell_index(*i, *j, e->row_sz);

		if(e->m[p1].cost < e->m[p2].cost) 
		  *j = k;
	}
}

int string_compare(edit_string* e, const char* s, const char* t) {
	int i, j;  /*p is cell position*/

	for(i = 0; i < e->row_sz; i++) 
		e->row_init(e, i); 

	for(i = 0; i < e->col_sz; i++) 
		e->col_init(e, i); 

	for(i = 1; i < e->row_sz; i++)
		for(j = 1; j < e->col_sz; j++) {
    	int opt[3];		/* cost of the three options */

			opt[MATCH] = e->m[cell_index(i-1, j-1, e->row_sz)].cost + 
			  e->match(s[i], t[j]);
			opt[INSERT] = e->m[cell_index(i, j-1, e->row_sz)].cost + indel(t[j]);
			opt[DELETE] = e->m[cell_index(i-1, j, e->row_sz)].cost + indel(s[i]);
  
			int p = cell_index(i, j, e->row_sz);

			e->m[p].cost = opt[MATCH]; 
			e->m[p].parent = MATCH;
			
			int k;
			
			for(k = INSERT; k <= DELETE; k++)
				if(opt[k] < e->m[p].cost) {
					e->m[p].cost = opt[k]; 
					e->m[p].parent = k;
				}
		}

	e->goal_cell(e, &i, &j);
	return e->m[cell_index(i, j, e->row_sz)].cost;
} 

void reconstruct_path(const edit_string* e, const char* s, const char* t, 
  int i, int j) {

  if(i < 0 || j < 0)
    return;
    
	int p = cell_index(i, j, e->row_sz);
	
  switch(e->m[p].parent) {
    case NONE:
      break;

    case MATCH:
      reconstruct_path(e, s, t, i-1, j-1);
      e->match_out(s, t, i, j);
      break;

    case INSERT:
      reconstruct_path(e, s, t, i, j-1);
      e->insert_out(t, j);
      break;

    case DELETE:
      reconstruct_path(e, s, t, i-1, j);
      e->delete_out(s, i);
      break;

    default:
      break;
  }
}

void print_matrix(const edit_string* e, const char* s, const char* t, 
  bool costQ) {
  
	int i, j;

	printf("   ");
	for(i = 0; i < e->col_sz; i++)
		printf("  %c", t[i]);
	printf("\n");

	for(i = 0; i < e->row_sz; i++) {
		printf("%c: ", s[i]);

		for(j = 0; j < e->col_sz; j++) {
			int p = cell_index(i, j, e->row_sz);
			
			if(costQ)
				printf(" %2d", e->m[p].cost);
			else
				printf(" %2d", e->m[p].parent);
		}

		printf("\n");
	}
}

void col_init(edit_string* e, int i)	{ /* what is e->m[i][0]? */
	int p = cell_index(i, 0, e->row_sz);
  e->m[p].cost = i;

	if(i > 0)
		e->m[p].parent = DELETE;
	else {
  	p = cell_index(0, i, e->row_sz);
		e->m[p].parent = NONE;
	}
}

void row_init(edit_string* e, int i) {		/* what is e->m[0][i]? */
	int p = cell_index(0, i, e->row_sz);
  e->m[p].cost = i;

	if(i > 0)
		e->m[p].parent =  INSERT;
	else
		e->m[p].parent = NONE;
}

void row_init_sub(edit_string* e, int i) {
	int p = cell_index(0, i, e->row_sz);
	e->m[p].cost = 0;
	e->m[p].parent = NONE;
}

int match(char c, char d) {
	if(c == d) 
	  return 0;
	
	return 1;
}

int match_lcs(char c, char d) {
	if(c == d) 
	  return 0;

	return LCS_MAX;  /*prevent addition overflow*/
}

void delete_out(const char* s, int i) {
  printf("D");
}

void insert_out(const char* t, int j) {
	printf("I");
}

void match_out(const char* s, const char* t, int i, int j) {
	if(s[i] == t[j]) 
	  printf("M");
	else 
	  printf("S");
}

void match_out_lcs(const char* s, const char* t, int i, int j) {
	if(s[i] == t[j]) 
	  printf("%c", s[i]);
}

void insert_out_lcs(const char* t, int j) {
}

void delete_out_lcs(const char* s, int i) {
}

static int cell_index(int row, int col, int row_sz) {
  return (row * row_sz) + col;
}

static int indel(char c) {
	return 1;
}
