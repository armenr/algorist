/*see README for original credits */

#ifndef SORT_H
#define SORT_H

#include "item.h"

#define NELEM	100		/* size of test arrays */
#define LESS_THAN	-1
#define EQUAL_TO	0
#define GREATER_THAN	1

int binary_search(const item_type s[], item_type key, int low, int high);
void heapsort(item_type s[], int n);
void insertion_sort(item_type s[], int n);
void mergesort(item_type s[], int low, int high);
void quicksort(item_type s[], int l, int h);
void selection_sort(item_type s[], int n);

#endif /* SORT_H */
