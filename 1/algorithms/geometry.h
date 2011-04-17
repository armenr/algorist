/*see README for original credits */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#define	PI	3.1415926	/* ratio of circumference to diameter */
#define EPSILON	0.000001	/* a quantity small enough to be zero */

typedef struct {
	double a;		/* x-coefficient */
	double b;		/* y-coefficient */
	double c;		/* constant term */
} line;

#define DIMENSION	2	/* dimension of points */
#define X		0	/* x-coordinate index */
#define	Y		1	/* y-coordinate index */

typedef double point[DIMENSION];

#define MAXPOLY		200	/* maximum number of points in a polygon */

typedef struct {
	int n;			/* number of points in polygon */
	point p[MAXPOLY];	/* array of points in polygon */
} polygon;


typedef struct {
	point p1,p2;		/* endpoints of line segment */
} segment;

typedef point triangle[3];	/* triangle datatype */

typedef struct {
	int n;			/* number of triangles in triangulation */
	int t[MAXPOLY][3];	/* indicies of vertices in triangulation */
} triangulation;

typedef struct {
	point c;		/* center of circle */
	double r;		/* radius of circle */
} circle;


/*	Comparison macros 	*/

#define	max(A, B)		((A) > (B) ? (A) : (B))
#define min(A, B)		((A) < (B) ? (A) : (B))

void closest_point(const point p_in, line l, point p_c);
bool collinear(const point a, const point b, const point c);
void copy_point(const point a, point b);
bool ccw(const point a, const point b, const point c);
bool cw(const point a, const point b, const point c);
double distance(const point a, const point b);
void intersection_point(line l1, line l2, point p);
bool parallelQ(line l1, line l2);
void points_to_segment(const point a, const point b, segment *s);
bool point_in_box(const point p, const point b1, const point b2);
void points_to_line(const point p1, const point p2, line *l);
void point_and_slope_to_line(const point p, double m, line *l);
void print_points(const point p[], int n);
void print_polygon(const polygon *p);
void print_point(const point p);
void print_line(line l);
void print_segment(const segment s);
void segment_to_points(const segment s, point p1, point p2);
bool segments_intersect(segment s1, segment s2);
double signed_triangle_area(const point a, const point b, const point c);
void swap_point(point a, point b);
bool same_lineQ(line l1, line l2);
double triangle_area(const point a, const point b, const point c);

#endif /* GEOMETRY_H */


