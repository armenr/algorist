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
1.6.8     Australian Voting
PC/UVa IDs: 110108/10142, Popularity: B, Success rate: low Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input                                 Sample Output

1                                            John Doe

3
John Doe
Jane Smith
Jane Austen
1 2 3
2 1 3
2 3 1
1 2 3
3 1 2
*/

#include<stdbool.h>
#include<stdio.h>

#define NUM_CAND 3

static char *candidates[NUM_CAND] = {"John Doe", "Jane Smith", "Jane Austen"};
/* format for totals is {candidate number, total}*/
static int totals[NUM_CAND][2] = {{0, 0}, {1, 0}, {2, 0}}; 

/* test data, comment out the ones preferred */
/*#define NUM_BALLOTS 5*/
/*static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, */
/*  {0, 1, 2}, {2, 0, 1}};*/

/*#define NUM_BALLOTS 6*/
/*static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, */
/*  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}};*/

/*#define NUM_BALLOTS 7*/
/*static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, */
/*  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}, {1, 0, 2}};*/

#define NUM_BALLOTS 8
static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 2, 1}, {1, 0, 2}, {1, 2, 0}, 
  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}, {0, 2, 1}, {2, 1, 0}};

#define WINNING_POST NUM_BALLOTS / 2


static void addUpLoserVotes(int choice, int first, int last) {
/* first and last denote range of loser votes */
  int candidate, i, j, k;

  /* check losers ballots */
  for(k = first; k <= last; k++)    
    for(i = 0; i < NUM_BALLOTS; i++) {

      if(ballots[i][0] == k) { /* found loser */
        candidate = ballots[i][choice]; /* get next candidate */

        /* if the loser votes for an eliminated candidate then ignore vote */
        if(totals[candidate][1] >= totals[first][1]) {
          j = 0;
      
          /* make sure we update the correct total */
          while(j < NUM_BALLOTS && totals[j][0] != candidate)
            j++;
          totals[j][1]++;                        
        }
      }    
    }
}

static void addUpVotes(int choice) {
  int candidate, i, j;

  for(i = 0; i < NUM_BALLOTS; i++) {
    candidate = ballots[i][choice];
    j = 0;

    /* make sure we update the correct total */
    while(j < NUM_BALLOTS && totals[j][0] != candidate)
      j++;
    totals[j][1]++;   
  }
}

/* index of loser or first of tied loser */
static int findLoser(int loser) {
  int l, losing_total = totals[loser][1]; 

  for(l = loser; totals[l][1] == losing_total; 
    l--) ;
    
  return l+1;
}

/* index of winner or last tied winner */ 
static int findWinner(void) {
  int winner, winning_total = totals[0][1]; 

  for(winner = 1; totals[winner][1] == winning_total; 
    winner++) ;
    
  return winner-1;
}

/* only sort totals of winners, ignore losers as found after each round */
static void sortTotals(int loser) {
	int i, j, k, v; /* key value pairs for totals */
  /* insertion sort, replace with quicksort for large N */
	for(i = 1; i < loser; i++) {
	  j = i;
	  while((j > 0) && (totals[j][1] > totals[j-1][1])) {
	    /* swap function */
	    k = totals[j][0]; v = totals[j][1];
	    totals[j][0] = totals[j-1][0]; totals[j][1] = totals[j-1][1];
	    totals[j-1][0] = k; totals[j-1][1] = v;
		  j = j-1;
	  }
	}
}

static void printTotals(void) {
  int i;
  for(i = 0; i < NUM_CAND; i++) 
    printf("%s: %d\n", candidates[totals[i][0]], totals[i][1]);
}

static void printWinner(void) {
  /* print winner or tied winners */
  int i, lastWinner = findWinner();
  for(i = 0; i <= lastWinner; i++)
    printf("And the winner(s) is(are) %s\n", candidates[totals[i][0]]);    
}

int main(void) {
  int choice = 0; /* start with 1st choice */
  /* initially loser or tied losers (in sorted totals) are unknown */  
  int firstLoser = -1, lastLoser; 
  bool foundWinner = false;

  while(!foundWinner) {

    if(firstLoser == -1) { /* first round */
      addUpVotes(choice);  

      /* sort all totals after 1st round of voting */          
      firstLoser = NUM_CAND; 

    } else  /* next round */
      addUpLoserVotes(choice, firstLoser, lastLoser);  
    
/*printTotals();   // debug */

    sortTotals(firstLoser);

    /* winning total should be first in sorted totals */
    if(findWinner() == 0 && totals[0][1] > WINNING_POST) {
      /* winner found with a majority vote */
      foundWinner = true;
      /* skip sorting at end */
      lastLoser = 0;    
    }
      
    else  { /* a tie or no winning majority found */

      if(firstLoser == NUM_CAND)          
        choice++; /* go to next choice candidate on losers ballots */

      if(firstLoser >= 0) {
        /* we need loser pointers for last sort */
        lastLoser = --firstLoser; /* set end marker of loser range */
        firstLoser = findLoser(firstLoser);/* find start of next loser batch */             
      }
                  
/*printf("%d %d %d\n", firstLoser, lastLoser, choice);      */
    } 
  }

  sortTotals(lastLoser);  /* final sort, only sort winner and tied winners */
  printTotals();  /* debug */
  printWinner();
  
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ cc -o voting voting.c 
osman@osman-desktop:~/src/challenges$ ./voting 
#define NUM_BALLOTS 5
static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, 
  {0, 1, 2}, {2, 0, 1}};
John Doe: 3
Jane Smith: 2
Jane Austen: 1
And the winner(s) is(are) John Doe

#define NUM_BALLOTS 6
static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, 
  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}};
osman@osman-desktop:~/src/challenges$ ./voting 
John Doe: 4
Jane Smith: 3
Jane Austen: 1
And the winner(s) is(are) John Doe

#define NUM_BALLOTS 6
static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 2, 1}, {1, 0, 2}, {1, 2, 0}, 
  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}};
osman@osman-desktop:~/src/challenges$ ./voting 
Jane Smith: 4
John Doe: 4
Jane Austen: 1
And the winner(s) is(are) Jane Smith
And the winner(s) is(are) John Doe
  
#define NUM_BALLOTS 7
static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, 
  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}, {1, 0, 2}};
osman@osman-desktop:~/src/challenges$ ./voting 
Jane Smith: 4
John Doe: 2
Jane Austen: 1
And the winner(s) is(are) Jane Smith

#define NUM_BALLOTS 8
static int ballots[NUM_BALLOTS][NUM_CAND] = {{0, 2, 1}, {1, 0, 2}, {1, 2, 0}, 
  {0, 1, 2}, {2, 0, 1}, {1, 0, 2}, {0, 2, 1}, {2, 1, 0}};
osman@osman-desktop:~/src/archive/challenges$ ./voting 
John Doe: 6
Jane Smith: 5
Jane Austen: 2
And the winner(s) is(are) John Doe

*/
