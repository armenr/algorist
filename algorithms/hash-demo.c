/*see README for original credits */

#include"hashtbl.h"
#include<stdio.h>

int main(void) {
	HASHTBL *hashtbl;
	char *spain, *italy;

	if(!(hashtbl = hashtbl_create(16, NULL))) {
		fprintf(stderr, "ERROR: hashtbl_create() failed\n");
		exit(EXIT_FAILURE);
	}

	hashtbl_insert(hashtbl, "France", "Paris");
	hashtbl_insert(hashtbl, "England", "London");
	hashtbl_insert(hashtbl, "Sweden", "Stockholm");
	hashtbl_insert(hashtbl, "Germany", "Berlin");
	hashtbl_insert(hashtbl, "Norway", "Oslo");
	hashtbl_insert(hashtbl, "Italy", "Rome");
	hashtbl_insert(hashtbl, "Spain", "Madrid");
	hashtbl_insert(hashtbl, "Estonia", "Tallinn");
	hashtbl_insert(hashtbl, "Netherlands", "Amsterdam");
	hashtbl_insert(hashtbl, "Ireland", "Dublin");

	printf("After insert:\n");
	italy = hashtbl_get(hashtbl, "Italy");
	printf("Italy: %s\n", italy ? italy : "-");
	spain = hashtbl_get(hashtbl, "Spain");
	printf("Spain: %s\n", spain ? spain : "-");

	hashtbl_remove(hashtbl, "Spain");

	printf("After remove:\n");
	spain = hashtbl_get(hashtbl, "Spain");
	printf("Spain: %s\n", spain ? spain : "-");


	hashtbl_resize(hashtbl, 8);

	printf("After resize:\n");
	italy = hashtbl_get(hashtbl, "Italy");
	printf("Italy: %s\n", italy ? italy : "-");

	hashtbl_destroy(hashtbl);
  return 0;
}

