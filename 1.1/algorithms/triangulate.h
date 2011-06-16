/*see README for original credits */

#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include<stdbool.h>
#include"geometry.h"

void triangulate(const polygon *p, triangulation *t);
void add_triangle(triangulation *t, int i, int j, int k);
bool ear_Q(int i, int j, int k, const polygon *p);
bool point_in_triangle(const point p, triangle t);
double area_triangulation(const polygon *p);
double area(const polygon *p);
void print_triangulation(const triangulation *t);

#endif /* TRIANGULATE_H */
