/*see README for original credits */

#include <stdio.h>
#include <stdlib.h> /* atoi() */

static unsigned int calls;

static unsigned int formula_ackermann(unsigned int m, unsigned int n) {
  calls++;
  while(1) {
    switch(m) {
      case 0:  return n + 1;
      case 1:  return n + 2;
      case 2:  return (n << 1) + 3;
      case 3:  return (1 << (n+3)) - 3;
      default:
      
        if(n == 0) 
          n = 1;
        else 
          n = formula_ackermann(m, n - 1);
        
        m--;
        break;
    }
  }
}

static unsigned int iterative_ackermann(unsigned int m, unsigned int n) {
  calls++;
  while (m != 0) {
    if(n == 0) 
      n = 1;
    else
      n = iterative_ackermann(m, n - 1);
    m--;
  }
  return n + 1;
}

static unsigned int naive_ackermann(unsigned int m, unsigned int n) {
  calls++;
  if(m == 0)
    return n + 1;
  else if(n == 0)
    return naive_ackermann(m - 1, 1);
  else
    return naive_ackermann(m - 1, naive_ackermann(m, n - 1));
}

int main(int argc, char* argv[]) {
  unsigned int m, n, result;
  m = (unsigned)atoi(argv[1]);
  n = (unsigned)atoi(argv[2]);

  calls = 0;
  result = naive_ackermann(m, n);
  printf("Naive:     %u (%u calls)\n", result, calls);

  calls = 0;
  result = iterative_ackermann(m, n);
  printf("Iterative: %u (%u calls)\n", result, calls);

  calls = 0;
  result = formula_ackermann(m, n);
  printf("Formula:   %u (%u calls)\n", result, calls);

  return 0;
}

