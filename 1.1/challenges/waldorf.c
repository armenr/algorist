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
3.8.2 Where’s Waldorf ?
PC/UVa IDs: 110302/10010, Popularity: B, Success rate: average Level: 2

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input

1

8 11

abcDEFGhigg
hEbkWalDork
FtyAwaldORm
FtsimrLqsrc
byoArBeDeyv
Klcbqwikomk
strEBGadhrb
yUiqlxcnBjf

4

Waldorf
Bambi
Betty
Dagbert

Sample Output

2 5
2 3
1 2
7 8

*/

#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ROWS 8
#define COLS 11
#define D_ROWS 2 * (ROWS + COLS - 1)

/*8 by 11 grid*/
char* grid[ROWS] = {"abcDEFGhigg", "hEbkWalDork", "FtyAwaldORm", "FtsimrLqsrc", 
  "byoArBeDeyv", "Klcbqwikomk", "strEBGadhrb", "yUiqlxcnBjf"};

/*11 by 8 transposed grid for vertical searches*/
char* t_grid[COLS];

typedef struct {
  int row; int col; /*starting point for diagonal grid lines*/
} point;

typedef struct {
  char* data[D_ROWS];
  point start[D_ROWS];
} diagonal_grid;

diagonal_grid d_grid;

char* search[] = {"Waldorf", "Bambi", "Betty", "Dagbert", "aEyirwan", 
  "nawriyEa", "GDOrv", "vrODG", "blrq", "qrlb", "Brk", "krB", "vmhn", "nhmv", 
  "DiG", "GiD"};
#define SEARCH (int)(sizeof(search) / sizeof(search[0]))

static char* upperCaseString(const char* s, char* d) {
  int i, l = (int)strlen(s)+1;
  for(i = 0; i < l; i++) 
    d[i] = toupper(s[i]);
  return d;
}

static char* reverseString(const char* s, char* d) {
  int i, l = (int)strlen(s);
  for(i = 0; i < l; i++) 
    d[i] = s[l-i-1];
  d[l] = '\0';    
  return d;
}

static int find(const char* substr, const char* str) {
  char* cptr;
  char* str1 = malloc(strlen(str)+1);
  char* substr1 = malloc(strlen(substr)+1);
  
  cptr = strstr(upperCaseString(str, str1), upperCaseString(substr, substr1));
  free(substr1);
  
  if(cptr != 0) {
    int f = (cptr - str1)+1;
    free(str1);
    return f; /*pointer subtraction to find first matching char*/
  }
  else {
    free(str1);   
    return 0;
  }
}

static void diagonalGrid(const char* gs[], diagonal_grid *gd, 
  int rows, int cols) {
  int i, c, r, dr = 0;
  char s[rows];
    
  for(i = 0; i < cols; i++, dr++) {
    int k = 0;
    for(c = i, r = 0; c < cols && r < rows; c++, r++, k++) 
      s[k] = gs[r][c];
    s[k] = '\0';  
    strcpy(gd->data[dr], s);
    gd->start[dr].row = 0; gd->start[dr].col = i;
  }
    
  for(i = 1; i < rows; i++, dr++) {
    int k = 0;
    for(c = 0, r = i; c < cols && r < rows; c++, r++, k++) 
      s[k] = gs[r][c];
    s[k] = '\0';  
    strcpy(gd->data[dr], s);
    gd->start[dr].row = i; gd->start[dr].col = 0;
  }      
  
  for(i = cols-1; i >= 0; i--, dr++) {
    int k = 0;
    for(c = i, r = 0; c >= 0 && r < rows; c--, r++, k++) 
      s[k] = gs[r][c];
    s[k] = '\0';  
    strcpy(gd->data[dr], s);
    gd->start[dr].row = 0; gd->start[dr].col = i;
  }      

  for(i = 1; i < rows; i++, dr++) {
    int k = 0;
    for(c = COLS-1, r = i; c >= 0 && r < rows; c--, r++, k++) 
      s[k] = gs[r][c];
    s[k] = '\0';  
    strcpy(gd->data[dr], s);
    gd->start[dr].row = i; gd->start[dr].col = COLS-1;
  }
}

/*transpose grid for vertical searches*/
static void allocGrid(char* g[], int rows, int cols) {
  int r;

  for(r = 0; r < rows; r++) 
    g[r] = malloc(cols);
}

