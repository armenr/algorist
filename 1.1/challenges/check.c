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
1.6.7    Check the Check
PC/UVa IDs: 110107/10196, Popularity: B, Success rate: average Level: 1

(refer to PROGRAMMING CHALLENGES by Steven S. Skiena & Miguel A. Revilla)

Sample Input                               Sample Output

..k.....                                   Game #1: black king is in check.
ppp.pppp                                   Game #2: white king is in check.
........
.R...B..
........
........
PPPPPPPP
K.......

rnbqk.nr
ppp..ppp
....p...
...p....
.bPP....
.....N..
PP..PPPP
RNBQKB.R
*/

#include<stdbool.h>
#include<stdio.h>

#define SIZE 8
#define SCANSIZE SIZE + 1
#define STOP -1

typedef struct {
  int x, y;
  char item;
  bool black; /* false if white */
} piece;

static char board[SIZE][SIZE + 1];  /* add one to cols to store null char */
static piece black[2 * SIZE], white[2 * SIZE];
static int bx, by, wx, wy; /* x, y co-ords of kings */

static bool readBoard(void) {
  int y, x, b = 0, w = 0;
  char c;
  bool valid = true;
  
  for(y = 0; y < SIZE; y++) {
    scanf("%sSCANSIZE", board[y]);

    for(x = 0; x < SIZE; x++) {
      c = board[y][x];
      
      switch(c) {
        case 'b': case 'k': case 'n': case 'p': case 'q': case 'r': 
          if(b < 2 * SIZE) {
            black[b].item = c; black[b].y = y; black[b].x = x; 
            black[b].black = true; b++;

            if(c == 'k') {
              if(bx == -1 && by == -1) { /* one king only */
                by = y; bx = x;
              } else 
                valid = false;
            }
          
          } else  /* too many pieces */
            valid = false;
          break;
          
        case 'B': case 'K': case 'N': case 'P': case 'Q': case 'R': 
          if(w < 2 * SIZE) {
            white[w].item = c; white[w].y = y; white[w].x = x; 
            white[w].black = false; w++;

            if(c == 'K') {
              if(wx == -1 && wy == -1) { /* one king only */
                wy = y; wx = x;
              } else  
                valid = false;
            }
            
          } else  /* too many pieces */
            valid = false;
          break;

        case '.':
          break;
          
        default:
          valid = false;      
      }
    }
  }      
  return valid;    
}

static int checkSquare(int x, int y, int kx, int ky) {
  int found;
  
    if(y == ky && x == kx) 
      found = true;
    else if(board[y][x] == '.')
      found = false;
    else  /* piece stopping search, for all except knights */
      found = STOP;
      
  return found;
}

