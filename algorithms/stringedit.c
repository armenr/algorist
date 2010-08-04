/*see README for original credits */

#include "editdistance.h"
#include "stringedit.h"
#include <stdio.h>
#include <string.h>

/*	For normal edit distance computation  */

void goal_cell(const char *s, const char *t, int *i, int *j) {
	*i = strlen(s) - 1;
	*j = strlen(t) - 1;
}

int match(char c, char d) {
	if(c == d) return 0;
	else return 1;
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
	if(s[i] == t[j]) printf("M");
	else printf("S");
}

void insert_out(const char *t, int j) {
	printf("I");
}

void delete_out(const char *s, int i) {
  printf("D");
}
