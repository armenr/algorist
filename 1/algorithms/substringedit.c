/*see README for original credits */

#include "bool.h"
#include "editdistance.h"
#include <stdio.h>
#include <string.h>

/*	For normal edit distance computation  */
void goal_cell(const char *s, const char *t, int *i, int *j) {
	int k;			/* counter */

	*i = strlen(s) - 1;
	*j = 0;

	for(k = 1; k < (int) strlen(t); k++)
		if(m[*i][k].cost < m[*i][*j].cost) 
		  *j = k;
}

int match(char c, char d) {
	if(c == d) return 0;
	else return 1;
}

int indel(char c) {
	return 1;
}

/* what is m[0][i]? */
void row_init(int i) {
	m[0][i].cost = 0;		/* NOTE CHANGE */
	m[0][i].parent = -1;		/* NOTE CHANGE */
}

/* what is m[i][0]? */
void column_init(int i)	{
  m[i][0].cost = i;
	if(i>0)
		m[i][0].parent = DELETE;
	else
		m[0][i].parent = -1;
}

void match_out(const char *s, const char *t, int i, int j) {
	if(s[i] == t[j]) printf("M");
	else printf("S");
}

void insert_out(const char *t, int j) {
	printf("I");
}

void delete_out(const char *s, int i) {
  printf("D");
}


int main(void) {
	int i, j;
	char s[MAXLEN], t[MAXLEN];		/* input strings */

	s[0] = t[0] = ' ';

	scanf("%s", &(s[1])); scanf("%s", &(t[1]));
	printf("matching cost = %d \n", string_compare(s, t));
	print_matrix(s, t, TRUE);	printf("\n");	print_matrix(s, t, FALSE);

	goal_cell(s, t, &i, &j); printf("%d %d\n", i, j);
	reconstruct_path(s,t, i ,j); printf("\n");
	
	return 0;
}

/* test runs
osman@osman-desktop:~/src/algorithms$ ./substringedit 
a
a
matching cost = 0 
        a
 :   0  0
a:   1  0

        a
 :  -1 -1
a:   2  0
1 1
M
osman@osman-desktop:~/src/algorithms$ ./substringedit 
abba
cabbage
matching cost = 0 
        c  a  b  b  a  g  e
 :   0  0  0  0  0  0  0  0
a:   1  1  0  1  1  0  1  1
b:   2  2  1  0  1  1  1  2
b:   3  3  2  1  0  1  2  2
a:   4  4  3  2  1  0  1  2

        c  a  b  b  a  g  e
 :  -1 -1 -1 -1 -1 -1 -1 -1
a:   2  0  0  0  0  0  0  0
b:   2  0  2  0  0  2  0  0
b:   2  0  2  0  0  1  0  0
a:   2  0  0  2  2  0  1  1
4 5
MMMM
osman@osman-desktop:~/src/algorithms$ ./substringedit 
aaa
zzz
matching cost = 3 
        z  z  z
 :   0  0  0  0
a:   1  1  1  1
a:   2  2  2  2
a:   3  3  3  3

        z  z  z
 :  -1 -1 -1 -1
a:   2  0  0  0
a:   2  0  0  0
a:   2  0  0  0
3 0
DDD
*/
