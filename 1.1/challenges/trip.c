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
1.6.3     The Trip
PC/UVa IDs: 110103/10137, Popularity: B, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

3
10.00
20.00
30.00

4
15.00
15.01
3.00
3.01

0

Sample Output

$10.00
$11.99
*/

/*
************
* workings *
************

5
5.00 diff is -5.6
7.00 diff is -3.6
11.00 diff is 0.4
13.00 diff is 2.4
17.00 diff is 6.4

avg cost = 10.6

total is either abs(-5.6 + -3.6) or 0.4 + 2.4 + 6.4 = 9.2

3
10.00
20.00
30.00

avg cost = 20
1st pays 3rd 10

total is 10

3
11.00 diff is -9 1/3
20.00 diff is -1/3
30.00 diff is 9 2/3

avg cost = 20 1/3
1st and 2nd pays 3rd 9 2/3

total is 9 2/3 or 9.67

4
15.00
15.01
3.00
3.01

avg cost = 36.02 / 4 = 9.005

15 - 9.005 = 5.995
15.01 - 9.005 = 6.005
9.005 - 3.01 = 5.995
9.005 - 3 = 6.005

4th pays 1st 5.995
3rd pays 2nd 6.005

total is 12
*/

#include<stdio.h>

int main(void) {
/*
  *********
  * input *
  *********
*/
  int count = 5;  /* number of students */
  float expenses[count];  /* student expenses */
  float total = 0;

  expenses[0] = 5;  
  expenses[1] = 7;  
  expenses[2] = 11;  
  expenses[3] = 13;  
  expenses[4] = 17;  

  int i;

  for(i = 0; i < count; i++) 
    total += expenses[i];  


/*
  ***********
  * process *
  ***********
*/
  float avg_cost; /* average expense */
  float diff; /* difference between expense and average */
  float min = 0;  /* minimum payment needed to equalise expenses */

  avg_cost = total / count; 

  /*
    to find min payment either add up all negative or all positive costs
    and perform abs of total
  */
  for(i = 0; i < count; i++) {
    diff = expenses[i] - avg_cost;
    if(diff > 0)
      min += diff;
  }


/*
  **********
  * output *
  **********
*/
  for(i = 0; i < count; i++) 
    printf("%4.2f\n", expenses[i]);

  printf("avg %4.3f \n", avg_cost);
  printf("min %4.2f \n", min);
  
  return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms/challenges$ ./trip 
10.00
20.00
30.00
avg 20.000
min 10.00 

15.00
15.01
3.00
3.01
avg 9.005 
min 12.00 

5.00
7.00
11.00
13.00
17.00
avg 10.600 
min 9.20 
*/
