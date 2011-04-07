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
2.8.7 Contest Scoreboard
PC/UVa IDs: 110207/10258, Popularity: B, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input 

1

1 2 10 I
3 1 11 C
1 2 19 R
1 2 21 C
1 1 25 C

Sample Output

1 2 66
3 1 11

*/


#include<stdio.h>

#define CONTESTANTS 100
#define TOTAL_ENTRIES 5
#define PROBLEMS 9
#define PENALTY_CHARGE 20  /*for incorrect entries*/
#define PROCESSED -1    /* so we don't reprocess incorrect entries once charged*/

typedef struct {
  int contestant;
  int problem;
  int time;
  char status;
} entry;

typedef struct {
  int solved;
  int time;
} result;

/*
issues with data (that will impact processing)
  * what if there are duplicate correct entries (contestant and problem)?
  * what if incorrect entries follow correct entries (for contestant and problem)?
  * i'm sure there are more 
*/   
static entry entries[TOTAL_ENTRIES] = {{1, 2, 10, 'I'}, {3, 1, 11, 'C'}, {1, 2, 19, 'R'}, 
  {1, 2, 21, 'C'}, {1, 1, 25, 'C'}};

/*hashed on index = contestant no - 1*/
static int incorrect[CONTESTANTS][PROBLEMS];
static result results[CONTESTANTS];


int main(void) {

  /*initialise data*/
  int i = 0;

  for(i = 0; i < CONTESTANTS; i++) 
    results[i].solved = results[i].time = 0;

  /*process  */
  for(i = 0; i < TOTAL_ENTRIES; i++) {  
  
    int contestant = entries[i].contestant-1;
    int problem = entries[i].problem-1;
    char status = entries[i].status;
    
    switch (status) {
      /*assume, if any found, one correct submission for contestant and problem)*/
      case 'C': 
        results[contestant].solved++;
        results[contestant].time += entries[i].time;
  
        /*add any incorrect submissions, if any        */
        int wrong = incorrect[contestant][problem];
        if(wrong > 0) {
          results[contestant].time += (wrong * PENALTY_CHARGE);
          incorrect[contestant][problem] = PROCESSED;
        }
        break;
        
      case 'I': 
        if(results[contestant].solved != PROCESSED)
          incorrect[contestant][problem]++;
        break;
        
      default: ;
    }

  }

/*  print results;*/
  for(i = 0; i < CONTESTANTS; i++) 
    if(results[i].solved > 0)
      printf("%d %d %d \n", i+1, results[i].solved, results[i].time);
  
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./scoreboard 
1 2 66 
3 1 11 
*/