static void freeGrid(char* g[], int rows) {
  int r;

  for(r = 0; r < rows; r++) 
    free(g[r]);
}

static void transposeGrid(const char* gs[], char* gt[], int rows, int cols) {
  int r, c;
  char s[rows];

  for(c = 0; c < cols; c++) {
    for(r = 0; r < rows; r++) 
      s[r] = gs[r][c];
    s[r] = '\0';
    strcpy(gt[c], s);
  }
}

static void printGrid(const char* g[], int r) {
  int i;
  for(i = 0; i < r; i++) 
    printf("%s\n", g[i]);
}

static void printResult(const char *s, int row, int col, bool transpose) {
  printf("%s found at ", s);
  if(!transpose)
    printf("%d %d\n", row, col);
  else
    printf("%d %d\n", col, row);
}

static void searchGrid(const char *s, const char *rs, const char* g[], 
  int rows, bool transpose) {
  int i, found;
  for(i = 0; i < rows; i++) {
    found = find(s, g[i]);
    if(found)
      printResult(s, i+1, found, transpose);
    found = find(rs, g[i]);
    if(found) /*for reverses, print normal string and reverse find position*/
      printResult(s, i+1, strlen(g[i])-found-1, transpose);
  }
}

static void searchDiagonalGrid(const char *s, const char *rs, diagonal_grid gd, 
  int rows) {
  int i, found, l = strlen(s);
  
  for(i = 0; i < rows; i++) 
    if(l <= (int)strlen(gd.data[i])) { /*skip rows smaller than search*/
      
      found = find(s, gd.data[i]);
      if(found) {
/*printf("normal %d %d %d\n", gd.start[i].row, gd.start[i].col, found);      */
        if(gd.start[i].col != COLS-1)
          printResult(s, gd.start[i].row + found, 
            gd.start[i].col + found, false);
        else
          printResult(s, gd.start[i].row + found, 
            gd.start[i].col - (found-2), false);
      }
            
      found = find(rs, gd.data[i]);
      if(found) {
/*printf("reverse %d %d %d\n", gd.start[i].row, gd.start[i].col, found);   */
        int l = strlen(rs)-1;   
        if(gd.start[i].col != COLS-1)
          printResult(s, gd.start[i].row + found + l, 
            gd.start[i].col + l + 1, false);
        else
          printResult(s, gd.start[i].row + found + l, 
            gd.start[i].col - found - l + 2 , false);
      }
    }
}

static void searchAllGrids(void) {
  int i;
  for(i = 0; i < SEARCH; i++) {
  
    char* s = search[i];
    char* rs = malloc(strlen(s)+1);
    reverseString(s, rs);

    searchGrid(s, rs, (const char**)grid, ROWS, false);
    searchGrid(s, rs, (const char**)t_grid, COLS, true);
    searchDiagonalGrid(s, rs, d_grid, D_ROWS);
    free(rs);
  }
}

int main(void) {
  allocGrid(t_grid, COLS, ROWS);
  allocGrid(d_grid.data, D_ROWS, COLS);
  transposeGrid((const char**)grid, t_grid, ROWS, COLS);
  diagonalGrid((const char**)grid, &d_grid, ROWS, COLS);
  printGrid((const char**)grid, ROWS);
/*  printGrid((const char**)d_grid.data, D_ROWS);*/
/*  printGrid((const char**)t_grid, ROWS);*/
  searchAllGrids();
  freeGrid(t_grid, COLS);  
  freeGrid(d_grid.data, D_ROWS);  
  return 0;
}

/* test runs
osman@osman-desktop:~/src/challenges$ ./waldorf 
abcDEFGhigg
hEbkWalDork
FtyAwaldORm
FtsimrLqsrc
byoArBeDeyv
Klcbqwikomk
strEBGadhrb
yUiqlxcnBjf
Waldorf found at 2 5
Bambi found at 2 3
Betty found at 1 2
Dagbert found at 7 8
aEyirwan found at 1 1
nawriyEa found at 8 8
GDOrv found at 1 7
vrODG found at 5 11
blrq found at 5 1
qrlb found at 8 4
Brk found at 8 9
krB found at 6 11
vmhn found at 5 11
nhmv found at 8 8
DiG found at 5 8
GiD found at 7 6
*/

