/*see README for original credits */

#include "bool.h"
#include "editdistance.h"
#include "stringedit.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	int i, j;
	char s[MAXLEN], t[MAXLEN];		/* input strings */

	s[0] = t[0] = ' ';
	scanf("%s", &(s[1]));	scanf("%s", &(t[1]));

	printf("matching cost = %d \n", string_compare(s, t));

	print_matrix(s, t, TRUE);
	printf("\n");
	print_matrix(s, t, FALSE);
	goal_cell(s, t, &i, &j);
	printf("%d %d\n", i, j);
	reconstruct_path(s, t, i, j);
	printf("\n");
	
	return 0;
}

/* test runs
osman@osman-desktop:~/src/algorithms$ ./stringedit-demo 
a
b
matching cost = 1 
        b
 :   0  1
a:   1  1

        b
 :  -1  1
a:   2  0
1 1
S
osman@osman-desktop:~/src/algorithms$ ./stringedit-demo 
a
a
matching cost = 0 
        a
 :   0  1
a:   1  0

        a
 :  -1  1
a:   2  0
1 1
M
osman@osman-desktop:~/src/algorithms$ ./stringedit-demo 
bat
cat
matching cost = 1 
        c  a  t
 :   0  1  2  3
b:   1  1  2  3
a:   2  2  1  2
t:   3  3  2  1

        c  a  t
 :  -1  1  1  1
b:   2  0  0  0
a:   2  0  0  1
t:   2  0  2  0
3 3
SMM
osman@osman-desktop:~/src/algorithms$ ./stringedit-demo 
hello
world
matching cost = 4 
        w  o  r  l  d
 :   0  1  2  3  4  5
h:   1  1  2  3  4  5
e:   2  2  2  3  4  5
l:   3  3  3  3  3  4
l:   4  4  4  4  3  4
o:   5  5  4  5  4  4

        w  o  r  l  d
 :  -1  1  1  1  1  1
h:   2  0  0  0  0  0
e:   2  0  0  0  0  0
l:   2  0  0  0  0  1
l:   2  0  0  0  0  0
o:   2  0  0  0  2  0
5 5
SSSMS
osman@osman-desktop:~/src/algorithms$ ./stringedit-demo 
Thoushaltnotkill
Youshallnotmurder
matching cost = 9 
        Y  o  u  s  h  a  l  l  n  o  t  m  u  r  d  e  r
 :   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
T:   1  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
h:   2  2  2  3  4  4  5  6  7  8  9 10 11 12 13 14 15 16
o:   3  3  2  3  4  5  5  6  7  8  8  9 10 11 12 13 14 15
u:   4  4  3  2  3  4  5  6  7  8  9  9 10 10 11 12 13 14
s:   5  5  4  3  2  3  4  5  6  7  8  9 10 11 11 12 13 14
h:   6  6  5  4  3  2  3  4  5  6  7  8  9 10 11 12 13 14
a:   7  7  6  5  4  3  2  3  4  5  6  7  8  9 10 11 12 13
l:   8  8  7  6  5  4  3  2  3  4  5  6  7  8  9 10 11 12
t:   9  9  8  7  6  5  4  3  3  4  5  5  6  7  8  9 10 11
n:  10 10  9  8  7  6  5  4  4  3  4  5  6  7  8  9 10 11
o:  11 11 10  9  8  7  6  5  5  4  3  4  5  6  7  8  9 10
t:  12 12 11 10  9  8  7  6  6  5  4  3  4  5  6  7  8  9
k:  13 13 12 11 10  9  8  7  7  6  5  4  4  5  6  7  8  9
i:  14 14 13 12 11 10  9  8  8  7  6  5  5  5  6  7  8  9
l:  15 15 14 13 12 11 10  9  8  8  7  6  6  6  6  7  8  9
l:  16 16 15 14 13 12 11 10  9  9  8  7  7  7  7  7  8  9

        Y  o  u  s  h  a  l  l  n  o  t  m  u  r  d  e  r
 :  -1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
T:   2  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
h:   2  0  0  0  0  0  1  1  1  1  1  1  1  1  1  1  1  1
o:   2  0  0  0  0  0  0  0  0  0  0  1  1  1  1  1  1  1
u:   2  0  2  0  1  1  1  0  0  0  0  0  0  0  1  1  1  1
s:   2  0  2  2  0  1  1  1  1  1  1  1  0  0  0  0  0  0
h:   2  0  2  2  2  0  1  1  1  1  1  1  1  1  1  0  0  0
a:   2  0  2  2  2  2  0  1  1  1  1  1  1  1  1  1  1  1
l:   2  0  2  2  2  2  2  0  0  1  1  1  1  1  1  1  1  1
t:   2  0  2  2  2  2  2  2  0  0  0  0  1  1  1  1  1  1
n:   2  0  2  2  2  2  2  2  0  0  1  1  0  0  0  0  0  0
o:   2  0  0  2  2  2  2  2  0  2  0  1  1  1  1  1  1  1
t:   2  0  2  2  2  2  2  2  0  2  2  0  1  1  1  1  1  1
k:   2  0  2  2  2  2  2  2  0  2  2  2  0  0  0  0  0  0
i:   2  0  2  2  2  2  2  2  0  2  2  2  0  0  0  0  0  0
l:   2  0  2  2  2  2  2  0  0  2  2  2  0  0  0  0  0  0
l:   2  0  2  2  2  2  2  0  0  0  2  2  0  0  0  0  0  0
16 17
DSMMMMMMSMMMIISSSS
*/
