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
2.8.3     Hartals
PC/UVa IDs: 110203/10050, Popularity: B, Success rate: high Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

2
14
3
3
4
8
100
4
12
15
25
40

Sample Output

5
15
*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include"../ds/util.h"

#define NOT_FOUND -1
#define FRIDAY 6
#define SATURDAY 7
#define WEEK 7

static bool isHoliday(int day, int holiday) {
  int weeks = day / WEEK, weeksInDays = weeks * WEEK;

  if((day - weeksInDays) % holiday == 0)
    return true;
  else
    return false;
}

static void sortHartals(int h[], int n) {
	qsort(&h, n, sizeof(int), compare_keys_int);
}

static int countHartals(const int h[], int n, int d) {
  int i, j, k, count = 0;

  /* do initial count with smallest number */
  for(i = 0; i <= d; i += h[0]) 
    if(!isHoliday(i, FRIDAY) && !isHoliday(i, SATURDAY)) /* skip weekends */
      count++;    

  /* for rest, we have to check that we don't recount previous numbers */
  for(j = 1; j <= n-1; j++) 
    for(i = 0; i <= d; i += h[j]) 
      if(!isHoliday(i, FRIDAY) && !isHoliday(i, SATURDAY)) { /* skip weekends */
        /* higher numbers may have some of their counts already done */
        for(k = 0; k < j; k++) {
          /* if lower number is a factor then skip */
          if(h[j] % h[k] == 0)
            break;
            
          if(i % h[k] == 0) /* already counted */
            break;
        }
        if(k == j)  /* not already counted */
          count++;               
     }
  
  return count;
}

int main(void) {
  int i, d; /* days */
  printf("no of days: ");
  scanf("%d", &d);

  int h; /* hartals */
  printf("no of hartals: ");
  scanf("%d", &h);

  int hartals[h];

  printf("enter hartals, one per line, that isn't a multiple of %d\n", WEEK);
  for(i = 0; i < h; i++)
    scanf("%d", &hartals[i]);

  sortHartals(hartals, h); /* sort from low to high */ 
  printf("%d\n", countHartals(hartals, h, d));
  
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./hartals 
no of days: 14
no of hartals: 3
enter hartals, one per line, that isn't a multiple of 7
3
4
8
5
osman@osman-desktop:~/src/challenges$ ./hartals 
no of days: 100
no of hartals: 4
enter hartals, one per line, that isn't a multiple of 7
12
15
25
40
15
osman@osman-desktop:~/src/challenges$ ./hartals 
no of days: 14
no of hartals: 1
enter hartals, one per line, that isn't a multiple of 7
1
10
osman@osman-desktop:~/src/challenges$ ./hartals 
no of days: 14
no of hartals: 1
enter hartals, one per line, that isn't a multiple of 7
2
5
osman@osman-desktop:~/src/challenges$ ./hartals 
no of days: 100
no of hartals: 4
enter hartals, one per line, that isn't a multiple of 7
40
25
15
12
15
*/
