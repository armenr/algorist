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
3.3 Craps

(refer to Understanding Probability Chance Rules in Everyday Life, 
Second Edition by HENK TIJMS, Vrije University)

Putting it all together, we get P(win) = 0.4929.
In other words, the probability of the player losing is 0.5071. The casino payout
is 1:1, so that you would lose on average (0.5071 − 0.4929) × 100 = 1.42 cents
  
*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DIE 6
#define RUNS 1000000

static int lose[] = {2, 3, 12};
#define LOSE_SIZE (int)(sizeof(lose) / sizeof(lose[0]))
#define FURTHER_LOSE 7

static int win[] = {7, 11};
#define WIN_SIZE (int)(sizeof(win) / sizeof(win[0]))

static int rollDie(void) {
  return (rand() % DIE)+1;
}

static bool findTotal(int a[], int sz, int f) {
  int i;
  for(i = 0; i < sz; i++)
    if(a[i] == f)
      return true;
  return false;
}

static bool isWinner(void) {
  int t, it;
  
  t = it = rollDie() + rollDie();
  
  if(findTotal(win, WIN_SIZE, t))
    return true;
    
  else if(findTotal(lose, LOSE_SIZE, t))
    return false;
    
  else {
    t = rollDie() + rollDie();
    for( ; (t != it) && (t != FURTHER_LOSE); ) 
      t = rollDie() + rollDie();
      
    if(t == it)
      return true;
    else if(t == FURTHER_LOSE)
      return false;
  }    
}

static void printResults(void) {
  int i, l = 0, w = 0;
  
  srand(time(NULL));
  
  for(i = 0; i < RUNS; i++) 
    if(isWinner())
      w++;
    else 
      l++;
  
  printf("wins: %d (%.1f%%)\tlosses: %d (%.1f%%)\tfrom %d runs\n", w, 
    (float)w/RUNS*100, l, (float)l/RUNS*100, RUNS);    
}

int main(void) {
  printResults();
  return 0;
}

/* test runs
osman@osman-vbox-l32:~/src/probs$ ./crapshoot 
wins: 492804 (49.3%)	losses: 507196 (50.7%)	from 1000000 runs
*/

