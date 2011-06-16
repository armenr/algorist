/*see README for original credits */

#include <stdio.h>
#include "matrix.h"

void initialize_matrix(matrix *m) {
	int i,j;			/* counters */

	for(i = 1; i <= m->rows; i++)
		for(j = 1; j <= m->columns; j++)
			m->m[i][j] = 0;
}

void read_matrix(matrix *m) {
	int i,j;			/* counters */

  printf("enter #rows #cols: ");
	scanf("%d %d",&(m->rows),&(m->columns));

	for(i = 1; i <= m->rows; i++) 
		for(j = 1; j <= m->columns; j++) {
      printf("enter value: ");
			scanf("%d",&m->m[i][j]);
		}
}

void print_matrix(const matrix *g) {
	int i,j;			/* counters */

	for(i = 1; i <= g->rows; i++) {
		for(j = 1; j <= g->columns; j++)
			printf(" %d",g->m[i][j]);
		printf("\n");
	}
	printf("\n");
}

void multiply(const matrix *a, const matrix *b, matrix *c) {
	int i,j,k;			/* dimension counters */

	if(a->columns != b->rows) {
		printf("Error: bounds dont match!\n");
		return;
	}

	c->rows = a->rows;
	c->columns = b->columns;

	for(i = 1; i <= a->rows; i++)
		for(j = 1; j <= b->columns; j++) {
			c->m[i][j] = 0;
    	for(k = 1; k <= b->rows; k++)
	   		c->m[i][j] += a->m[i][k] * b->m[k][j];
		}
}
