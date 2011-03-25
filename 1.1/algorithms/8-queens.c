/*see README for original credits */

#include"back-track.h"
#include<math.h>
#include<stdbool.h>
#include<stdio.h>

int solution_count; /* how many solutions are there? */

void process_solution(const int a[], int k) {
  solution_count++;
}

bool is_a_solution(const int a[], int k, int n) {
  return (k == n);
}

void make_move(const int a[], int k, int n) {}
void unmake_move(const int a[], int k, int n) {}

/*	What are possible elements of the next slot in the 8-queens problem? */
void construct_candidates(const int a[], int k, int n, int c[], int *ncandidates) {
  int i, j; 
  bool legal_move; /* might the move be legal? */

  *ncandidates = 0;

  for(i = 1; i <= n; i++) {
    legal_move = true;
  
    for(j = 1; j < k; j++) {

      if(abs((k) - j) == abs(i - a[j])) /* diagonal threat */
        legal_move = false;

      if(i == a[j]) /* column threat */
        legal_move = false;
      }

    if(legal_move == true) {
      c[*ncandidates] = i; (*ncandidates)++;
    }
  }
}

int main(void) {
  int a[NMAX]; /* solution vector */
  int i; /* counter */

  for(i = 1; i <= 10; i++) {
    solution_count = 0;
    back_track(a, 0, i);
    printf("n=%d  solution_count=%d\n", i, solution_count);
  }
  return 0;
}

/* test run 
osman@osman-desktop:~/src/algorithms$ ./8-queens 
n=1  solution_count=1
n=2  solution_count=0
n=3  solution_count=0
n=4  solution_count=2
n=5  solution_count=10
n=6  solution_count=4
n=7  solution_count=40
n=8  solution_count=92
n=9  solution_count=352
n=10  solution_count=724
*/
