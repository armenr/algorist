/*see README for original credits */

#define	DIMENSION	3

#include <math.h>

typedef int point[DIMENSION];

double distance(point a, point b) {
	int i;
	double d=0.0;

	for(i = 0; i < DIMENSION; i++)
		d = d + (a[i]-b[i]) * (a[i]-b[i]);

	return sqrt(d);
}

/*main(){*/
/*	point a={6,2,3};*/
/*	point b={6,3,4};*/
/*	double distance();*/

/*	printf("distance = %f\n",distance(a,b));*/
/*}*/


