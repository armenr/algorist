/*see README for original credits */

#include<stdio.h>
#include<math.h>

void prime_factorization(long x) {
	long i;			/* counter */
	long c;			/* remaining product to factor */

	c = x;

	while((c % 2) == 0) {
		printf("%ld\n", 2); 
		c /= 2;
	}

	i = 3;

	while(i <= (sqrt(c)+1)) 
		if((c % i) == 0) {
			printf("%ld\n", i);
			c /= i;	
		} else
			i = i + 2;

	if(c > 1) printf("%ld\n", c);
}

int main(void) {
  long p;

  printf("enter number: ");
  while(scanf("%ld", &p) != EOF) {
    printf("prime factorization of p=%ld \n", p);
    prime_factorization(p);
    printf("enter number: ");
  }
  return 0;
}

