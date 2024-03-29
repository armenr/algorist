/*see README for original credits */

#include "bool.h"
#include "editdistance.h"
#include <string.h>
#include <stdio.h>

void goal_cell(const char *s, const char *t, int *i, int *j) {
	*i = strlen(s) - 1;
	*j = strlen(t) - 1;
}

int match(char c, char d) {
	if (c == d) return(0);
	else return(MAXLEN);
}

int indel(char c) {
	return 1;
}

void row_init(int i) {		/* what is m[0][i]? */
	m[0][i].cost = i;
	if(i>0)
		m[0][i].parent =  INSERT;
	else
		m[0][i].parent = -1;
}

void column_init(int i)	{ /* what is m[i][0]? */

  m[i][0].cost = i;
	if(i>0)
		m[i][0].parent = DELETE;
	else
		m[0][i].parent = -1;
}

void match_out(const char *s, const char *t, int i, int j) {
	if (s[i] == t[j]) printf("%c", s[i]);
}

void insert_out(const char *t, int j) {}
void delete_out(const char *s, int i) {}

int main(void) {
	int i, j;
	int lcslen, complen;
	char s[MAXLEN], t[MAXLEN];		/* input strings */

	s[0] = t[0] = ' ';
	scanf("%s", &(s[1])); scanf("%s", &(t[1]));

	complen = string_compare(s, t);
	lcslen = (strlen(s) + strlen(t) - 2 - complen) / 2;
	printf("length of longest common subsequence = %d\n", lcslen);
	goal_cell(s, t, &i, &j);
	reconstruct_path(s, t, i, j);
	printf("\n");
	return 0;
}

/* test run
osman@osman-desktop:~/src/algorithms$ ./lcs
democrat 
republican
length of longest common subsequence = 3
eca
*/

