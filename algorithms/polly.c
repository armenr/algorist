/*see README for original credits */

#define NAMELENGTH	30		/* maximum length of name */
#define NSUITORS	100		/* maximum number of suitors */

#define BESTHEIGHT	180		/* best height in centimeters */
#define BESTWEIGHT	75		/* best weight in kilograms */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char first[NAMELENGTH];		/* suitor's first name */
	char last[NAMELENGTH];          /* suitor's last name */
	int height;			/* suitor's height */
	int weight;			/* suitor's weight */
} suitor;


static suitor suitors[NSUITORS];		/* database of suitors */
static int nsuitors;				/* number of suitors */

void read_suitors() {
	int height, weight;

	nsuitors = 0;

  printf("enter suitor %d 1st name 2nd name height weight: ", nsuitors);
	while(scanf("%s %s %d %d", suitors[nsuitors].first,
		suitors[nsuitors].last, &height, &weight) != EOF) {
			
		suitors[nsuitors].height = abs(height - BESTHEIGHT);
		if(weight > BESTWEIGHT)
			suitors[nsuitors].weight = weight - BESTWEIGHT;
		else
			suitors[nsuitors].weight = - weight;

		nsuitors ++;
    printf("enter suitor %d 1st name 2nd name height weight: ", nsuitors);
	}
}

int suitor_compare(const suitor *a, const suitor *b) {
	int result;			/* result of comparsion */

  if(a->height < b->height) return -1;
  if(a->height > b->height) return 1;

	if(a->weight < b->weight) return -1;
	if(a->weight > b->weight) return 1;

	if((result=strcmp(a->last, b->last)) != 0) return result;

	return(strcmp(a->first, b->first));
}

int main(void) {
	int i;				/* counter */

	read_suitors();
	qsort(suitors, nsuitors, sizeof(suitor), suitor_compare);

	for(i=0; i < nsuitors; i++) 
		printf("%s, %s\n", suitors[i].last, suitors[i].first);
		
  return 0;		
}

