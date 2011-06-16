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
4.6.1 Vito’s Family

PC/UVa IDs: 110401/10041, Popularity: A, Success rate: high Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

2 4
2 4 6
4 8 16 2 2 8
4 8 16 2 32 2 8

Sample Output

2
4
18
42
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"../ds/util.h"

#define MAX_HOUSES (int)7  
#define IGNORE 0

static int house[][MAX_HOUSES] = {
{2, 4, 0, 0, 0, 0, 0}, 
{2, 4, 6, 0, 0, 0, 0}, 
{4, 8, 16, 2, 2, 8, 0}, 
{4, 8, 16, 2, 32, 2, 8}};
#define TOTAL_HOUSES (int)sizeof(house) / (int)sizeof(house[0])

static int count[TOTAL_HOUSES] = {0, 0, 0}; /*count of uniques*/
static int median[TOTAL_HOUSES] = {0, 0, 0}; /*median of uniques*/

static void sort_houses(void) {
  int i;
  for(i = 0; i < TOTAL_HOUSES; i++) 
	  qsort(&house[i], MAX_HOUSES, sizeof(int), compare_keys_int);	  
}

static void print_houses(void) {
  int i, j;

  for(i = 0; i < TOTAL_HOUSES; i++) {
    for(j = 0; j < MAX_HOUSES; j++) {
      int h = house[i][j];
      
      if(h > IGNORE)
        printf("%d ", h);
    }

    printf("\n");
  }
}

static void remove_duplicates(void) {
/* ensure arrays are sorted first*/
  bool found;
  int i, j;

  for(i = 0; i < TOTAL_HOUSES; i++) {
    int d = IGNORE;  /* first duplicate house */
    
    for(j = 1; j < MAX_HOUSES; j++) {
      found = house[i][j] ==  house[i][j-1];
      
      if(d == IGNORE) {
        if(found) 
          d = j;  /* start index of duplicates*/

      } else {
        if(!found) {  /* erase duplicates*/
          int k;
          for(k = d; k < j; k++)
            house[i][k] = IGNORE;
          d = IGNORE;
        }
      }      
    }
  }    
}

static void count_uniques(void) {
  int i, j;

  for(i = 0; i < TOTAL_HOUSES; i++) 
    for(j = 0; j < MAX_HOUSES; j++) {
      int h = house[i][j];      
      if(h > IGNORE)
        count[i]++;
    }
}

static void find_medians(void) {
  int i, j;

  for(i = 0; i < TOTAL_HOUSES; i++) {
    int m = (count[i]-1) / 2; /* floor of median    */
    int c = 0;
    
    for(j = 0; j < MAX_HOUSES; j++) {
      int h = house[i][j];      
      
      if(h > IGNORE) {
        if(c < m)
          c++;
        else {
          median[i] = h;
          break;      
        }
      }        
    }
  }
}

static void print_totals(void) {
  int i, j;

  for(i = 0; i < TOTAL_HOUSES; i++) {    
    int s = 0;
    
    for(j = 0; j < MAX_HOUSES; j++) {
      int h = house[i][j];      
      
      if(h > IGNORE) {
        int v = abs(h - median[i]);
        s += v;
      }        
    }
    printf("%d\n", s);
  }
}

int main(void) {
  print_houses();
  sort_houses();
  remove_duplicates();
  count_uniques();
  find_medians();
  print_totals();
  return 0;
}


/* test runs
osman@osman-desktop:~/src/algorist/1.1/challenges$ make vito && ./vito 
gcc -Wall -Wextra -ggdb    -c -o vito.o vito.c
vito.c: In function ‘sort_houses’:
vito.c:67: warning: passing argument 4 of ‘qsort’ from incompatible pointer type
/usr/include/stdlib.h:756: note: expected ‘__compar_fn_t’ but argument is of type ‘int (*)(const int *, const int *)’
gcc   vito.o   -o vito
2 4 
2 4 6 
4 8 16 2 2 8 
4 8 16 2 32 2 8 
2
4
18
42
*/

