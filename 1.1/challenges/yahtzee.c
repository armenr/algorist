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

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

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

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

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
    return true;   
    
  return false;
}

static bool haveSameRank(int t[], int start, int end) {
  /* ensure throw is sorted */
  int i;

  for(i = start; i <= end-1; i++)
    if(t[i] != t[i+1])
      return false;

  return true;
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
  if(i == NOT_FOUND) return false;

  int j;
  /* pair must be at 0..1 or 3..4 if three cards found */
  if(i == 0)
    j = 3;
  else if(i == 2)
    j = 0;
  else
    return false;

  if(hasPair(t, j) != NOT_FOUND)
    return true;      
  else
    return false;  
}

static bool isStraight(int t[], int l) {
  /* ensure throw is sorted */
  int i, j = 0;
  
  for(i = 0; i <= DICE-l; i++) {
    int rank = t[i];     
    bool found;

    found = true;  
    
    for(j = i+1; j < (l+i); j++)
      if(t[j] != rank+j) 
        found = false;
        
    if(found)     
      return true;
  }
  
  return false;
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
  category_found[category] = true;
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
  int throw, oldthrow, score,
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
j = 0; 
  if(bonus > BONUS_THRESHOLD) {
    j++;  /*can we pick a lower total for each number and still make bonus?*/
    for(i = TOTALS-2; i >= TOTALS-2; i--) { 
      sortGameTotals(i);  
/*      printSortedGame();*/
      throw = game_totals[j][0];
      oldthrow = game_totals[j-1][0]; 
      printf("%d: ", i);
      printThrow(game[throw]);
      score = scoreNumber(throw, i); 
      int delta = scoreNumber(oldthrow, i) - score;       
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
    category_found[i] = false;
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

