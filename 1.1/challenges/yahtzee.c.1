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
2.8.8 Yahtzee

PC/UVa IDs: 110208/10149, Popularity: C, Success rate: average Level: 3

The game of Yahtzee involves five dice, which are thrown in 13 rounds. A score 
card contains 13 categories. Each round may be scored in a category of the 
player’s choosing, but each category may be scored only once in the game. The 
13 categories are scored as follows:

• ones - sum of all ones thrown
• twos - sum of all twos thrown
• threes - sum of all threes thrown
• fours - sum of all fours thrown
• fives - sum of all fives thrown
• sixes - sum of all sixes thrown
• chance - sum of all dice
• three of a kind - sum of all dice, provided at least three have same value
• four of a kind - sum of all dice, provided at least four have same value
• five of a kind - 50 points, provided all five dice have same value
• short straight - 25 points, provided four of the dice form a sequence (that is,
1,2,3,4 or 2,3,4,5 or 3,4,5,6)
• long straight - 35 points, provided all dice form a sequence 
(1,2,3,4,5 or 2,3,4,5,6)
• full house - 40 points, provided three of the dice are equal and the other two
dice are also equal. (for example, 2,2,5,5,5)

Each of the last six categories may be scored as 0 if the criteria are not met.
The score for the game is the sum of all 13 categories plus a bonus of 35 points 
if the sum of the first six categories is 63 or greater.

Your job is to compute the best possible score for a sequence of rounds.

Input

Each line of input contains five integers between 1 and 6, indicating the 
values of the five dice thrown in each round. There are 13 such lines for each 
game, and there may be any number of games in the input data.

Output

Your output should consist of a single line for each game containing 15 
numbers: the score in each category (in the order given), the bonus score 
(0 or 35), and the total score. If there is more than categorization that 
yields the same total score, any one will do.

Sample Input

1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5


1 1 1 1 1
6 6 6 6 6
6 6 6 1 1
1 1 1 2 2
1 1 1 2 3
1 2 3 4 5
1 2 3 4 6
6 1 2 6 6
1 4 5 5 5
5 5 5 5 6
4 4 4 5 6
3 1 3 6 3
2 2 2 4 6

Sample Output

1 2 3 4 5 0 15 0 0 0 25 35 0 0 90
3 6 9 12 15 30 21 20 26 50 25 35 40 35 327
*/

#include "bool.h"
#include <stdio.h>
#include <stdlib.h>

#define CATEGORIES_NUM 13
#define DICE 5
#define TOTALS 8 /*arranged by index, one, two, three, four, five, six, all*/
#define NOT_FOUND -1
#define BONUS_THRESHOLD 63
#define BONUS_SCORE 35

static int game[CATEGORIES_NUM][DICE] = {{1, 1, 1, 1, 1}, {6, 6, 6, 6, 6}, 
  {6, 6, 6, 1, 1}, {1, 1, 1, 2, 2}, {1, 1, 1, 2, 3}, {1, 2, 3, 4, 5}, 
  {1, 2, 3, 4, 6}, {6, 1, 2, 6, 6}, {1, 4, 5, 5, 5}, {5, 5, 5, 5, 6}, 
  {4, 4, 4, 5, 6}, {3, 1, 3, 6, 3}, {2, 2, 2, 4, 6}};

static int game_totals[CATEGORIES_NUM][TOTALS];
static int compare_column = 0;  /*have to make this module level for qsort*/  

static bool category_found[CATEGORIES_NUM]; /*index positions below*/
#define ONES 0
#define TWOS 1
#define THREES 2
#define FOURS 3
#define FIVES 4
#define SIXES 5
#define CHANCE 6
#define THREE_OF_A_KIND 7
#define FOUR_OF_A_KIND 8
#define FIVE_OF_A_KIND 9 
#define SHORT_STRAIGHT 10
#define LONG_STRAIGHT 11
#define FULL_HOUSE 12

/*index positions above*/
static int points[CATEGORIES_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 25, 35, 40}; 
static int score = 0;

