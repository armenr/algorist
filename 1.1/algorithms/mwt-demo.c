/*see README for original credits */

#include "mwt.h"
#include <stdio.h>

int main(void){
	point in[MAXPOLY];		/* input points */
	polygon hull;			/* convex hull */
	int n;				/* number of points */
	int i;				/* counter */

  printf("enter # points: ");
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
    printf("enter point #%d (x, y): ", i);
		scanf("%lf %lf", &in[i][X], &in[i][Y]);
	}

	convex_hull(in, n, &hull);
	print_polygon(&hull);
	return 0;
}



