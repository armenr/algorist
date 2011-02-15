/*see README for original credits */

#ifndef MWT_H
#define MWT_H

#include "bool.h"
#include "geometry.h"
#include <math.h>

point first_point;		/* first hull point */

void convex_hull(point in[], int n, polygon *hull);
void sort_and_remove_duplicates(point in[], int *n);
bool leftlower(const point *p1, const point *p2);
bool smaller_angle(const point *p1, const point *p2);

#endif /* MWT_H */