static void printGame(void) {
  int i, j;

  for(i = 0; i < CATEGORIES_NUM; i++) {
    for(j = 0; j < DICE; j++) 
	    printf("%d ", game[i][j]);
    printf("\n");
  }
}

static void printSortedGame(void) {
  int i, j;

  for(i = 0; i < CATEGORIES_NUM; i++) {
    for(j = 0; j < DICE; j++) 
      printf("%d ", game[game_totals[i][0]][j]);
    printf("\n");
  }
}

static void printGameTotals(void) {
  int i, j;

  for(i = 0; i < CATEGORIES_NUM; i++) {
    for(j = 0; j < TOTALS; j++) 
      printf("%d ", game_totals[i][j]);   
    printf("\n");   
  }    
}

static void printThrow(int t[]) {
  int i;

  for(i = 0; i < DICE; i++)
    printf("%d ", t[i]);
  printf("\n");
}

static int compareDice(const int *x, const int *y) {
  int xv = *x, yv = *y;
  
	if(xv < yv) 
	  return -1;
	else if(xv > yv) 
	  return 1;

	return 0;
}

static int compareTotals(const int x[], const int y[]) {
  /*in descending order*/
  if(x[compare_column] > y[compare_column]) 
    return -1;
  else if(x[compare_column] < y[compare_column]) 
    return 1;

	return 0;
}

static int compareThrows(const int x[], const int y[]) {
  int i;
  
  for(i = 0; i < DICE; i++)
	  if(x[i] < y[i]) 
	    return -1;
	  else if(x[i] > y[i]) 
	    return 1;

	return 0;
}

static void sortGame(void) {
  int i;
  
  for(i = 0; i < CATEGORIES_NUM; i++)
	  qsort(&game[i], DICE, sizeof(int), compareDice);
	  
  qsort(&game, CATEGORIES_NUM, sizeof(int) * DICE, compareThrows);
}

static void sortGameTotals(int n) {
  compare_column = n; /*only set here*/
  qsort(&game_totals, CATEGORIES_NUM, sizeof(int) * TOTALS, compareTotals);
}

static void addUpTotals(void) {
  int i, j;

  for(i = 0; i < CATEGORIES_NUM; i++) {
    game_totals[i][0] = i;

    for(j = 1; j < TOTALS; j++) 
      game_totals[i][j] = 0;
    
    for(j = 0; j < DICE; j++) {
      int d = game[i][j];
      game_totals[i][d] += d;
      game_totals[i][TOTALS-1] += d;  /*all*/
    }
    
/*    for(j = 0; j < TOTALS; j++) */
/*      printf("%d ", game_totals[i][j]);   */
/*    printf("\n");   */
  }
}

/* null out entry so we can process variable scores only*/
static void clearThrow(int i) {
  int j = 0;
  for(j = 0; j < DICE; j++)
    game[i][j] = 0;
}

static int isOfaKind(int t[], int q) {
/*   ensure throw is sorted */
  if(t[0] == t[q-1]) 
    return TRUE;   
    
  return FALSE;
}

static bool haveSameRank(int t[], int start, int end) {
  /* ensure throw is sorted */
  int i;

  for(i = start; i <= end-1; i++)
    if(t[i] != t[i+1])
      return FALSE;

  return TRUE;
}

static int hasNumber(int t[], int n) {
  /* ensure throw is sorted */
  int i, s = 0;
  
  for(i = 0; i < DICE; i++)
    if(t[i] == n)
      s += n;
  return s; /*sum of all found*/
}

static int hasPair(int t[], int start) {
  /* ensure throw is sorted */
  int i;
  
  for(i = start; i < DICE-1; i++)
    if(haveSameRank(t, i, i+1)) 
      return i;

  return NOT_FOUND;
}

static int hasThree(int t[]) {
  /* ensure throw is sorted */
  int i;
  
  for(i = 0; i < DICE-2; i++)
    if(haveSameRank(t, i, i+2)) 
      return i;

  return NOT_FOUND;
}

