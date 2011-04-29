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
3.2 The coupon collector’s problem

(refer to Understanding Probability Chance Rules in Everyday Life, 
Second Edition by HENK TIJMS, Vrije University)

For n = 10, we find then that the expected number of bags of chips needed in
order to get a complete set of flippos is equal to 29.3.

*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DICE 6
#define FLIPPOS 10
#define DAYS 365
#define RUNS 100000

static int n[] = {DICE, FLIPPOS, DAYS};
#define SIZE (int)(sizeof(n) / sizeof(n[0]))

static int totalPerRun(int n) {
  bool results[n];
  int i, r, f = 0, s = 0;
      
  for(i = 0; i < n; i++) 
    results[i] = false;

  while(f != n) {
    r = rand() % n;
    
    if(!results[r]) {
      results[r] = true;
      f++;    
    }
    s++;
  }
  
  return s;
}

static void printResults(void) {
  int i;
  
  srand(time(NULL));
  printf("for %d runs per n:\n", RUNS);
    
  for(i = 0; i < SIZE; i++) {
    int j, t = 0;
    
    for(j = 0; j < RUNS; j++) 
      t += totalPerRun(n[i]);
      
    printf("n = %d\tavg total %.1f\n", n[i], (float)t/RUNS);
  }
}

int main(void) {
  printResults();
  return 0;
}

/* test runs
osman@osman-vbox-l32:~/src/probs$ ./coupon 
for 100000 runs per n:
n = 6	avg total 14.7
n = 10	avg total 29.3
n = 365	avg total 2366.0
*/

