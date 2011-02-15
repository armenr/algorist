/*see README for original credits */

#include "bool.h"
#include "editdistance.h"
#include <stdio.h>
#include <string.h>

int string_compare(char *s, char *t) {
	int i, j ,k;		
	int opt[3];		/* cost of the three options */

	for(i = 0; i < MAXLEN; i++) {
		row_init(i); column_init(i);	
	}

	for(i = 1; i < (int) strlen(s); i++)
		for(j = 1; j < (int)strlen(t); j++) {

			opt[MATCH] = m[i-1][j-1].cost + match(s[i], t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);

			m[i][j].cost = opt[MATCH]; m[i][j].parent = MATCH;

			for(k=INSERT; k<=DELETE; k++)
				if(opt[k] < m[i][j].cost) {
					m[i][j].cost = opt[k]; m[i][j].parent = k;
				}
		}

	goal_cell(s, t, &i, &j);
	return m[i][j].cost;
} 

void reconstruct_path(char *s, char *t, int i, int j) {

	if(m[i][j].parent == -1) return;

	if(m[i][j].parent == MATCH) {
		reconstruct_path(s, t, i-1, j-1);	match_out(s, t, i, j);
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
	int x, y;

	x = strlen(s); y = strlen(t);

	printf("   ");
	for(i = 0; i < y; i++)
		printf("  %c", t[i]);
	printf("\n");

	for(i = 0; i < x; i++) {
		printf("%c: ", s[i]);

		for(j = 0; j < y; j++) 
			if(costQ == TRUE)
				printf(" %2d", m[i][j].cost);
			else
				printf(" %2d", m[i][j].parent);

		printf("\n");
	}
}