static bool isFullHouse(int t[]) {
  /* ensure throw is sorted */
  int i = hasThree(t); 
  if(i == NOT_FOUND) return FALSE;

  int j;
  /* pair must be at 0..1 or 3..4 if three cards found */
  if(i == 0)
    j = 3;
  else if(i == 2)
    j = 0;
  else
    return FALSE;

  if(hasPair(t, j) != NOT_FOUND)
    return TRUE;      
  else
    return FALSE;  
}

static bool isStraight(int t[], int l) {
  /* ensure throw is sorted */
  int i, j = 0;
  
  for(i = 0; i <= DICE-l; i++) {
    int rank = t[i];     
    bool found;

    found = TRUE;  
    
    for(j = i+1; j < (l+i); j++)
      if(t[j] != rank+j) 
        found = FALSE;
        
    if(found)     
      return TRUE;
  }
  
  return FALSE;
}

static int scoreNumber(int throw, int n) {
  int i, s = 0;
  for(i = 0; i < DICE; i++) 
    if(game[throw][i] == n)
      s += n;
  return s;
}

static void scoreThrow(int category, int throw) {
  if(category >= FIVE_OF_A_KIND)
    score += points[category];
  else
    score += scoreNumber(throw, category+1);
    
  printf("Score is now: %d\n", score);
  category_found[category] = TRUE;
  clearThrow(throw);    
}

static void findFixedScores(void) {
/*ensure totals sorted first*/
  int i;
  for(i = 0; i < CATEGORIES_NUM; i++) {
    int g = game[i];
    
    if(!category_found[FIVE_OF_A_KIND] && isOfaKind(g, 5)) {
      printf("five of a kind: ");
      printThrow(g);
      scoreThrow(FIVE_OF_A_KIND, i);
    } else if(!category_found[FULL_HOUSE] && isFullHouse(g)) {
      printf("full house: ");
      printThrow(g);
      scoreThrow(FULL_HOUSE, i);
    } else if(!category_found[LONG_STRAIGHT] && isStraight(g, DICE)) {
      printf("long straight: ");
      printThrow(g);
      scoreThrow(LONG_STRAIGHT, i);
    } else if(!category_found[SHORT_STRAIGHT] && isStraight(g, DICE-1)) {
      printf("short straight: ");
      printThrow(g);
      scoreThrow(SHORT_STRAIGHT, i);
    }
  }
}

  
static void findVariableScores(void) {
  int throw, oldthrow, 
    i, j = 0, 
    bonus = 0;  /*j = 0, 1, 2 ... order of decreasing number totals*/

  for(i = TOTALS-2; i > 0; i--) { 
    sortGameTotals(i);  
    throw = game_totals[j][0];
    printf("%d: ", i);
    printThrow(game[throw]);
    bonus += scoreNumber(throw, i);
/*    printGameTotals();*/
/*    printf("\n");*/
/*    printSortedGame();*/
  }
printf("bonus is %d\n", bonus);  
  if(bonus > BONUS_THRESHOLD) {
    j++;  /*can we pick a lower total for each number and still make bonus?*/
    for(i = TOTALS-2; i >= TOTALS-2; i--) { 
      sortGameTotals(i);  
/*      printSortedGame();*/
      throw = game_totals[j][0];
      oldthrow = game_totals[j-1][0];
      printf("%d: ", i);
      printThrow(game[throw]);
      int delta = scoreNumber(oldthrow, i) - scoreNumber(throw, i);       
printf("delta is %d\n", delta);  
      if(bonus - delta > BONUS_THRESHOLD) {
        scoreThrow(i-1, throw);
        bonus -= delta;
      }
      else
        scoreThrow(i-1, oldthrow);
    }    
  }   
printf("bonus is %d\n", bonus);  
  
/*#define BONUS_SCORE 35*/
  
}

static void initFound(void) {
  int i;
  for(i = 0; i < CATEGORIES_NUM; i++) 
    category_found[i] = FALSE;
}

int main(void) {
  initFound();
  sortGame();
  printGame();
  findFixedScores();
  printGame();
  addUpTotals();
  findVariableScores();
  printGame();
  return 0;
}

/* test runs
*/

