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
4.6.3 Bridge
PC/UVa IDs: 110403/10037, Popularity: B, Success rate: low Level: 3

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

1
2
5
10

Sample Output

17
1 2
1
5 10
2
1 2
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define FINISHED -1  /*no more left to cross bridge*/

static int people[] = {1, 2, 5, 10};
#define TOTAL (int)sizeof(people) / (int)sizeof(people[0])

static int compare_people(const int* xh, const int* yh) {
  int x = *xh, y = *yh;
  
  /* comparisons reversed, we want list from high to low */
	if(x < y) 
	  return 1;
	else if(x > y) 
	  return 0;

	return -1;
}

static void sort_people(void) {
  qsort(&people, TOTAL, sizeof(int), compare_people);	  
}

static void print_people(void) {
  int i;
  
  for(i = 0; i < TOTAL; i++) 
    printf("%d ", people[i]);
  
  printf("\n");
}

/*! side effect of printing in time function*/
static int calculate_time(void) {
  bool is_pair = (TOTAL < 3); /* up to 2 people*/
  int next = (!is_pair) ? 0 : FINISHED; /* next pair to cross, or none*/
  int time = 0;
  
  if(!is_pair) {    
    while(next < TOTAL-2) {
      time += people[TOTAL-2]; /* lowest two across*/
      time += people[TOTAL-1]; /* send lowest one back*/
      printf("%d %d\n", people[TOTAL-1], people[TOTAL-2]);
      printf("%d\n", people[TOTAL-1]);
      
      if(next < TOTAL-3) {
        time += people[next];  /* next pair cross*/
        time += people[TOTAL-2]; /* send second lowest one back*/
        printf("%d %d\n", people[next+1], people[next]);
        printf("%d\n", people[TOTAL-2]);

      } else {   /* one slow coach left to cross*/
        time += people[next];  /* first and last cross*/
        printf("%d %d\n", people[TOTAL-1], people[next]);
      }
      
      next += 2;  /* next pair ready to cross*/
    }

    if(next == TOTAL-2) {/* rest paired up*/
      time += people[TOTAL-2]; /* lowest two finish, if rest have been paired */
      printf("%d %d\n", people[TOTAL-1], people[TOTAL-2]);      
    } 
    
  } else  { /* two or less in a group*/
    int t;
    if(TOTAL == 1) {
      t = people[TOTAL-1];
      printf("%d\n", t);
    } else {
      t = people[TOTAL-2];
      printf("%d %d\n", people[TOTAL-1], t);
    }
    time += t;
  }

  return time;  
}

int main(void) {
  printf("people:\n");
  print_people();
  sort_people();
  printf("strategy:\n");
  int t = calculate_time(); /* side effect of printing*/
  printf("time taken is %d units\n", t);  
  return 0;
}

/* test runs
osman@osman-desktop:~/src/algorist/1.1/challenges$ make bridge && ./bridge 
gcc -Wall -Wextra -ggdb    -c -o bridge.o bridge.c
bridge.c: In function ‘sort_people’:
bridge.c:62: warning: passing argument 4 of ‘qsort’ from incompatible pointer type
/usr/include/stdlib.h:756: note: expected ‘__compar_fn_t’ but argument is of type ‘int (*)(const int *, const int *)’
gcc   bridge.o   -o bridge

people:
1 
strategy:
1
time taken is 1 units

people:
1 2 
strategy:
1 2
time taken is 2 units

people:
1 2 5 
strategy:
1 2
1
1 5
time taken is 8 units

people:
1 2 5 10 
strategy:
1 2
1
5 10
2
1 2
time taken is 17 units

people:
1 2 5 10 20 
strategy:
1 2
1
10 20
2
1 2
1
1 5
time taken is 33 units

people:
1 2 5 10 20 40 
strategy:
1 2
1
20 40
2
1 2
1
5 10
2
1 2
time taken is 62 units
*/

