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
2.1.1 Coin-tossing

(refer to Understanding Probability Chance Rules in Everyday Life, 
Second Edition by HENK TIJMS, Vrije University)

Table 2.1. Results of coin-toss simulations.

Fair coin ( p = 1/2 ) Unfair coin ( p = 1/6 )

n         K(n) − np   fn      K(n) − np   fn

10        1.0       0.6000    0.33      0.2000
25        1.5       0.5600    1.83      0.2400
50        2.0       0.5400    2.67      0.2200
100       2.0       0.5200    3.33      0.2040
250       1.0       0.5040    5.33      0.1880
500       −2.0      0.4960    4.67      0.1760
1,000     10.0      0.5100    −3.67     0.1630
2,500     12.0      0.5048    −15.67    0.1604
5,000     −9.0      0.4982    −5.33     0.1656
7,500     11.0      0.5015    21.00     0.1659
10,000    24.0      0.5024    −33.67    0.1633
15,000    40.0      0.5027    −85.00    0.1610
20,000    91.0      0.5045    −17.33    0.1658
25,000    64.0      0.5026    −30.67    0.1654
30,000    78.0      0.5026    −58.00    0.1647
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define PRECISION 1200
#define FAIR_HEADS PRECISION / 2
#define EXP_FAIR_HEADS 0.5
#define BIAS_HEADS PRECISION / 6
#define EXP_BIAS_HEADS 0.16667

static long tosses[] = {10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 15000, 
  20000, 25000, 30000, 50000, 100000, 250000, 500000, 1000000};
#define SIZE (int)(sizeof(tosses) / sizeof(tosses[0]))

static void printCoinResults(int n, int t, float e) {
  int i, kn = 0, r;

  for(i = 0; i < n; i++) {
    r = rand() % PRECISION;
    if(r < t)
      kn++;
  }
  printf("%d\t%.1f\t%.4f\n", n, kn - (float)n*e, (float)kn/n);
}

static void printResults(void) {
  int i;
  srand(time(NULL));
  
  printf("\nfair coin 1/2\n");
  for(i = 0; i < SIZE; i++)
    printCoinResults(tosses[i], FAIR_HEADS, EXP_FAIR_HEADS);

  printf("\nbiased coin 1/6\n");
  for(i = 0; i < SIZE; i++)
    printCoinResults(tosses[i], BIAS_HEADS, EXP_BIAS_HEADS);
}

int main(void) {
  printResults();
  return 0;
}

/* test runs
osman@osman-vbox-l32:~/src/probs$ ./coin-toss 
fair coin 1/2
10	-1.0	0.4000
25	0.5	0.5200
50	4.0	0.5800
100	3.0	0.5300
250	-5.0	0.4800
500	-1.0	0.4980
1000	32.0	0.5320
2500	-14.0	0.4944
5000	-27.0	0.4946
15000	24.0	0.5016
20000	32.0	0.5016
25000	9.0	0.5004
30000	26.0	0.5009
50000	6.0	0.5001
100000	-122.0	0.4988
250000	-371.0	0.4985
500000	-350.0	0.4993
1000000	176.0	0.5002

biased coin 1/6
10	-0.7	0.1000
25	-1.2	0.1200
50	-1.3	0.1400
100	-1.7	0.1500
250	-2.7	0.1560
500	-1.3	0.1640
1000	-8.7	0.1580
2500	-7.7	0.1636
5000	-13.3	0.1640
15000	-58.0	0.1628
20000	62.6	0.1698
25000	-75.7	0.1636
30000	63.9	0.1688
50000	-27.5	0.1661
100000	250.0	0.1692
250000	31.5	0.1668
500000	-304.0	0.1661
1000000	-106.0	0.1666
*/

