/*see README for original credits */

#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include"geometry.h"

int main(void) {
	point p1, p2, q1, q2, i;
	line l1, l2, l3;

  printf("enter point p1 (x, y): ");
	while(scanf("%lf %lf", &p1[X], &p1[Y]) != EOF ) {
    printf("enter point p2 (x, y): ");
  	scanf("%lf %lf", &p2[X], &p2[Y]);
    printf("enter point q1 (x, y): ");
		scanf("%lf %lf", &q1[X], &q1[Y]);
    printf("enter point q2 (x, y): ");
		scanf("%lf %lf", &q2[X], &q2[Y]);

    print_point(p1);
		print_point(p2);
		print_point(q1);
		print_point(q2);

		points_to_line(p1, p2, &l1);
		points_to_line(q1, q2, &l2);

		print_line(l1);
		print_line(l2);
		
		printf("slope and line tests\n");
		point_and_slope_to_line(p1, -l1.a, &l3);
		print_line(l3);

    point_and_slope_to_line(p2, -l1.a, &l3);
    print_line(l3);
    point_and_slope_to_line(q1, -l2.a, &l3);
    print_line(l3);
    point_and_slope_to_line(q2, -l2.a, &l3);
    print_line(l3);

		printf("parallel lines test\n");
		printf("%d\n",  parallelQ(l1, l2));

		printf("intersection point\n");
		intersection_point(l1, l2, i);
		print_point(i);

		printf("closest point\n");
		closest_point(p1, l1, i);
		print_point(i);
    closest_point(p2, l1, i);
    print_point(i);
    closest_point(q1, l1, i);
    print_point(i);
    closest_point(q2, l1, i);
    print_point(i);
    closest_point(p1, l2, i);
    print_point(i);
    closest_point(p2, l2, i);
    print_point(i);
    closest_point(q1, l2, i);
    print_point(i);
    closest_point(q2, l2, i);
    print_point(i);

		printf("--------------------------------\n");
    printf("enter point p1 (x, y): ");
	}

  return 0;
}

/* test runs
osman@osman-desktop:~/src/algorithms$ ./geotest 
enter point p1 (x, y): 1 1
enter point p2 (x, y): 2 2
enter point q1 (x, y): 3 3
enter point q2 (x, y): 4 4
  1.000   1.000
  2.000   2.000
  3.000   3.000
  4.000   4.000
(a= -1.000, b=  1.000, c=  0.000)
(a= -1.000, b=  1.000, c=  0.000)
slope and line tests
(a= -1.000, b=  1.000, c= -0.000)
(a= -1.000, b=  1.000, c= -0.000)
(a= -1.000, b=  1.000, c= -0.000)
(a= -1.000, b=  1.000, c= -0.000)
parallel lines test
1
intersection point
Warning: Identical lines, all points intersect.
  0.000   0.000
closest point
  1.000   1.000
  2.000   2.000
  3.000   3.000
  4.000   4.000
  1.000   1.000
  2.000   2.000
  3.000   3.000
  4.000   4.000
--------------------------------

osman@osman-desktop:~/src/algorithms$ ./geotest 
enter point p1 (x, y): 5 5
enter point p2 (x, y): 15 5
enter point q1 (x, y): 10 10
enter point q2 (x, y): 10 0
  5.000   5.000
 15.000   5.000
 10.000  10.000
 10.000   0.000
(a=  0.000, b=  1.000, c= -5.000)
(a=  1.000, b=  0.000, c=-10.000)
slope and line tests
(a=  0.000, b=  1.000, c= -5.000)
(a=  0.000, b=  1.000, c= -5.000)
(a=  1.000, b=  1.000, c=-20.000)
(a=  1.000, b=  1.000, c=-10.000)
parallel lines test
0
intersection point
 10.000   5.000
closest point
  5.000   5.000
 15.000   5.000
 10.000   5.000
 10.000   5.000
 10.000   5.000
 10.000   5.000
 10.000  10.000
 10.000   0.000
--------------------------------
*/
