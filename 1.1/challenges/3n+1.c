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
1.6.1     The 3n + 1 Problem
PC/UVa IDs: 110101/100, Popularity: A, Success rate: low Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input                                 Sample Output

1 10                                         1 10 20
100 200                                      100 200 125
201 210                                      201 210 89
900 1000                                     900 1000 174
*/

#include<stdio.h>

static int cycleLength(int n) {
  int counter = 1, next = n;
  
  while(next != 1) {
  
    if((next % 2) == 0)
      next = next / 2;
    else
      next = next * 3 + 1;

    counter++;
  }

  return counter;
}

int main(void) {
  int i, j, length, n, max;
  
  while(scanf("%d %d", &i, &j) != EOF) {
    max = 0;
    
    for(n = i; n <= j; n++) {
      length = cycleLength(n);
      if(length > max) 
        max = length;         
    }
    printf("%d %d %d\n", i, j, max);  
  }
  
  return 0;
}

/* test run
osman@osman-desktop:~/src/challenges$ cc -o 3n+1 3n+1.c 
osman@osman-desktop:~/src/challenges$ ./3n+1 
1 10
1 10 20
100 200
100 200 125
201 210
201 210 89
900 1000
900 1000 174
*/

