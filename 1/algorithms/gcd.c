/*see README for original credits */

#include<math.h>
#include<stdio.h>

/* integers to compute the GCD of */
static long gcd1(long p, long q) {
	if(q > p) return gcd1(q,p);
	if(q == 0) return p;

	printf(" gcd(%ld,%ld) &=& gcd(%ld \\mod %ld, %ld) = gcd(%ld,%ld) \n",
	  p, q, p, q, q, q, p%q);
	return( gcd1(q, p % q) );
}

/*	Find the gcd(p,q) and x,y such that p*x + q*y = gcd(p,q)	*/
long gcd(long p, long q, long *x, long *y) {
	long x1,y1;			/* previous coefficients */
	long g;				/* value of gcd(p,q) */

  if(q > p) return gcd(q,p,y,x);
  if(q == 0) {
    *x = 1; *y = 0;
    return p;
	}

  g = gcd(q, p%q, &x1, &y1);
  *x = y1;
  *y = (x1 - floor(p/q)*y1);
  return g;
}

int main(void) {
  long p, q;
  long x, y, g1, g2;

  while(scanf("%ld %ld", &p, &q)!=EOF) {
    printf("gcd of p = %ld and q = %ld = %ld\n",p, q, g1 = gcd1(p, q));
    printf(" %ld*%ld + %ld*%ld = %ld\n",p, x, q, y, g2 = gcd(p, q, &x, &y));

    if(g1 != g2) printf("ERROR: GCD\n");
    if((p*x + q*y) != g1) printf("ERROR: DIOPHONINE SOLUTION WRONG!\n");
  }
  return 0;      
}


