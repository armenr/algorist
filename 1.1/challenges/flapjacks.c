/*
 Copyright 2010 Osman Pub

 Licensed under the Apache License, Version 2.0 (the "License"); you may not use
 this file except in compliance with the License.
  
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software distributed
 under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied. See the License for the
 specific language governing permissions and limitations under the License.
 */

/*
4.6.2 Stacks of Flapjacks
PC/UVa IDs: 110402/120, Popularity: B, Success rate: high Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

1 2 3 4 5 
5 4 3 2 1 
5 1 2 3 4 

Sample Output

1 2 3 4 5 
0
5 4 3 2 1 
1 0
5 1 2 3 4 
1 2 0
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_FLAPS (int)5  

static int flapjacks[][MAX_FLAPS] = {
{1, 2, 3, 4, 5}, 
{5, 4, 3, 2, 1}, 
{5, 1, 2, 3, 4}};
#define TOTAL_FLAPS (int)sizeof(flapjacks) / (int)sizeof(flapjacks[0])

static int sorted_flapjacks[TOTAL_FLAPS][MAX_FLAPS];

static int compare_flapjacks(const int* xh, const int* yh) {
  int x = *xh, y = *yh;
  
	if(x < y) 
	  return -1;
	else if(x > y) 
	  return 1;

	return 0;
}

static void sort_flapjacks(void) {
  int i;

  // copy first
  for(i = 0; i < TOTAL_FLAPS; i++) {
    int l = sizeof(int) * MAX_FLAPS;
    memcpy(&sorted_flapjacks[i], &flapjacks[i], l);
  }
  
  for(i = 0; i < TOTAL_FLAPS; i++) 
	  qsort(&sorted_flapjacks[i], MAX_FLAPS, sizeof(int), compare_flapjacks);	  
}

static void print_flapjacks(int* fp) {
  int i, j;
  
  for(i = 0; i < TOTAL_FLAPS; i++) {
    int l = i * MAX_FLAPS;
    
    for(j = 0; j < MAX_FLAPS; j++) {
      int f = fp[l + j];
      printf("%d ", f);
    }
    printf("\n");
  }
}

static bool is_sorted(int p) {
  int i;
  
  for(i = 0; i < MAX_FLAPS; i++)     
    if(flapjacks[p][i] != sorted_flapjacks[p][i])
      return false;
      
  return true;
}

static int flip(int f, int l, int p) {
  int i, sz = l-f;;
  int tmp[sz];  // store reversed array here
  
  for(i = 0; i < sz+1; i++)     
    tmp[i] = flapjacks[p][l-i];  // flip (reverse) flapjack array from f to l

  for(i = 0; i < sz+1; i++)     
    flapjacks[p][f+i] = tmp[i];  // copy back into flapjack array

  return MAX_FLAPS - l; // return position of flip
}        
  
static int find_flapjack(int f, int p) {
  int i;
  
  for(i = 0; i < MAX_FLAPS; i++)     
    if(flapjacks[p][i] == f)
      return i; // index of flapjack in unsorted array
      
  return -1;  // not found
}

static void find_sequences(void) {
  int i, j;
  
  for(i = 0; i < TOTAL_FLAPS; i++) {
    for(j = MAX_FLAPS-1; j >= 0; j--) {
      if(is_sorted(i))
        break;
        
      int f = sorted_flapjacks[i][j];  // find next largest flapjack to search 
      int k = find_flapjack(f, i);  // find flapjack to flip
      
      if(j != k) {  // out of sync
        if(k != 0)  // not in first position
          printf("%d ", flip(0, k, i));  // get flapjack in front position

        printf("%d ", flip(0, j, i));
      }
    }     

    printf("0\n");
  }     
}

int main(void) {
  printf("\nflapjack piles:\n");
  print_flapjacks(&flapjacks);
  sort_flapjacks();
  printf("\nflip sequences:\n");
  find_sequences();
  printf("\nsorted flapjack piles:\n");
  print_flapjacks(&flapjacks);
  return 0;
}

/* test runs
osman@osman-desktop:~/src/algorist/1.1/challenges$ make flapjacks && ./flapjacks 
gcc -Wall -Wextra -ggdb    -c -o flapjacks.o flapjacks.c
flapjacks.c: In function ‘sort_flapjacks’:
flapjacks.c:75: warning: passing argument 4 of ‘qsort’ from incompatible pointer type
/usr/include/stdlib.h:756: note: expected ‘__compar_fn_t’ but argument is of type ‘int (*)(const int *, const int *)’
flapjacks.c: In function ‘main’:
flapjacks.c:150: warning: passing argument 1 of ‘print_flapjacks’ from incompatible pointer type
flapjacks.c:78: note: expected ‘int *’ but argument is of type ‘int (*)[3][5]’
flapjacks.c:155: warning: passing argument 1 of ‘print_flapjacks’ from incompatible pointer type
flapjacks.c:78: note: expected ‘int *’ but argument is of type ‘int (*)[3][5]’
gcc   flapjacks.o   -o flapjacks

flapjack piles:
1 2 3 4 5 
5 4 3 2 1 
5 1 2 3 4 

flip sequences:
0
1 0
1 2 0

sorted flapjack piles:
1 2 3 4 5 
1 2 3 4 5 
1 2 3 4 5 
*/

