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
4.6.5 Shoemaker’s Problem
PC/UVa IDs: 110405/10026, Popularity: C, Success rate: average Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

3 4
1 1000
2 2
5 5

Sample Output

2 1 3 4
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// (start, length, penalty)
static int jobs[][3] = {{1, 3, 4}, {2, 1, 1000}, {3, 2, 2}, {4, 5, 5}};  
#define SIZE (int)sizeof(jobs) / (int)sizeof(jobs[0])

/*static int compare_length(const int* xh, const int* yh) {*/
/*  int x = *xh, y = *yh;*/
/*  */
/*	if(x < y) */
/*	  return -1;*/
/*	else if(x > y) */
/*	  return 0;*/

/*	return 1;*/
/*}*/

/*static int compare_penalty(const int* xh, const int* yh) {*/
/*  int x = *xh, y = *yh;*/
/*  */
/*  // comparisons reversed, we want list from high to low*/
/*	if(x < y) */
/*	  return 1;*/
/*	else if(x > y) */
/*	  return 0;*/

/*	return -1;*/
/*}*/

/*static void sort_people(void) {*/
/*  qsort(&people, TOTAL, sizeof(int), compare_people);	  */
/*}*/

/*static void print_people(void) {*/
/*  int i;*/
/*  */
/*  for(i = 0; i < TOTAL; i++) */
/*    printf("%d ", people[i]);*/
/*  */
/*  printf("\n");*/
/*}*/

/*//! side effect of printing in time function*/
/*static int calculate_time(void) {*/
/*  bool is_pair = (TOTAL < 3); // up to 2 people*/
/*  int next = (!is_pair) ? 0 : FINISHED; // next pair to cross, or none*/
/*  int time = 0;*/
/*  */
/*  if(!is_pair) {    */
/*    while(next < TOTAL-2) {*/
/*      time += people[TOTAL-2]; // lowest two across*/
/*      time += people[TOTAL-1]; // send lowest one back*/
/*      printf("%d %d\n", people[TOTAL-1], people[TOTAL-2]);*/
/*      printf("%d\n", people[TOTAL-1]);*/
/*      */
/*      if(next < TOTAL-3) {*/
/*        time += people[next];  // next pair cross*/
/*        time += people[TOTAL-2]; // send second lowest one back*/
/*        printf("%d %d\n", people[next+1], people[next]);*/
/*        printf("%d\n", people[TOTAL-2]);*/

/*      } else {   // one slow coach left to cross*/
/*        time += people[next];  // first and last cross*/
/*        printf("%d %d\n", people[TOTAL-1], people[next]);*/
/*      }*/
/*      */
/*      next += 2;  // next pair ready to cross*/
/*    }*/

/*    if(next == TOTAL-2) {// rest paired up*/
/*      time += people[TOTAL-2]; // lowest two finish, if rest have been paired */
/*      printf("%d %d\n", people[TOTAL-1], people[TOTAL-2]);      */
/*    } */
/*    */
/*  } else  { // two or less in a group*/
/*    int t;*/
/*    if(TOTAL == 1) {*/
/*      t = people[TOTAL-1];*/
/*      printf("%d\n", t);*/
/*    } else {*/
/*      t = people[TOTAL-2];*/
/*      printf("%d %d\n", people[TOTAL-1], t);*/
/*    }*/
/*    time += t;*/
/*  }*/

/*  return time;  */
/*}*/

int main(void) {
/*  printf("people:\n");*/
/*  print_people();*/
/*  sort_people();*/
/*  printf("strategy:\n");*/
/*  int t = calculate_time(); //! side effect of printing*/
/*  printf("time taken is %d units\n", t);  */
  return 0;
}

/* test runs
new copie sorted by start, length and penalty

1 1 
2 3 4
3  
4  
5 2 4
6  
7 5 15
8  
9  
10  
11 

1 1 
2 3 4
3  
4  
5 5 5
6
7
8  
9  
10 2 14
11 

*/

