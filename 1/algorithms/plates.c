/*see README for original credits */

#include <stdio.h>
#include <math.h>

/*	how many triangular-lattice layers of radius r balls fit in height h? */
int dense_layers(double w, double h, double r) {
	double gap;			/* distance between layers */

	if ((2*r) > h) return(0);

	gap = 2.0 * r * (sqrt(3)/2.0);
	return( 1 + floor((h-2.0*r)/gap) );
}

int plates_per_row(int row, double w, double r) {
  int plates_per_full_row;        /* number of plates in full/even row */

  plates_per_full_row = floor(w/(2*r));

  if ((row % 2) == 0) return(plates_per_full_row);

  if (((w/(2*r))-plates_per_full_row) >= 0.5)     /* odd row full, too */
    return(plates_per_full_row);
  else
    return(plates_per_full_row - 1);
}

/*	How many radius r plates fit in a hexagonal-lattice packed w*h box?
*/
int dense_plates(double w, double l, double r) {
	int layers;			/* number of layers of balls */

	layers = dense_layers(w,l,r);

	return (ceil(layers/2.0) * plates_per_row(0,w,r) +
		floor(layers/2.0) * plates_per_row(1,w,r) );
}

int grid_plates(double w, double h, double r) {
  int layers;			/* number of layers of balls */

  layers = floor(h/(2*r));
  return (layers * plates_per_row(0,w,r));
}

/*	Hexagonal coordinates start with the center of disk (0,0) at
	geometric point (0,0).  The hexagonal coordinate $(xh,yh)$
	refers to the center of the disk on the horizontal row xh
	and positive-slope diagonal yh.   The geometric coordinate of
	such a point is a function of the radius of the disk $r$.
*/
void hex_to_geo(int xh, int yh, double r, double *xg, double *yg) {
	*yg = (2.0 * r) * xh * (sqrt(3)/2.0);
	*xg = (2.0 * r) * xh * (1.0/2.0) + (2.0 * r) * yh;
}

void geo_to_hex(double xg, double yg, double r, double *xh, double *yh) {
	*xh = (2.0/sqrt(3)) * yg / (2.0 * r);
	*yh = (xg - (2.0 * r) * (*xh) * (1.0/2.0) ) / (2.0 * r);
}

/*	Under the hexagonal coordinate system, the set of hexagons defined
	by coordinates (hx,hy), where $0 <= hx <= xmax$ and $0 <= hx <= ymax$
	forms a diamond-shaped patch, not a conventional axis-oriented 
	rectangle.  To solve this problem, we define array coordinates
	so that (ax,ay) refers to the position in an axis-oriented
	rectangle with (0,0) as the lower righthand point in the matrix.
*/
void array_to_hex(int xa, int ya, int *xh, int *yh) {
	*xh = xa;
	*yh = ya - xa + ceil(xa/2.0);
}

void hex_to_array(int xh, int yh, int *xa, int *ya) {
	*xa = xh;
	*ya = yh + xh - ceil(xh/2.0);
}


int plates_on_top(int xh, int yh, double w, double l, double r) {
	int number_on_top = 0;		/* total plates on top */
	int layers;			/* number of rows in grid */
	int rowlength;			/* number of plates in row */
	int row;			/* counter */
	int xla,yla,xra,yra;		/* array coordinates */

  layers = dense_layers(w,l,r);

	for (row=xh+1; row<layers; row++) {
		rowlength = plates_per_row(row,w,r) - 1;

		hex_to_array(row,yh-(row-xh),&xla,&yla);
		if (yla < 0) yla = 0;			/* left boundary */

		hex_to_array(row,yh,&xra,&yra);
		if (yra > rowlength) yra = rowlength;	/* right boundary */

		number_on_top += yra-yla+1;
	}

	return(number_on_top);
}

int main(void) {
	double w;			/* box width */
	double l;			/* box length */
	double r;			/* plate radius */

	int i,j;			/* counters */
	int xh,yh,xa,ya;
	double xhf,yhf,xg,yg;
	int xmax,ymax;

	printf("input box width, box length, and plate radius:\n");
	scanf("%lf %lf %lf",&w,&l,&r);
	printf("box width=%lf, box length=%lf, and plate radius=%lf:\n",w,l,r);
	printf("dense packing = %d\n", dense_plates(w,l,r));
	printf("grid packing = %d\n",  grid_plates(w,l,r));

	/* print all the possible hexes in the box */
	xmax = floor(w / (2*r));
	ymax = dense_layers(w,l,r);

	for (i=0; i<xmax; i++)
		printf("(0,%d) has %d on top.\n",i,plates_on_top(0,i,w,l,r));
		
  return 0;
}

/*test runs
osman@osman-desktop:~/src/algorithms$ ./plates
input box width, box length, and plate radius:
100 100 10
box width=100.000000, box length=100.000000, and plate radius=10.000000:
dense packing = 23
grid packing = 25
(0,0) has 8 on top.
(0,1) has 12 on top.
(0,2) has 14 on top.
(0,3) has 12 on top.
(0,4) has 8 on top.
osman@osman-desktop:~/src/algorithms$ ./plates
input box width, box length, and plate radius:
10 10 1
box width=10.000000, box length=10.000000, and plate radius=1.000000:
dense packing = 23
grid packing = 25
(0,0) has 8 on top.
(0,1) has 12 on top.
(0,2) has 14 on top.
(0,3) has 12 on top.
(0,4) has 8 on top.
*/
