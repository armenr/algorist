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
1.6.2    Minesweeper
PC/UVa IDs: 110102/10189, Popularity: A, Success rate: high Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input                                Sample Output

4 4                                         Field #1:
*...                                        *100
....                                        2210
.*..                                        1*10
....                                        1110
3 5
**...                                       Field #2:
.....                                       **100
.*...                                       33200
                                            1*100
0 0
*/

#include<stdio.h>
#include<stdlib.h>

#define N 3
#define M 5
#define MINE -1

/*
* a 2d array (n rows by m cols) to hold field, initialised to zeros
  allowable values for each cell:
    >= 0 in the array indicates that the cell (y, x) [where 0 <= y < n and 
    0 <= x < m] is adjacent to that many number of mines
    -1 indicates a mine
    (the theoretical max value for a cell should be n.m - 1)
*/
static int field[N][M];

/*    
* a linked list holding the (y, x) co-ords of each mine to speed up processing
*/
typedef struct {
  int y, x;
  struct mine *next;
} mine;

static mine *m = NULL;

/* list operations */
static void clear_list(mine **m) {
  mine *p;
  
  while(*m != NULL) {
    p = *m;
    *m = p->next;
    free(p);
  }
}

static void insert_list(mine **m, int y, int x) {
	mine *p;			/* temporary pointer */

	p = malloc( sizeof(mine) );
	p->x = x; p->y = y;
	p->next = *m;
	*m = p;
}

static void initialiseField(void) {
  int x, y;
  
  for(y = 0; y < N; y++)  
    for(x = 0; x < M; x++)
      field[y][x] = 0;
}

static void populateField(void) {
  /* populate field:
    * when a mine is found then add it to mine list
    * set field position for mine to -1
  */
  /* add sample mines
  **...                                       Field #2:
  .....                                       **100
  .*...                                       33200
                                              1*100
  */ 
  field[0][0] = MINE; field[0][1] = MINE; field[2][1] = MINE;
  insert_list(&m, 0, 0); insert_list(&m, 0, 1); insert_list(&m, 2, 1);
}

static void printField(void) {
  int cell, x, y;
  
  for(y = 0; y < N; y++) {
    for(x = 0; x < M; x++) {
      cell = field[y][x];
      
      if(cell != -1) 
        printf("%d", cell);
      else
        printf("*");  /* mine */     
    }
    printf("\n");
  }  
}

static void processMines(void) {
  int firstY, lastY, firstX, lastX, y, x;
  mine *list = m;
  
  while(list != NULL) {
    
    /* find all adjacent cells in field array using (y, x) co-ords
      * adjacent cells will range from y-1 to y+1 and x-1 to x+1
      * where y-1 >= 0 and y+1 < n and x-1 >= 0 and x+1 < m 
    */

    y = list->y; x = list->x;   /* mine co-ords */

    if((y - 1) < 0)
      firstY = 0;
    else
      firstY = y - 1;

    if((y + 1) > (N - 1))
      lastY = N - 1;
    else
      lastY = y + 1;

    if((x - 1) < 0)
      firstX = 0;
    else
      firstX = x - 1;

    if((x + 1) > (M - 1))
      lastX = M - 1;
    else
      lastX = x + 1;

    /* for each adjacent cell, if it isn't a mine increase it's value by 1 */
    for(y = firstY; y <= lastY; y++)
      for(x = firstX; x <= lastX; x++)
        if(field[y][x] != MINE) 
          field[y][x]++;
    
    list = list->next;
  }
  list = NULL;
  clear_list(&m);
}

int main(void) {
  initialiseField();
  populateField();        
  processMines();
  printField();    
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./mine 
**100
33200
1*100

osman@osman-desktop:~/src/challenges$ ./mine 
*100
2210
1*10
1110
*/
