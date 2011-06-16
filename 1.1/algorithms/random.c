/*see README for original credits */

/*consider using random number generators in stdlib.h instead*/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include"random.h"

double random_float(int low, int high) {
  double i = RAND_MAX / (high - low);

  i *= (high - low);

  double j;
  
  while ((j = rand()) >= i) 
    continue;

  double r = (j / i) * (high - low) + low;

  if(r < low || r > high)
    printf("ERROR: random real %f out of range [%d, %d]\n", r, low, high);

  return r;
}

int random_int(int low, int high) {
  int i = RAND_MAX / (high - low + 1);

  i *= (high - low + 1);

  int j;
  
  while((j = rand()) >= i) 
    continue;

  int r = (j % (high - low + 1)) + low;

  if(r < low || r > high)
    printf("Error: random integer %d out of range [%d, %d]\n", r, low, high);

  return r;
}

/*      Construct a random permutation of the $n$ elements of the
        given array.
 */
void random_permutation(int a[], int n) {
  int i;

  for (i = n; i > 1; i--)
      swap(&a[i - 1], &a[random_int(0, i - 1)]);
}

void swap(int* a, int* b) {
  int x = *a;
  *a = *b;
  *b = x;
}