static bool checkBishop(piece p, int kx, int ky) {
  int check;
  int y, x;
  
  for(y = p.y - 1, x = p.x - 1; y >= 0 && x >= 0; y--, x--) {
    check = checkSquare(x, y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }
     
  for(y = p.y - 1, x = p.x + 1; y >= 0 && x < SIZE; y--, x++) {
    check = checkSquare(x, y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }

  for(y = p.y + 1, x = p.x - 1; y < SIZE && x >= 0; y++, x--) {
    check = checkSquare(x, y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }

  for(y = p.y + 1, x = p.x + 1; y < SIZE && x < SIZE; y++, x++) {
    check = checkSquare(x, y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }
      
  return false;
}

static bool checkKnightX(piece p, int y, int kx, int ky) {
  int x;
  
  x = p.x - 1;
  if(x >= 0) 
    if(y == ky && x == kx) 
      return true;
  
  x = p.x + 1;
  if(x < SIZE) 
    if(y == ky && x == kx) 
      return true;
      
  return false;
}

static bool checkKnightY(piece p, int x, int kx, int ky) {
  int y;
  
  y = p.y - 1;
  if(y >= 0) 
    if(y == ky && x == kx) 
      return true;
  
  y = p.y + 1;
  if(y < SIZE) 
    if(y == ky && x == kx) 
      return true;
      
  return false;
}

static bool checkKnight(piece p, int kx, int ky) {
  int y, x;

  y = p.y - 2;
  if(y >= 0) 
    if(checkKnightX(p, y, kx, ky))
      return true;  

  y = p.y + 2;
  if(y < SIZE) 
    if(checkKnightX(p, y, kx, ky))
      return true;  
  
  x = p.x - 2;
  if(x >= 0) 
    if(checkKnightY(p, x, kx, ky))
      return true;  

  x = p.x + 2;
  if(x < SIZE) 
    if(checkKnightY(p, x, kx, ky))
      return true;  
        
  return false;
}

static bool checkPawn(piece p, int kx, int ky) {
  int check;
  
  switch(p.black) {
    case true:  /* black */

      if(p.y > 0 && p.y < SIZE - 1) {
        if(p.x > 0) {
          check = checkSquare(p.x - 1, p.y + 1, kx, ky);            
          if(check == true) 
            return true;
        }

        if(p.x < SIZE - 1) {
          check = checkSquare(p.x + 1, p.y + 1, kx, ky);            
          if(check == true) 
            return true;
        }
      }
        
      break;
     
    case false: /* white */

      if(p.y > 0 && p.y < SIZE - 1) {
        if(p.x > 0) {
          check = checkSquare(p.x - 1, p.y - 1, kx, ky);            
          if(check == true) 
            return true;
        }

        if(p.x < SIZE - 1) {
          check = checkSquare(p.x + 1, p.y - 1, kx, ky);            
          if(check == true) 
            return true;
        }
      }        
  }
      
  return false;
}

static bool checkRook(piece p, int kx, int ky) {
  int check;
  int y, x;
   
  for(y = p.y - 1; y >= 0; y--) {
    check = checkSquare(p.x, y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }
     
  for(y = p.y + 1; y < SIZE; y++) {
    check = checkSquare(p.x, y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }

  for(x = p.x - 1; x >= 0; x--) {
    check = checkSquare(x, p.y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }

  for(x = p.x + 1; x < SIZE; x++) {
    check = checkSquare(x, p.y, kx, ky);
    if(check == true) 
      return true;
    else if(check == STOP)
      break;
  }
      
  return false;
}

static bool checkPiece(piece p, int kx, int ky) {
  bool check = false;

  switch(p.item) {
    case 'b': case 'B': /* bishop */
      if(checkBishop(p, kx, ky))
        check = true;
      break;
                
    case 'n': case 'N': /* knight */
      if(checkKnight(p, kx, ky))
        check = true;
      break;

    case 'p': case 'P': /* pawn */
      if(checkPawn(p, kx, ky))
        check = true;
      break;

    case 'q': case 'Q': /* queen */
      if(checkBishop(p, kx, ky))
        check = true;

      if(checkRook(p, kx, ky))
        check = true;
      break;

    case 'r': case 'R': /* rook */
      if(checkRook(p, kx, ky))
        check = true;
      break;
  }
  return check;
}

int main(void) {
  int i;
  
  bx = by = wx = wy = -1;

  if(!readBoard()) return -1;

  for(i = 0; i < 2 * SIZE; i++) {
  
    if(checkPiece(black[i], wx, wy))
      printf("white king is in check.\n");
      
    if(checkPiece(white[i], bx, by))
      printf("black king is in check.\n");
  }     
  
  return 0; 
}

/* test runs
osman@osman-desktop:~/src/challenges$ cc -o check check.c 
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
........
......b.
B.....K.
black king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
........
......b.
.B.....K
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
.....b..
......n.
.B.....K
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
.....b..
......b.
.B.....K
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
.....b..
......B.
.B.....K
osman@osman-desktop:~/src/challenges$ 
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
.....b..
......B.
B......K
black king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
.......k
........
........
........
........
.....b..
......B.
.B.....K
osman@osman-desktop:~/src/challenges$ ./check 
R......k
........
........
........
........
.....b..
......B.
.B.....K
black king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
........
........
........
........
.....b..
......B.
.B.....K
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
.......r
........
........
........
.....b..
......B.
.B.....K
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
.......r
........
........
........
.....b..
......BR
.B.....K
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
.......r
........
........
........
.....b..
......BR
QB.....K
black king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
......qr
........
........
........
.....b..
......BR
QB.....K
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
......qr
........
........
........
.....b..
......BR
QB.q...K
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
......Pr
.....P..
........
........
.....b..
......BR
QB.....K
black king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
......qr
.....p..
........
........
.....b..
......BR
QB.....K
osman@osman-desktop:~/src/challenges$ ./check 
R.....rk
...p..qr
.....p..
........
........
.....b..
......BR
QB.....K
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..qr
.....p..
........
........
.....b..
......BR
QB.P...K
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..Pr
.....p..
........
........
.....b..
......BR
QB.P...K
black king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..Pr
.....p..
........
........
.....b..
......pR
QB.P...K
black king is in check.
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..pr
.....p..
........
........
.....b..
......PR
QB.P...K
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..pr
.....p..
........
........
.....b..
.....nPR
QB.P...K
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p.Npr
.....p..
........
........
.....b..
.....nPR
QB.P...K
black king is in check.
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..pr
.....pN.
........
........
.....b..
.....nPR
QB.P...K
black king is in check.
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..pr
.....pN.
........
........
.....bn.
......PR
QB.P...K
black king is in check.
white king is in check.
osman@osman-desktop:~/src/challenges$ ./check 
Rp....rk
...p..pr
.....pn.
........
........
.....bN.
......PR
QB.P...K
*/
