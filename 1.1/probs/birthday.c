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
3.1 The birthday problem

(refer to Understanding Probability Chance Rules in Everyday Life, 
Second Edition by HENK TIJMS, Vrije University)

Table 3.1. Probabilities for the birthday problem.
n   pn
15  0.2529 
20  0.4114      
23  0.5073
25  0.5687
30  0.7063 
40  0.8912
50  0.9704
75  0.9997
*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DAYS 365
#define RUNS 1000000

static int n[] = {15, 20, 23, 25, 30, 40, 50, 75};
#define SIZE (int)(sizeof(n) / sizeof(n[0]))

static bool isRunSuccessful(int n) {
  bool results[DAYS];
  int i, r;
      
  for(i = 0; i < DAYS; i++) 
    results[i] = false;

  for(i = 0; i < n; i++) {
    r = rand() % DAYS;
    
    if(!results[r])
      results[r] = true;
    else 
      return true;
  }
  
  return false;
}

static void printResults(void) {
  int i;
  srand(time(NULL));
  
  for(i = 0; i < SIZE; i++) {
    int j, c = 0;   
    
    for(j = 0; j < RUNS; j++)   
      if(isRunSuccessful(n[i])) 
        c++;     
        
    printf("n = %d\t%d of %d (%.2f%%) runs successful\n", n[i], c, j, 
      (float)c/j*100);
  }   
}

int main(void) {
  printResults();
  return 0;
}

/* test runs
osman@osman-vbox-l32:~/src/probs$ ./birthday 
n = 15	253142 of 1000000 (25.31%) runs successful
n = 20	411422 of 1000000 (41.14%) runs successful
n = 23	507196 of 1000000 (50.72%) runs successful
n = 25	568053 of 1000000 (56.81%) runs successful
n = 30	706014 of 1000000 (70.60%) runs successful
n = 40	891530 of 1000000 (89.15%) runs successful
n = 50	970232 of 1000000 (97.02%) runs successful
n = 75	999736 of 1000000 (99.97%) runs successful
*/

