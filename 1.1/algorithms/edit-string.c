/*see README for original credits */

#include<stdio.h>
#include<string.h>
#include"edit-string.h"

static cell m[MAXLEN][MAXLEN];

static int indel(char c);
static int match(char c, char d);
static void column_init(int i);	/* what is m[i][0]? */
static void row_init(int i);		/* what is m[0][i]? */
static void delete_out(const char* s, int i);
static void insert_out(const char* t, int j);
static void match_out(const char* s, const char* t, int i, int j);

/*	For normal edit distance computation  */

void goal_cell(const char* s, const char* t, int* i, int* j) {
	*i = strlen(s)-1;
	*j = strlen(t)-1;
}

int string_compare(char* s, char* t) {
	int i, j;

	for(i = 0; i < MAXLEN; i++) {
		row_init(i); 
		column_init(i);	
	}

  int ls = (int)strlen(s), lt = (int)strlen(t);
  
	for(i = 1; i < ls; i++)
		for(j = 1; j < lt; j++) {
    	int opt[3];		/* cost of the three options */

			opt[MATCH] = m[i-1][j-1].cost + match(s[i], t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);

			m[i][j].cost = opt[MATCH]; 
			m[i][j].parent = MATCH;
			
			int k;

			for(k = INSERT; k <= DELETE; k++)
				if(opt[k] < m[i][j].cost) {
					m[i][j].cost = opt[k]; 
					m[i][j].parent = k;
				}
		}

	goal_cell(s, t, &i, &j);
	return m[i][j].cost;
} 

void reconstruct_path(char* s, char* t, int i, int j) {
  switch(m[i][j].parent) {
    case NONE:
      break;

    case MATCH:
      reconstruct_path(s, t, i-1, j-1);	
      match_out(s, t, i, j);
      break;

    case INSERT:
      reconstruct_path(s, t, i, j-1); 
      insert_out(t, j);
      break;

    case DELETE:
      reconstruct_path(s, t, i-1, j); 
      delete_out(s, i);
      break;

    default:
      break;
  }
}

void print_matrix(const char* s, const char* t, bool costQ) {
	int x = strlen(s), y = strlen(t);
	int i, j;

	printf("   ");
	for(i = 0; i < y; i++)
		printf("  %c", t[i]);
	printf("\n");

	for(i = 0; i < x; i++) {
		printf("%c: ", s[i]);

		for(j = 0; j < y; j++) 
			if(costQ)
				printf(" %2d", m[i][j].cost);
			else
				printf(" %2d", m[i][j].parent);

		printf("\n");
	}
}

static int indel(char c) {
	return 1;
}

static int match(char c, char d) {
	if(c == d) 
	  return 0;
	
	return 1;
}

static void column_init(int i)	{ /* what is m[i][0]? */
  m[i][0].cost = i;

	if(i > 0)
		m[i][0].parent = DELETE;
	else
		m[0][i].parent = NONE;
}

static void row_init(int i) {		/* what is m[0][i]? */
	m[0][i].cost = i;

	if(i > 0)
		m[0][i].parent =  INSERT;
	else
		m[0][i].parent = NONE;
}

static void delete_out(const char* s, int i) {
  printf("D");
}

static void insert_out(const char* t, int j) {
	printf("I");
}

static void match_out(const char* s, const char* t, int i, int j) {
	if(s[i] == t[j]) 
	  printf("M");
	else 
	  printf("S");
}

