/*see README for original credits */

#include <stdlib.h> 
#include <stdio.h>

struct player {
  int key;
  struct player *next;
};


int main(void) {
  printf(
  "Solve the Josephus problem for an arbitrary number of players and an \n"
  "arbitrary choice of count. The last output will be the number of the \n"
  "surviving player.\n\n");


  int n, m; 
  printf("number of players (n): ");
  scanf("%d", &n);

  printf("number of players you want to miss before execution (m): ");
  scanf("%d", &m);

  struct player *firstPlayer, *currentPlayer, *victim; 

  firstPlayer = currentPlayer = 
    (struct player *) malloc(sizeof(struct player));

  currentPlayer->key = 1; 

  int i;
  for(i = 2; i <= n; i++) {
    currentPlayer->next = 
      (struct player *) malloc(sizeof(struct player));

    currentPlayer = currentPlayer->next; 
    currentPlayer->key = i; 
  }

  currentPlayer->next = firstPlayer;

  /*Loop over n, counting up one every time a player dies*/
  while(currentPlayer != currentPlayer->next) {

    /*Cycle through players until the one just before the unlucky one is 
      reached*/
    for( i = 1; i < m; i++) currentPlayer = currentPlayer->next;

    /*Victim is the player just after the current player*/
    victim = currentPlayer->next;

    /*Set the current player to point at the space just after where the victim 
      was*/
    currentPlayer->next = victim->next;

    /*Set space now pointed to by victim free*/
    printf("%d ", victim->key);
    free(victim);
  }

  printf("\nsurvivor is %d\n", currentPlayer->key);
  free(currentPlayer);
  return 0;
} 
