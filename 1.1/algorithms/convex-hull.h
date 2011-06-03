/*see README for original credits */

#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include<math.h>
#include<stdbool.h>
#include"geometry.h"

point first_point;		/* first hull point */

void convex_hull(point in[], int n, polygon *hull);
void sort_and_remove_duplicates(point in[], int *n);
bool leftlower(const point *p1, const point *p2);
bool smaller_angle(const point *p1, const point *p2);

#endif /* CONVEX_HULL_H */

