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
2.1.2 Random walk

(refer to Understanding Probability Chance Rules in Everyday Life, 
Second Edition by HENK TIJMS, Vrije University)

Table 2.2. Probability P(α, β) in the arc-sine law.

(α, β)          P(α, β)   (α, β)      P(α, β)
(0.50, 0.505)   0.0064    (0.995, 1)  0.0901
(0.50, 0.510)   0.0127    (0.990, 1)  0.1275
(0.50, 0.525)   0.0318    (0.975, 1)  0.2022
(0.50, 0.550)   0.0638    (0.950, 1)  0.2871
(0.50, 0.600)   0.1282    (0.900, 1)  0.4097
*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define COIN 2
#define HEADS (COIN / 2)
#define MATCH 20
#define RUNS 1000000

static int heads[MATCH+1];
static int tails[MATCH+1];

static int tossCoin(void) {
  return (rand() % COIN);
}

static void playMatch(void) {
  int i, c, h = 0, t = 0, hl = 0, tl = 0;

  for(i = 0; i < MATCH; i++) {
    c = tossCoin();
    
    if(c < HEADS)
      h++;
    else
      t++;
      
    if(h > t) 
      hl++;
    else if(t > h) 
      tl++;
      
/*    printf("round: %d toss: %d h: %d t: %d h_l: %d t_l: %d\n", i, c, h, t, */
/*      hl, tl);    */
  }  
  
  heads[hl]++;
  tails[tl]++;
}

static void printResults(void) {
  int i;
  
  srand(time(NULL));

  for(i = 0; i < MATCH+1; i++) 
    heads[i] = tails[i] = 0;

  for(i = 0; i < RUNS; i++)   
    playMatch();

  printf("n = %d\n", RUNS);
  
  for(i = 1; i < MATCH+1; i++) {
    int s = heads[i] + tails[i];
    printf("lead: %d heads: %d tails: %d total: %d (%.2f%%)\n", i, heads[i], 
      tails[i], s, (float)s/RUNS*100);    
  }
}

int main(void) {
  printResults();
  return 0;
}

/* test runs
osman@osman-vbox-l32:~/src/probs$ ./random-walk 
n = 1000000
lead: 1 heads: 88168 tails: 88297 total: 176465 (17.65%)
lead: 2 heads: 46273 tails: 46100 total: 92373 (9.24%)
lead: 3 heads: 46115 tails: 46310 total: 92425 (9.24%)
lead: 4 heads: 36955 tails: 36874 total: 73829 (7.38%)
lead: 5 heads: 36923 tails: 36998 total: 73921 (7.39%)
lead: 6 heads: 32659 tails: 32918 total: 65577 (6.56%)
lead: 7 heads: 32731 tails: 32771 total: 65502 (6.55%)
lead: 8 heads: 30772 tails: 30713 total: 61485 (6.15%)
lead: 9 heads: 30829 tails: 30894 total: 61723 (6.17%)
lead: 10 heads: 30355 tails: 30321 total: 60676 (6.07%)
lead: 11 heads: 30561 tails: 30397 total: 60958 (6.10%)
lead: 12 heads: 31196 tails: 30923 total: 62119 (6.21%)
lead: 13 heads: 30867 tails: 30742 total: 61609 (6.16%)
lead: 14 heads: 32512 tails: 32756 total: 65268 (6.53%)
lead: 15 heads: 32732 tails: 32512 total: 65244 (6.52%)
lead: 16 heads: 36805 tails: 36841 total: 73646 (7.36%)
lead: 17 heads: 36729 tails: 36779 total: 73508 (7.35%)
lead: 18 heads: 46484 tails: 46449 total: 92933 (9.29%)
lead: 19 heads: 46041 tails: 46228 total: 92269 (9.23%)
lead: 20 heads: 88207 tails: 88088 total: 176295 (17.63%)
*/

