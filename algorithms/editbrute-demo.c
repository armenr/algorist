/*see README for original credits */

#include "bool.h"
#include "editbrute.h"
#include "stringedit.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	int i, j;
	char s[MAXLEN], t[MAXLEN];		/* input strings */

	s[0] = t[0] = ' ';
	scanf("%s", &(s[1]));	scanf("%s", &(t[1]));

	printf("matching cost = %d \n", string_compare(s, t, strlen(s)-1,
	  strlen(t)-1));

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
osman@osman-desktop:~/src/algorithms$ ./editbrute-demo 
a
b
matching cost = 1 
        b
 :   0  0
a:   0  1

        b
 :   0  0
a:   0  0
1 1
MS
osman@osman-desktop:~/src/algorithms$ ./editbrute-demo 
a
a
matching cost = 0 
        a
 :   0  0
a:   0  0

        a
 :   0  0
a:   0  0
1 1
MM
osman@osman-desktop:~/src/algorithms$ ./editbrute-demo 
bat
cat
matching cost = 1 
        c  a  t
 :   0  0  0  0
b:   0  1  2  3
a:   0  2  1  2
t:   0  3  2  1

        c  a  t
 :   0  0  0  0
b:   0  0  0  0
a:   0  0  0  0
t:   0  0  0  0
3 3
MSMM
*/
