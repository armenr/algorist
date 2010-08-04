/*see README for original credits */

#ifndef MATRIX_H
#define MATRIX_H

#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

#define MAXINT	100007

typedef struct {
  int m[MAXV+1][MAXV+1];    	/* adjacency/weight info */
  int rows;			/* number of rows */
  int columns;			/* number of columns */
} matrix;

void initialize_matrix(matrix *m);
void read_matrix(matrix *m);
void print_matrix(const matrix *g);
void multiply(const matrix *a, const matrix *b, matrix *c);

#endif /* MATRIX_H */
