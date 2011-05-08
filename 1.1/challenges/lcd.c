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
1.6.4     LCD Display
PC/UVa IDs: 110104/706, Popularity: A, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input                                Sample Output

2 12345                                    --   --        --
3 67890                                 |    |    | |  | |
0 0                                     |    |    | |  | |
                                           --   --   --   --
                                        | |       |    |    |
                                        | |       |    |    |
                                           --   --        --
*/

#include<stdbool.h>
#include<stdio.h>

/*s display size*/
#define SIZE 3
#define MIDDLE SIZE + 1

static char digits[10][2 * SIZE + 3][SIZE + 2];  /* (rows, cols) */

static void horizontal(int s, int number, int row) {
  int i;
  digits[number][row][0] = ' ';
  for(i = 1; i <= s; i++)
    digits[number][row][i] = '-'; 
  digits[number][row][s + 1] = ' ';
}
  
static void space(int s, int number, int row) {
  int i;
  for(i = 0; i <= (s + 1); i++)
    digits[number][row][i] = ' '; 
}

static void vertical(int s, int number, int row, bool first, bool last) {
  int i;
  
  if(first == true) {
    digits[number][row][0] = '|';
    for(i = 1; i <= (s + 1); i++)
      digits[number][row][i] = ' ';  
  }
  else
    digits[number][row][0] = ' ';
      
  if(last == true) {
    for(i = 1; i < (s + 1); i++)
      digits[number][row][i] = ' '; 
    digits[number][row][s + 1] = '|';
  }
}

static void zero(int s, int m) {
  int i;
  
  horizontal(s, 0, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 0, (1 + i), true, true); 
  space(s, 0, m);
  for(i = 0; i < s; i++) 
    vertical(s, 0, (m + 1 + i), true, true); 
  horizontal(s, 0, (2 * s + 2)); 
}

static void one(int s, int m) {
  int i;
  
  space(s, 1, 0);
  for(i = 0; i < s; i++) 
    vertical(s, 1, (1 + i), false, true); 
  space(s, 1, m);
  for(i = 0; i < s; i++) 
    vertical(s, 1, (m + 1 + i), false, true); 
  space(s, 1, (2 * s + 2));
}

static void two(int s, int m) {
  int i;
  
  horizontal(s, 2, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 2, (1 + i), false, true); 
  horizontal(s, 2, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 2, (m + 1 + i), true, false); 
  horizontal(s, 2, (2 * s + 2)); 
}

static void three(int s, int m) {
  int i;
  
  horizontal(s, 3, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 3, (1 + i), false, true); 
  horizontal(s, 3, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 3, (m + 1 + i), false, true); 
  horizontal(s, 3, (2 * s + 2)); 
}

static void four(int s, int m) {
  int i;
  
  space(s, 4, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 4, (1 + i), true, true); 
  horizontal(s, 4, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 4, (m + 1 + i), false, true); 
  space(s, 4, (2 * s + 2)); 
}

static void five(int s, int m) {
  int i;
  
  horizontal(s, 5, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 5, (1 + i), true, false); 
  horizontal(s, 5, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 5, (m + 1 + i), false, true); 
  horizontal(s, 5, (2 * s + 2)); 
}

static void six(int s, int m) {
  int i;
  
  horizontal(s, 6, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 6, (1 + i), true, false); 
  horizontal(s, 6, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 6, (m + 1 + i), true, true); 
  horizontal(s, 6, (2 * s + 2)); 
}

static void seven(int s, int m) {
  int i;
  
  horizontal(s, 7, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 7, (1 + i), false, true); 
  space(s, 7, m);
  for(i = 0; i < s; i++) 
    vertical(s, 7, (m + 1 + i), false, true); 
  space(s, 7, (2 * s + 2));
}

static void eight(int s, int m) {
  int i;
  
  horizontal(s, 8, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 8, (1 + i), true, true); 
  horizontal(s, 8, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 8, (m + 1 + i), true, true); 
  horizontal(s, 8, (2 * s + 2)); 
}

static void nine(int s, int m) {
  int i;
  
  horizontal(s, 9, 0); 
  for(i = 0; i < s; i++) 
    vertical(s, 9, (1 + i), true, true); 
  horizontal(s, 9, m); 
  for(i = 0; i < s; i++) 
    vertical(s, 9, (m + 1 + i), false, true); 
  horizontal(s, 9, (2 * s + 2)); 
}


int main(void) {
  int size = SIZE, middle = MIDDLE;

  zero(size, middle);
  one(size, middle); 
  two(size, middle); 
  three(size, middle); 
  four(size, middle); 
  five(size, middle); 
  six(size, middle); 
  seven(size, middle); 
  eight(size, middle); 
  nine(size, middle); 

  int row, col, number;
  for(row = 0; row < (2 * size + 3); row++) {
    for(number = 0; number < 10; number++) {
      for(col = 0; col < (size + 2); col++) 
        printf("%c", digits[number][row][col]);    
      printf(" ");      
    } 
    printf("\n");
  }
  
  return 0;
}

/* test run
#define SIZE 2

osman@osman-desktop:~/src/challenges$ ./lcd
 --        --   --        --   --   --   --   --  
|  |    |    |    | |  | |    |       | |  | |  | 
|  |    |    |    | |  | |    |       | |  | |  | 
           --   --   --   --   --        --   --  
|  |    | |       |    |    | |  |    | |  |    | 
|  |    | |       |    |    | |  |    | |  |    | 
 --        --   --        --   --        --   --  

#define SIZE 3
 ---         ---   ---         ---   ---   ---   ---   ---  
|   |     |     |     | |   | |     |         | |   | |   | 
|   |     |     |     | |   | |     |         | |   | |   | 
|   |     |     |     | |   | |     |         | |   | |   | 
             ---   ---   ---   ---   ---         ---   ---  
|   |     | |         |     |     | |   |     | |   |     | 
|   |     | |         |     |     | |   |     | |   |     | 
|   |     | |         |     |     | |   |     | |   |     | 
 ---         ---   ---         ---   ---         ---   ---  
*/
