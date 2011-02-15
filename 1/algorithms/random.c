/*see README for original credits */

#include "random.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double random_float(int low,int high) {
  int rand();
  double i,j;                             /* avoid arithmetic trouble */
  double r;                                  /*random number*/

  i = RAND_MAX / (high-low);
  i *= (high-low);

  while((j = rand()) >=i) continue;
  r = (j/i) * (high-low) + low;

  if((r < low) || (r > high))
    printf("ERROR: random real %f out of range [%d, %d]\n", r, low, high);

  return(r);

}

int random_int(int low, int high) {
  int rand();
  int i,j,r;                                      /*random number*/

  i = RAND_MAX / (high-low+1);
  i *= (high-low+1);

  while((j = rand()) >=i) continue;

  r = (j % (high-low+1)) + low;

  /*printf("rand=%d RAND_MAX=%d \n",r,RAND_MAX);*/
  /*printf("rand=%d low=%d high=%d \n",r,low,high);*/

  if((r < low) || (r > high))
    printf("Error: random integer %d out of range [%d, %d]\n", r, low, high);

  return(r);
}

/*      Construct a random permutation of the $n$ elements of the
        given array.
*/
void random_permutation(int a[], int n) {
  int i;

  for(i = n; i > 1; i--) 
    swap(&a[i-1], &a[random_int(0, i-1)]);
}

void swap(int *a, int *b) {
  int x;
  x = *a; *a = *b; *b = x;
}



