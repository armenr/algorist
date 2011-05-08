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
2.8.2    Poker Hands
PC/UVa IDs: 110202/10315, Popularity: C, Success rate: average Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

2H  3D 5S  9C  KD  2C 3H  4S  8C   AH
2H  4S 4C  2D  4H  2S 8S  AS  QS   3S
2H  3D 5S  9C  KD  2C 3H  4S  8C   KH
2H  3D 5S  9C  KD  2D 3H  5C  9S   KH

Sample Output

White wins.
Black wins.
Black wins.
Tie.
*/

#include<stdbool.h>
#include<stdio.h>

#define NOT_FOUND -1
#define RANKS 13
#define SIZE 5

typedef struct {
  char rank;
  int num;  /* translation of char rank to ordinal */
} rankNum;

typedef struct {
  char rank;
  char suit; /* one of 'h', 's', 'd' or 'c' */
  int num;
} card;

rankNum ranks[] = {{'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, 
  {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};

/*card black[] = {{'2', 'H'}, {'3', 'D'}, {'5', 'S'}, {'9', 'C'}, {'K', 'D'}};*/
/*card white[] = {{'2', 'C'}, {'3', 'H'}, {'4', 'S'}, {'8', 'C'}, {'A', 'H'}};*/
/*card black[] = {{'2', 'H'}, {'4', 'S'}, {'4', 'C'}, {'2', 'D'}, {'4', 'H'}};*/
/*card white[] = {{'2', 'S'}, {'8', 'S'}, {'A', 'S'}, {'Q', 'S'}, {'3', 'S'}};*/
/*card black[] = {{'2', 'H'}, {'3', 'D'}, {'5', 'S'}, {'9', 'C'}, {'K', 'D'}};*/
/*card white[] = {{'2', 'C'}, {'3', 'H'}, {'4', 'S'}, {'8', 'C'}, {'K', 'H'}};*/
card black[] = {{'2', 'H'}, {'3', 'D'}, {'5', 'S'}, {'9', 'C'}, {'K', 'D'}};
card white[] = {{'2', 'D'}, {'3', 'H'}, {'5', 'C'}, {'9', 'S'}, {'K', 'H'}};


static void printHand(card hand[]) {
  int i;
  
  for(i = 0; i < SIZE; i++)
    printf("%c %c %d ", hand[i].rank, hand[i].suit, hand[i].num);
  printf("\n");
}

static void rankHand(card hand[]) {
  int i, j;
  
  for(i = 0; i < SIZE; i++)
    for(j = 0; j < RANKS; j++) {
      if(hand[i].rank == ranks[j].rank) {
        hand[i].num = ranks[j].num;
        break; 
      }   
    }
}

static void sortHand(card hand[]) {
	int i, j;
	card c;
	
  /* insertion sort, replace with quicksort for large N */
	for(i = 1; i < SIZE; i++) {
	  j = i;
	  while((j > 0) && (hand[j].num > hand[j-1].num)) {
	    /* swap function */
	    c = hand[j]; hand[j] = hand[j-1]; hand[j-1] = c;
		  j--;
	  }
	}
}

/* determine if cards in range have same value */
static bool haveSameRank(card hand[], int start, int end) {
  /* ensure hand is sorted */
  int i;

  for(i = start; i <= end-1; i++)
    if(hand[i].num != hand[i+1].num)
      return false;

  return true;
}

/*
High Card. Hands which do not fit any higher category are ranked by the value of
their highest card. If the highest cards have the same value, the hands 
are ranked by the next highest, and so on.
*/
static int highCard(card hand[]) {
  /* ensure hand is sorted */
  return hand[0].num;
}

/*
Pair. Two of the five cards in the hand have the same value. Hands which both 
contain a pair are ranked by the value of the cards forming the pair. If 
these values are the same, the hands are ranked by the values of the cards 
not forming the pair, in decreasing order.
*/
static int hasPair(card hand[], int start) {
  /* ensure hand is sorted */
  int i;
  
  for(i = start; i < SIZE-1; i++)
    if(haveSameRank(hand, i, i+1)) 
      return i;

  return NOT_FOUND;
}

/*
Two Pairs. The hand contains two different pairs. Hands which both contain two 
pairs are ranked by the value of their highest pair. Hands with the same 
highest pair are ranked by the value of their other pair. If these values 
are the same the hands are ranked by the value of the remaining card.
*/
static bool hasTwoPairs(card hand[]) {
  /* ensure hand is sorted */
  int i = hasPair(hand, 0);
  
  /* find 1st pair */
  if(i == NOT_FOUND || i == 3) 
    return false;

  /* find 2nd pair */
  if(hasPair(hand, i+2) == NOT_FOUND) 
    return false;

  return true;
}

/*
Three of a Kind. Three of the cards in the hand have the same value. Hands which
both contain three of a kind are ranked by the value of the three cards.
*/
static int hasThree(card hand[]) {
  /* ensure hand is sorted */
  int i;
  
  for(i = 0; i < SIZE-2; i++)
    if(haveSameRank(hand, i, i+2)) 
      return i;

  return NOT_FOUND;
}

/*
Straight. Hand contains five cards with consecutive values. Hands which both 
contain  straight are ranked by their highest card.
*/
static bool isStraight(card hand[]) {
  /* ensure hand is sorted */
  int i;
  int rank = hand[0].num;

  for(i = 1; i < SIZE; i++)
    if(hand[i].num != rank-i ) 
      return false;

  return true;
}

/*
Flush. Hand contains five cards of the same suit. Hands which are both flushes 
are ranked using the rules for High Card.
*/
static bool isFlush(card hand[]) {
  /* ensure hand is sorted */
  int i;
  char suit = hand[0].suit;  

  for(i = 1; i < SIZE; i++)
    if(hand[i].suit != suit) 
      return false;

  return true;
}

/*
Full House. Three cards of the same value, with the remaining two cards forming 
a pair. Ranked by the value of the three cards.
*/
static bool isFullHouse(card hand[]) {
  /* ensure hand is sorted */
  int i = hasThree(hand); 
  if(i == NOT_FOUND) return false;

  int j;
  /* pair must be at 0..1 or 3..4 if three cards found */
  if(i == 0)
    j = 3;
  else if(i == 2)
    j = 0;
  else
    return false;

  if(hasPair(hand, j) != NOT_FOUND)
    return true;      
  else
    return false;  
}

/*
Four of a Kind. Four cards with the same value. Ranked by the value of the four
cards.
*/
static bool isFourKind(card hand[]) {
  /* ensure hand is sorted */
  if(hand[0].num == hand[SIZE-2].num)
    return true;
  else if(hand[1].num == hand[SIZE-1].num)
    return true;
  else
    return false;    
}

/*
Straight Flush. Five cards of the same suit with consecutive values. Ranked by 
the highest card in the hand.
*/
static bool isStraightFlush(card hand[]) {
  if(isStraight(hand) && isFlush(hand)) 
    return true;
  else
    return false;    
}

static void printWinner(int bh, int wh) {
  if(bh > wh)
    printf("black wins\n");
  else if(wh > bh)
    printf("white wins\n");
  else
    printf("tie\n");
}

static bool findWinner(bool b, bool w, int bh, int wh) {
  if(b && w) 
    printWinner(bh, wh);
  else if(b) 
    printf("black wins\n");
  else if(w) 
    printf("white wins\n");  
  else
    return false;      

  return true;    
}

static void findHighCardWinner(void) {
  int i, bh, wh;
  for(i = 0; bh = black[i].num, wh = white[i].num, i < SIZE-1; i++)
    if(bh > wh) {
      printf("black wins\n");
      return;    
    } else if(wh > bh) {
      printf("white wins\n");
      return;       
    } 

  printf("tie\n");
}

static void getWinner(void) {
  int bh = highCard(black), wh = highCard(white);  
  bool b, w; /* type of hand */

  b = isStraightFlush(black); w = isStraightFlush(white);   
  if(findWinner(b, w, bh, wh))
    return;

  b = isFourKind(black); w = isFourKind(white);   
  if(findWinner(b, w, bh, wh))
    return;

  b = isFullHouse(black); w = isFullHouse(white);   
  if(findWinner(b, w, bh, wh))
    return;

  b = isFlush(black); w = isFlush(white);   
  if(findWinner(b, w, bh, wh))
    return;

  b = isStraight(black); w = isStraight(white);   
  if(findWinner(b, w, bh, wh))
    return;

  b = hasThree(black); w = hasThree(white);  
  if(findWinner((b != NOT_FOUND ? true : false), 
                (w != NOT_FOUND ? true : false),
                bh, wh))
    return;

  b = hasTwoPairs(black); w = hasTwoPairs(white);   
  if(findWinner(b, w, bh, wh))
    return;

  b = hasPair(black, 0); w = hasPair(white, 0);  
  if(findWinner((b != NOT_FOUND ? true : false), 
                (w != NOT_FOUND ? true : false),
                bh, wh))
    return;

  /* high card */
  findHighCardWinner();
}

void main(void) {
  rankHand(black); sortHand(black); printf("black:\n"); printHand(black);       
  rankHand(white); sortHand(white); printf("white:\n"); printHand(white);       
  getWinner();    
}

/* test runs 
osman@osman-desktop:~/src/challenges$ ./poker-hands 
black:
K D 13 9 C 9 5 S 5 3 D 3 2 H 2 
white:
A H 14 8 C 8 4 S 4 3 H 3 2 C 2 
white wins
osman@osman-desktop:~/src/challenges$ ./poker-hands 
black:
4 S 4 4 C 4 4 H 4 2 H 2 2 D 2 
white:
A S 14 Q S 12 8 S 8 3 S 3 2 S 2 
black wins
osman@osman-desktop:~/src/challenges$ ./poker-hands 
black:
K D 13 9 C 9 5 S 5 3 D 3 2 H 2 
white:
K H 13 8 C 8 4 S 4 3 H 3 2 C 2 
black wins
osman@osman-desktop:~/src/challenges$ ./poker-hands 
black:
K D 13 9 C 9 5 S 5 3 D 3 2 H 2 
white:
K H 13 9 S 9 5 C 5 3 H 3 2 D 2 
tie
*/
