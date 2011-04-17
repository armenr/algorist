/*see README for original credits */

#include "triangulate.h"
#include <stdio.h>

int main(void){
	polygon p;			/* input polygon */
	int i;				/* counter */

  printf("enter # vertices: ");
	scanf("%d", &p.n);
	for(i = 0; i < p.n; i++) {
	  printf("enter (x,y) for vertex %d: ", i+1);
		scanf("%lf %lf", &p.p[i][X], &p.p[i][Y]);
	}

	printf(" area via triangulation = %f\n", area_triangulation(&p));
	printf(" area slick = %f\n", area(&p));
  return 0;
}


