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
3.8.5 Automated Judge Script
PC/UVa IDs: 110305/10188, Popularity: B, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 15
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is:  5
3
Input Set #1: YES
Input Set #2: NO
Input Set #3: NO
3
Input Set #0: YES
Input Set #1: NO
Input Set #2: NO
1
1 0 1 0
1
1010
1
The judges are mean!
1
The judges are good!
0

Sample Output

Run #1: Accepted
Run #2: Wrong Answer
Run #3: Presentation Error
Run #4: Wrong Answer
Run #5: Presentation Error
Run #6: Presentation Error
*/

#include"../ds/queue.h"
#include<ctype.h>
#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static queue q[2];

static void buildQueues(void) {
  int i;
  char *s;
  
  init_queue(&q[0]);
  init_queue(&q[1]);
	
  /*first queue fill*/
  i = 2;
  en_queue(&q[0], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[0], s, strlen(s));
  s = "The answer is: 5";
  en_queue(&q[0], s, strlen(s));
  
  en_queue(&q[0], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[0], s, strlen(s));
  s = "The answer is: 5";
  en_queue(&q[0], s, strlen(s));

  en_queue(&q[0], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[0], s, strlen(s));
  s = "The answer is:  5";
  en_queue(&q[0], s, strlen(s));

	i = 3;
  en_queue(&q[0], &i, sizeof(int));
  s = "Input Set #1: YES";
  en_queue(&q[0], s, strlen(s));
  s = "Input Set #2: NO";
  en_queue(&q[0], s, strlen(s));
  s = "Input Set #3: NO";
  en_queue(&q[0], s, strlen(s));

	i = 1;
  en_queue(&q[0], &i, sizeof(int));
  s = "1 0 1 0";
  en_queue(&q[0], s, strlen(s));

  en_queue(&q[0], &i, sizeof(int));
  s = "The judges are mean!";
  en_queue(&q[0], s, strlen(s));

  /*second queue fill*/
	i = 2;
  en_queue(&q[1], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[1], s, strlen(s));
  s = "The answer is: 5";
  en_queue(&q[1], s, strlen(s));
  
  en_queue(&q[1], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[1], s, strlen(s));
  s = "The answer is: 15";
  en_queue(&q[1], s, strlen(s));

  en_queue(&q[1], &i, sizeof(int));
  s = "The answer is: 10";
  en_queue(&q[1], s, strlen(s));
  s = "The answer is: 5";
  en_queue(&q[1], s, strlen(s));

	i = 3;
  en_queue(&q[1], &i, sizeof(int));
  s = "Input Set #0: YES";
  en_queue(&q[1], s, strlen(s));
  s = "Input Set #1: NO";
  en_queue(&q[1], s, strlen(s));
  s = "Input Set #2: NO";
  en_queue(&q[1], s, strlen(s));

	i = 1;
  en_queue(&q[1], &i, sizeof(int));
  s = "1010";
  en_queue(&q[1], s, strlen(s));

  en_queue(&q[1], &i, sizeof(int));
  s = "The judges are good!";
  en_queue(&q[1], s, strlen(s));
}

static int getNumber(const char *s) {
  int i, j = 0;
  char *d = malloc(strlen(s));
  
  /*extract all digits from string, ignoring other chars*/
  for(i = 0; i < (int)strlen(s); i++)
    if(isdigit(s[i]))
      d[j++] = s[i];
  d[j] = '\0';

  /*convert string to int*/
  char *n;
  errno = 0;
  int result = strtol(d, &n, 0);
  
  if(!(errno != 0 || *n != '\0' || n == d)) {
    free(d);
    return result;
  } else {
    free(d);
    return -1;
  }
}

static int getBatchCount(queue* q) {
  int *ip = (int*)de_queue(q), tmp;
    
  if(ip != NULL) {
    tmp = *ip;
    free(ip);	  
    return tmp;
    
  } else
    return 0;
}

static void getBatchData(queue* q, int sz, char* s[]) {
  int i;
  
  for(i = 0; i < sz; i++) 
    s[i] = (char*)de_queue(q);
}

static void compareQueues(void) {
  int b = 0, i, sz[2];
  bool batches_ok = true;
  
  while(!(empty_queue(&q[0]) || empty_queue(&q[1]) || !batches_ok)) {
  
    sz[0] = getBatchCount(&q[0]);
    sz[1] = getBatchCount(&q[1]);
    b++;
  
    if(sz[0] == sz[1])  { /*batches must be equal, otherwise rejected*/    
      char* s[2][sz[0]];
      
      getBatchData(&q[0], sz[0], s[0]);  
      getBatchData(&q[1], sz[1], s[1]);  
      
      bool accepted = true, presentation = true;
     
      for(i = 0; i < sz[0]; i++) 
        if(strcmp(s[0][i], s[1][i])) { /*mismatch*/
          accepted = false;
          
          /*are the numbers the same?*/
          if(getNumber(s[0][i]) != getNumber(s[1][i])) {
            presentation = false;
            break;
          }
      }
      
      for(i = 0; i < sz[0]; i++) {
        printf("%s\t%s\n", s[0][i], s[1][i]);
        free(s[0][i]);
        free(s[1][i]);
      }

      if(accepted)
        printf("Run #%d: Accepted\n", b);
      else if(presentation)
        printf("Run #%d: Presentation Error\n", b);
      else
        printf("Run #%d: Wrong Answer\n", b);
    } else
      batches_ok = false; /*reject further processing*/
  }
}

int main(void) {
  buildQueues();
  compareQueues();
  clear_queue(&q[0]);
  clear_queue(&q[1]);
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./judge 
The answer is: 10	The answer is: 10
The answer is: 5	The answer is: 5
Run #1: Accepted
The answer is: 10	The answer is: 10
The answer is: 5	The answer is: 15
Run #2: Wrong Answer
The answer is: 10	The answer is: 10
The answer is:  5	The answer is: 5
Run #3: Presentation Error
Input Set #1: YES	Input Set #0: YES
Input Set #2: NO	Input Set #1: NO
Input Set #3: NO	Input Set #2: NO
Run #4: Wrong Answer
1 0 1 0	1010
Run #5: Presentation Error
The judges are mean!	The judges are good!
Run #6: Presentation Error
*/

