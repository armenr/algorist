/*see README for original credits */

#include "editbrute.h"
#include <stdio.h>
#include <string.h>

cell m[MAXLEN][MAXLEN];		/* dynamic programming table */

int string_compare(const char *s, const char *t, int i, int j) {
	int k;			
	int opt[3];		/* cost of the three options */
	int lowest_cost;	

	if(i == 0) return(j * indel(' '));
	if(j == 0) return(i * indel(' '));

	opt[MATCH] = string_compare(s, t, i-1, j-1) + match(s[i], t[j]);
	opt[INSERT] = string_compare(s, t, i, j-1) + indel(t[j]);
	opt[DELETE] = string_compare(s, t, i-1, j) + indel(s[i]);

	lowest_cost = opt[MATCH];
	
	for(k = INSERT; k <= DELETE; k++)
		if(opt[k] < lowest_cost) lowest_cost = opt[k];

	m[i][j].cost = lowest_cost;	/* REMOVE FROM PRINTED VERSION */

	return lowest_cost;
} 

void reconstruct_path(char *s, char *t, int i, int j) {
	if(m[i][j].parent == -1) return;
  if(i < 0 || j < 0) return;
  
	if(m[i][j].parent == MATCH) {
		reconstruct_path(s, t, i-1, j-1); match_out(s, t, i, j);
		return;
	}
	
  if(m[i][j].parent == INSERT) {
    reconstruct_path(s, t, i, j-1); insert_out(t, j);
    return;
  }

  if(m[i][j].parent == DELETE) {
    reconstruct_path(s, t, i-1, j); delete_out(s, i);
    return;
  }
}

void print_matrix(const char *s, const char *t, bool costQ) {
	int i, j;			
	int x, y;			/* string lengths */

	x = strlen(s); y = strlen(t);

	printf("   ");
	for(i = 0; i < y; i++)
		printf("  %c", t[i]);
	printf("\n");

	for(i = 0; i < x; i++) {
		printf("%c: ", s[i]);
		
		for(j = 0; j < y; j++) {
			if(costQ == TRUE)
				printf(" %2d", m[i][j].cost);
			else
				printf(" %2d", m[i][j].parent);

		}
		printf("\n");
	}
}

