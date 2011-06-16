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
2.8.1     Jolly Jumpers
PC/UVa IDs: 110201/10038, Popularity: A, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

4 1 4 2 3
5 1 4 2 -1 6

Sample Output

Jolly
Not jolly
*/

#include<math.h>
#include<stdbool.h>
#include<stdio.h>

/*static int sequence[] = {1};*/
/*static int sequence[] = {1, 2};*/
/*static int sequence[] = {1, 2, 3};*/
/*static int sequence[] = {1, 4, 2, 3}; */
/* note, no 3! */
/*static int sequence[] = {1, 2, 4, 1}; */
/*static int sequence[] = {-4, 3, -2, 1}; */
/*static int sequence[] = {4, 1, 4, 2, 3};*/

static int sequence[] = {5, 1, 4, 2, -1, 6};
#define SIZE (int)(sizeof(sequence) / sizeof(sequence[0]))

int main(void) {
  int i, n = 1;
  bool isJolly = true;

  /* find max in sequence, so we can determine N */
 for(i = 0; i < SIZE; i++)   
  if(sequence[i] > n)
    n = sequence[i];

  if(n > 1) {
    bool members[n-1]; /* range is 0 to n-2 inclusive */
    
    /* initally there are no members found */
    for(i = 0; i < n-1; i++)
      members[i] = false;

    int diff;
    /* populate members */ 
    for(i = 1; i < SIZE; i++) {
      diff = abs(sequence[i] - sequence[i-1]);
      members[diff-1] = true; /* for 0 based array subtract 1 */
    }

    /* have we found all jollies? */        
    for(i = 0; i < n-1; i++)
      if(members[i] == false) {
        isJolly = false;
        break;
      } 
  }
    
  for(i = 0; i < SIZE; i++) 
    printf("%d ", sequence[i]);
    
  if(isJolly)        
    printf("is jolly\n");
  else
    printf("isn't jolly\n");   
    
  return 0;    
}

/* test runs 
static int sequence[] = {1};
osman@osman-desktop:~/src/challenges$ ./jolly 
1 is jolly

static int sequence[] = {1, 2};
osman@osman-desktop:~/src/challenges$ ./jolly 
1 2 is jolly

static int sequence[] = {1, 2, 3};
osman@osman-desktop:~/src/challenges$ ./jolly 
1 2 3 isn't jolly

static int sequence[] = {1, 4, 2, 3}; 
osman@osman-desktop:~/src/challenges$ ./jolly 
1 4 2 3 is jolly

static int sequence[] = {1, 2, 4, 1}; 
osman@osman-desktop:~/src/challenges$ ./jolly 
1 2 4 1 is jolly

static int sequence[] = {-4, 3, -2, 1}; 
osman@osman-desktop:~/src/challenges$ ./jolly 
-4 3 -2 1 isn't jolly

static int sequence[] = {4, 1, 4, 2, 3};
osman@osman-desktop:~/src/challenges$ ./jolly 
4 1 4 2 3 is jolly

static int sequence[] = {5, 1, 4, 2, -1, 6};
osman@osman-desktop:~/src/challenges$ ./jolly 
5 1 4 2 -1 6 isn't jolly
*/
