/*see README for original credits */

#include <stdio.h>

#define	MAXN	45		/* largest n or m */
#define UNKNOWN	-1		/* contents denote an empty cell */

static long f[MAXN+1];			/* array for caching computed fib values */

static long binomial_coefficient(int n, int m) {
	int i,j;		
	long bc[MAXN][MAXN];	/* table of binomial coefficient values */

	for(i = 0; i <= n; i++) bc[i][0] = 1;
  	for(j = 0; j <= n; j++) bc[j][j] = 1;

	for(i = 1; i <= n; i++)
		for(j = 1; j < i; j++)
			bc[i][j] = bc[i-1][j-1] + bc[i-1][j];

	return bc[n][m];
}

static long fib_r(int n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	return(fib_r(n-1) + fib_r(n-2));
}

static long fib_c(int n) {
	if(f[n] == UNKNOWN) 
		f[n] = fib_c(n-1) + fib_c(n-2);

	return f[n];
}

long fib_c_driver(int n) {
	int i;		

	f[0] = 0; 	f[1] = 1;
	for(i = 2; i <= n; i++)  f[i] = UNKNOWN;

	return fib_c(n);
}

static long fib_dp(int n) {
	int i;		
	long f[MAXN+1];         /* array for caching computed fib values */

  f[0] = 0; f[1] = 1;

  for(i = 2; i <= n; i++)  f[i] = f[i-1]+f[i-2];

  return f[n];
}

static long fib_dp2(int n) {
  int i;             
	long back1 = 1, back2 = 0;	/* last two values of f[n] */
	long next;		/* placeholder for sum */

	if(n == 0) return 0;

  for(i = 2; i < n; i++) {
		next = back1+back2;	back2 = back1; back1 = next;
	}
  return(back1+back2);
}


int main(void) {
	int i;

  for(i = 0; i < MAXN; i++)
    printf("fib_c(%d) = %d\n",i, fib_c_driver(i));
  for(i = 0; i < MAXN; i++)
    printf("fib_dp(%d) = %d\n",i, fib_dp(i));
  for(i = 0; i < MAXN; i++)
    printf("fib_dp2(%d) = %d\n",i, fib_dp2(i));
	for(i = 0; i < MAXN; i++)
		printf("fib(%d) = %d\n",i, fib_r(i));
  return 0;		
}

